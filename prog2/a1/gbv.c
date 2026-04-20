#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gbv.h"
#include "util.h"
#include "aux.h"

// super bloco
typedef struct {
  int qtd; 
  long offset; 
} bloco; 

int gbv_create(const char *filename) {
  FILE *f = fopen(filename, "wb");
  if (!f) {
    perror("erro: falha ao abrir arquivo");
    return -1;
  }

  bloco sb;
  sb.qtd = 0;
  sb.offset = sizeof(sb); 

  if (!fwrite(&sb, sizeof(sb), 1, f)) {   
    perror("erro: falha ao escrever no arquivo");
    fclose(f);
    return -1;
  }

  fclose(f);
  return 0;
}

int gbv_open(Library *lib, const char *filename) {
  if (!lib || !filename) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  FILE *f = fopen(filename, "rb");
  if (!f) { 
    if (gbv_create(filename)) { //se n conseguiu criar, tenta criar de nv
      perror("erro: falha ao criar arquivo");
      return -1;
    }
    f = fopen(filename, "rb"); //se n conseguiu abrir nem oq criou, ai ja era
    if (!f) {
      perror("erro: falha ao abrir arquivo");
      return -1;
    }
  }

  bloco sb; 
  if (fread(&sb, sizeof(sb), 1, f) != 1) { //verifica se conseguiu ler  o sb 
    perror("erro: falha ao ler arquivo");
    fclose(f);
    return -1;
  }

  lib -> count = sb.qtd; //pega qtd de doc

  if (sb.qtd) { //se nao ta vazio
    lib -> docs = calloc(sb.qtd, sizeof(Document)); //aloca os docs
    if (!lib -> docs) {
      perror("erro: falta de memoria");
      fclose(f);
      return -1;
    }
    fseek(f, sb.offset, SEEK_SET); //aponta pra onde deve ficar os documentos a serem lidos
    if (fread(lib -> docs, sizeof(Document), sb.qtd, f) != sb.qtd) { // coloca os docs do arq dentro da lib
      perror("erro: falha ao ler arquivo");
      free(lib -> docs);
      fclose(f);
      return -1;
    }
  }
  else
    lib -> docs = NULL; //aponta pra null (?) n sei se precisa na real

  fclose(f);
  return 0;
}

