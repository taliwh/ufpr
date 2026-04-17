#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gbv.h"
#include "util.h"

typedef struct {
  int qtd; 
  long offset; //diretorio(metadado?)
} bloco; 

//var global pois deu problema na gbv_view e gbv_remove ...
char libname[MAX_NAME];

//funcoes AUXILIARES

int gbv_finder(const Library *lib, const char *docname, int *id) {
  if (!lib || !docname) {
    fprintf(stderr,"erro: parametros nulos\n");
    return -1;
  }

  for(int i = 0; i < lib -> count; i++)
    if(!strcmp(lib -> docs[i].name, docname)) {
      *id = i;
      return 0;
    }

  return 1;
}

int gbv_data(Library *lib, int i, FILE *doc, const char *docname, long offset) {
  if (!lib || !docname) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  fseek(doc, 0, SEEK_END);

  strcpy(lib -> docs[i].name, docname); 
  lib -> docs[i].size = ftell(doc);     
  lib -> docs[i].offset = offset;     
  lib -> docs[i].date = time(NULL); 
  lib -> count++;
  
  rewind(doc);
  return 0;
}

// escreve o doc na lib
int gbv_writer(FILE *f_lib, FILE *doc) {
  if (!f_lib || !doc) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  char cont[BUFFER_SIZE]; //buffer q armazena contteudo
  size_t qtd; //qtd de coisa lida do doc;

  while ((qtd = fread(cont, 1, sizeof(cont), doc)) > 0)
    if (fwrite(cont, 1, qtd, f_lib) != qtd) {
      perror("erro: falha ao escrever no arquivo");
      return -1;
    }
  
  if (!feof(doc)) {   //caso o fread dentro do while tenha dado erro
    perror("erro: falha ao ler o arquivo");
    return -1;
  }

  return 0;
}

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

  //atualiza var local com a lib
  strcpy(libname, filename);

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
    perror("erro: falha ao ler");
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
    gbv_remove(lib, docname); 
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
int gbv_remove(Library *lib, const char *docname) {
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
  FILE *f_lib = fopen(libname, "rb+");
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

  printf("Documentos presentes na biblioteca:\n");
  printf("%-20s | %-10s | %-20s | %s\n", "Nome", "Tamanho", "Data de Insercao", "Posicao\n");
  printf("----------------------------------------------------------\n");

  for (int i = 0; i < lib -> count; i++) {
    format_date(lib->docs[i].date, data, sizeof(data));
    printf("%-20s | %-10ld | %-20s | %ld\n", lib -> docs[i].name, lib -> docs[i].size, data, lib -> docs[i].offset);
  }

  return 0;
}

int gbv_view(const Library *lib, const char *docname) {
  if (!lib || !docname)
    return -1;  
  
  int id;
  if (gbv_finder(lib, docname, &id)) {
    printf("Este documento nao esta presente\n");
    return -1;
  }

  // abre var global pq deu problema
  FILE *f_lib = fopen(libname, "rb");
  if (!f_lib) {
    perror("erro: falha ao criar arquivo");
    return -1;
  }

  Document *doc = &lib -> docs[id];
  int ptr = doc -> offset; //ptr do doc, comeca no comeco 
  int end = ptr + doc -> size; //fim do doc
  //buffer pra ler conteudo por isso  cont
  char cont[BUFFER_SIZE];
  char opcao;
  int restante;
  int ler;
  int qtd;

  //ponteiro p ler o comeco do doc
  fseek(f_lib, ptr, SEEK_SET);

  while (1) {
    restante = end - ptr;

    if (restante > BUFFER_SIZE)
      ler = BUFFER_SIZE;
    else
      ler = restante;

    if (ler) {
      fseek(f_lib, ptr, SEEK_SET);
      qtd = fread(cont, 1, ler, f_lib);
      if (qtd) {
        if (fwrite(cont, 1, qtd, stdout) < (size_t)qtd) {
          fclose(f_lib);
          return -1;
        }
        printf("\n--- Bloco: %ld de %ld bytes ---\n", ptr - doc -> offset + qtd, doc -> size);
      }
    }
    else
      printf("fim do doc");

    printf("Escolha n, p, q\n");

    scanf(" %c", &opcao);

    if (opcao == 'q') {
      break; 
    }

    if (opcao == 'n') {
      if (ptr + BUFFER_SIZE < end) 
        ptr = ptr + BUFFER_SIZE;
      else 
        printf("Voce ja esta no final.\n");
    } 

    else if (opcao == 'p') 
      if (ptr - BUFFER_SIZE >= doc -> offset) 
        ptr = ptr - BUFFER_SIZE;
      else {
        ptr = doc -> offset; // volta pro comeco
        printf("Voce ja esta no inicio.\n");
      }

    else 
      printf("opcao invalida, digite n p ou q.\n");

  }  

  fclose(f_lib);
  return 0;
}

int gbv_order(Library *lib, const char *archive, const char *criteria) {
  if (!lib || !archive || !criteria) {
    perror("erro: ponteiro invalido"); 
    return -1;
  }

  // 1. Abrir o arquivo de critérios (.txt com a ordem)
  FILE *f = fopen(criteria, "r");
  if (!f) {
      perror("erro: falha ao abrir arquivo de criterios");
      return -1;
  }

  


}