int gbv_add(Library *lib, const char *archive, const char *docname) {
  if (!lib || !archive || !docname) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }
  
  if (strlen(docname) + 1 > MAX_NAME) {
    fprintf(stderr, "erro: o nome do documento eh muito longo\n");
    return -1;
  }

  //cria ponteiros pro doc e pra lib
  FILE *doc = fopen(docname, "rb");
  if (!doc) {
    perror("erro: falha ao abrir arquivo");
    return -1;
  }

  FILE *f_lib = fopen(archive, "rb+");
  if (!f_lib) {
    perror("erro: falha ao abrir arquivo");
    fclose(doc);
    return -1;
  }

  //le o super bloco
  bloco sb;
  if (fread(&sb, sizeof(bloco), 1, f_lib) != 1) { 
    perror("erro: falha ao ler arquivo");
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  //caso haja substituto, remove ele e reaproveita o espaco p inserir outro 
  int id;
  if (gbv_finder(lib, docname, &id) == 0) 
    gbv_remove(lib, archive, docname); 
  else { //caso n tenha substituto tem q realocar
    Document *rlc = realloc(lib -> docs, sizeof(Document) * (lib -> count + 1));
    if (!rlc) {
      perror("erro: falta de memoria");
      fclose(doc);
      fclose(f_lib); 
      return -1;
    }
    lib -> docs = rlc;
  }

  if (gbv_data(lib, lib -> count, doc, docname, sb.offset)) {
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  //coloca o ponteiro da lib no comeco do diretorio p/ inserir o doc
  fseek(f_lib, sb.offset, SEEK_SET);
  
  //escreve o doc na lib
  if (gbv_writer(f_lib, doc)) {
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  //atualiza o super bloco
  sb.qtd = lib -> count;
  sb.offset = ftell(f_lib);

  //atualiza o endereco do diretorio
  if (fwrite(lib -> docs, sizeof(Document), lib -> count, f_lib) != lib -> count) {
    perror("erro: falha ao escrever no arquivo");
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  //coloca o sb atualizado de novo
  rewind(f_lib);
  if (fwrite(&sb, sizeof(bloco), 1, f_lib) != 1) {
    perror("erro: falha ao escrever no arquivo");
    fclose(doc);
    fclose(f_lib);
    return -1;
  }
  
  fclose(doc);
  fclose(f_lib);
  return 0;
}

// remove substituto
int gbv_remove(Library *lib, const char *archive, const char *docname) {
  if (!lib || !docname) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  int id;
  if (gbv_finder(lib, docname, &id) != 0)
    return 1; //nao acho o arquivo af

  // remove o metadado da memoria
  for (int i = id; i < lib -> count - 1; i++) {
      lib -> docs[i] = lib -> docs[i + 1];
  }
  
  lib -> count--;

  //abre var global de novo (?)
  FILE *f_lib = fopen(archive, "rb+");
  if (!f_lib) {
    perror("erro: falha ao abrir arquivo");
    return -1;
  }

  //le o super bloco
  bloco sb;
  if (fread(&sb, sizeof(bloco), 1, f_lib) != 1) { 
    perror("erro: falha ao ler arquivo");
    fclose(f_lib);
    return -1;
  }

  //atualiza so o sb.qtd, sb.offset mantem ja q removemos
  sb.qtd = lib -> count;

  //coloca ponteiro pro diretorio p atualizar o diretorio
  fseek(f_lib, sb.offset, SEEK_SET);

  //atualiza o endereco do diretorio
  if (fwrite(lib -> docs, sizeof(Document), lib -> count, f_lib) != lib -> count) {
    perror("erro: falha ao escrever no arquivo");
    fclose(f_lib);
    return -1;
  }

  //coloca o sb atualizado de novo
  rewind(f_lib);
  if (fwrite(&sb, sizeof(bloco), 1, f_lib) != 1) {
    perror("erro: falha ao escrever no arquivo");
    fclose(f_lib);
    return -1;
  }

  fclose(f_lib);
  return 0;
}

int gbv_list(const Library *lib) {
  if (!lib) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  if (!lib -> count) {
    printf("Biblioteca vazia.\n");
    return 1;
  }

  char data[24];

  printf("\nDocumentos presentes na biblioteca:\n\n");
  printf("%-20s | %-10s | %-20s | %s\n", "Nome", "Tamanho", "Data de Insercao", "Posicao");
  printf("-------------------------------------------------------------------\n");

  for (int i = 0; i < lib -> count; i++) {
    format_date(lib -> docs[i].date, data, sizeof(data));
    printf("%-20s | %-10ld | %-20s | %ld\n", lib -> docs[i].name, lib -> docs[i].size, data, lib -> docs[i].offset);
  }

  return 0;
}

int gbv_view(const Library *lib, const char *archive, const char *docname) {
  if (!lib || !docname)
    return -1;  
  
  int id;
  if (gbv_finder(lib, docname, &id)) {
    printf("Este documento nao esta presente\n");
    return -1;
  }

  // abre var global pq deu problema
  FILE *f_lib = fopen(archive, "rb");
  if (!f_lib) {
    perror("erro: falha ao criar arquivo");
    return -1;
  }

  Document *doc = &lib -> docs[id];
  int ptr = doc -> offset; //ptr do doc, comeca no comeco 
  int end = ptr + doc -> size; //fim do doc
  //buffer pra ler conteudo por isso  cont
  char cont[BUFFER_SIZE];
  int mover = 1;
  char opcao;
  int restante;
  int ler;
  int qtd;

  //ponteiro p ler o comeco do doc
  fseek(f_lib, ptr, SEEK_SET);

  while (1) {
    if (mover) {
      restante = end - ptr;

      if (restante > BUFFER_SIZE)
        ler = BUFFER_SIZE;
      else
        ler = restante;

      if (ler) {
        fseek(f_lib, ptr, SEEK_SET);
        qtd = fread(cont, 1, ler, f_lib);
        if (qtd) {
          printf("\n\n");
          if (fwrite(cont, 1, qtd, stdout) < (size_t)qtd) {
            fclose(f_lib);
            return -1;
          }
          printf("\n\n--- Bloco: %ld de %ld bytes ---", ptr - doc -> offset + qtd, doc -> size);
          if (ptr - doc -> offset + qtd == doc -> size)
            printf(" (ultimo bloco)");
        }
      }
      else
        printf("fim do doc");
    }

    printf("\n(p) <anterior>, (n) <proximo>, (q) <sair>\n");

    scanf(" %c", &opcao);

    if (opcao == 'q') {
      break; 
    }

    if (opcao == 'n') {
      if (ptr + BUFFER_SIZE < end) {
        ptr = ptr + BUFFER_SIZE;
        mover = 1;
      }
    }

    else if (opcao == 'p') {
      if (ptr - BUFFER_SIZE >= doc -> offset) {
        ptr = ptr - BUFFER_SIZE;
        mover = 1;
      }
      else 
        ptr = doc -> offset; // volta pro comeco
    }

    else {
      mover = 0;
      printf("\nOpcao invalida, digite: ");
    }
  }  

  fclose(f_lib);
  return 0;
}

