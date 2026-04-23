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

// cria uma lib vazia e escreve o super bloco
int gbv_create(const char *filename) {
  FILE *f = fopen(filename, "wb");
  if (!f) {
    perror("erro: falha ao abrir arquivo");
    return -1;
  }

  // inicializa com {0} para evitar padding com lixo de memoria
  bloco sb = {0};
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

// abre a lib e armazena os documentos
int gbv_open(Library *lib, const char *filename) {
  if (!lib || !filename) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  FILE *f = fopen(filename, "rb");
  if (!f) { 
    // cria a lib caso ela ainda nao exista
    if (gbv_create(filename)) { 
      perror("erro: falha ao criar arquivo");
      return -1;
    }
    // verifica se a lib recem criada pode ser aberta
    f = fopen(filename, "rb"); 
    if (!f) {
      perror("erro: falha ao abrir arquivo");
      return -1;
    }
  }

  bloco sb; 
  if (fread(&sb, sizeof(sb), 1, f) != 1) { 
    perror("erro: falha ao ler arquivo");
    fclose(f);
    return -1;
  }
  
  // atualiza a quantidade de documentos do diretorio
  lib -> count = sb.qtd;

  // se ha documentos, aloca eles dentro da lib
  if (sb.qtd) {
    lib -> docs = calloc(sb.qtd, sizeof(Document)); 
    if (!lib -> docs) {
      perror("erro: falta de memoria");
      fclose(f);
      return -1;
    }

    // aponta pra onde deve ficar os documentos a serem lidos
    fseek(f, sb.offset, SEEK_SET); 

    // armazena os documentos na lib
    if (fread(lib -> docs, sizeof(Document), sb.qtd, f) != sb.qtd) { 
      perror("erro: falha ao ler arquivo");
      free(lib -> docs);
      fclose(f);
      return -1;
    }
  }
  else
    lib -> docs = NULL; 

  fclose(f);
  return 0;
}

// adiciona um novo documento no final da lib
int gbv_add(Library *lib, const char *archive, const char *docname) {
  if (!lib || !archive || !docname) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }
  
  // verifica se o nome desse documento excede o maximo de caracteres
  if (strlen(docname) + 1 > MAX_NAME) {
    fprintf(stderr, "erro: o nome do documento eh muito longo\n");
    return -1;
  }
  
  // previne erro de escrita e leitura infinita
  if (!strcmp(archive, docname)) {
    fprintf(stderr, "erro: nao e possivel inserir a propria biblioteca\n");
    return -1;
  }

  // cria ponteiros pro documento e pra lib
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

  // le o super bloco
  bloco sb;
  if (fread(&sb, sizeof(bloco), 1, f_lib) != 1) { 
    perror("erro: falha ao ler arquivo");
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  // caso haja substituto, remove ele e reaproveita o espaco para inserir outro 
  int id;
  if (gbv_finder(lib, docname, &id) == 0) 
    gbv_remove(lib, archive, docname); 
  else { 

    // caso nao tenha substituto tem q realocar para inserir o novo documento
    Document *rlc = realloc(lib -> docs, sizeof(Document) * (lib -> count + 1));
    if (!rlc) {
      perror("erro: falta de memoria");
      fclose(doc);
      fclose(f_lib); 
      return -1;
    }
    lib -> docs = rlc;
  }

  // inicializa o novo campo
  memset(&lib->docs[lib->count], 0, sizeof(Document));

  // preenche os metadados do novo documento
  if (gbv_data(lib, lib -> count, doc, docname, sb.offset)) {
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  // coloca o ponteiro da lib no comeco do diretorio para inserir o documento
  fseek(f_lib, sb.offset, SEEK_SET);
  
  // escreve o doc na lib
  if (gbv_writer(f_lib, doc)) {
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  // atualiza o super bloco
  sb.qtd = lib -> count;
  sb.offset = ftell(f_lib);

  // atualiza o endereco do diretorio
  if (fwrite(lib -> docs, sizeof(Document), lib -> count, f_lib) != lib -> count) {
    perror("erro: falha ao escrever no arquivo");
    fclose(doc);
    fclose(f_lib);
    return -1;
  }

  // coloca o super bloco atualizado de novo
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

// remove o metadado da memoria
int gbv_remove(Library *lib, const char *archive, const char *docname) {
  if (!lib || !docname) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  // encontra o id do documento que sera retirado
  int id;
  if (gbv_finder(lib, docname, &id) != 0)
    return 1;

  // alinha os docs
  for (int i = id; i < lib -> count - 1; i++) {
      lib -> docs[i] = lib -> docs[i + 1];
  }

  // atualiza a quantidade de docs
  lib -> count--;

  FILE *f_lib = fopen(archive, "rb+");
  if (!f_lib) {
    perror("erro: falha ao abrir arquivo");
    return -1;
  }

  bloco sb;
  if (fread(&sb, sizeof(bloco), 1, f_lib) != 1) { 
    perror("erro: falha ao ler arquivo");
    fclose(f_lib);
    return -1;
  }

  // atualiza so o sb.qtd, sb.offset mantem ja que removemos
  sb.qtd = lib -> count;

  // coloca ponteiro pro diretorio p atualizar o diretorio
  fseek(f_lib, sb.offset, SEEK_SET);

  // atualiza o endereco do diretorio
  if (fwrite(lib -> docs, sizeof(Document), lib -> count, f_lib) != lib -> count) {
    perror("erro: falha ao escrever no arquivo");
    fclose(f_lib);
    return -1;
  }

  // coloca o super bloco atualizado de novo
  rewind(f_lib);
  if (fwrite(&sb, sizeof(bloco), 1, f_lib) != 1) {
    perror("erro: falha ao escrever no arquivo");
    fclose(f_lib);
    return -1;
  }

  fclose(f_lib);
  return 0;
}

// lista os documentos presentes na lib
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

// visualiza o conteudo de um documento da lib
int gbv_view(const Library *lib, const char *archive, const char *docname) {
  if (!lib || !docname)
    return -1;  
  
  // verifica se o documento esta presente
  int id;
  if (gbv_finder(lib, docname, &id)) {
    printf("Este documento nao esta presente\n");
    return -1;
  }

  FILE *f_lib = fopen(archive, "rb");
  if (!f_lib) {
    perror("erro: falha ao criar arquivo");
    return -1;
  }

  Document *doc = &lib -> docs[id];
  size_t qtd;

  // ponteiro do comeco do documento
  long ptr = doc -> offset;
  
  // ponteiro do final do documento
  long end = ptr + doc -> size; 

  // buffer pra ler o conteudo 
  char cont[BUFFER_SIZE];

  // indicador que sinaliza se eh necessario mover o bloco
  int mover = 1;

  // indicador do que ainda falta para ler no documento
  long restante;
  
  char opcao;

  // indicador do que devemos ler no documento
  long ler;

  // ponteiro para ler o comeco do doc
  fseek(f_lib, ptr, SEEK_SET);

  while (1) {
    if (mover) {
      restante = end - ptr;

      // define o que devemos ler no momento, se é o tamanho do buffer ou o resto do arquivo
      if (restante > BUFFER_SIZE)
        ler = BUFFER_SIZE;
      else
        ler = restante;

      if (ler) {

        // aponta o ponteiro da lib (f_lib) para onde o ponteiro do documento esta
        fseek(f_lib, ptr, SEEK_SET);
        qtd = fread(cont, 1, ler, f_lib);

        // mostra na tela o conteudo do documento
        if (qtd) {
          printf("\n\n");
          if (fwrite(cont, 1, qtd, stdout) < qtd) {
            fclose(f_lib);
            return -1;
          }
          printf("\n\n--- Bloco: %ld de %ld bytes ---", ptr - doc -> offset + qtd, doc -> size);
          if (ptr - doc -> offset + qtd == doc -> size)
            printf(" (ultimo bloco)");
        }
      }
    }

    printf("\ndigite: (p) <anterior>, (n) <proximo>, (q) <sair>\n");

    scanf(" %c", &opcao);

    if (opcao == 'q') {
      break; 
    }

    // avanca o ponteiro do documento para o proximo bloco 
    if (opcao == 'n') {

      // verificacao pra nao ultrapassar o final do bloco
      if (ptr + BUFFER_SIZE < end) {
        ptr = ptr + BUFFER_SIZE;
        mover = 1;
      }
    }

    // retrocede o ponteiro do documento para o bloco anterior 
    else if (opcao == 'p') {

      // verificacao pro ponteiro nao ir antes do comeco do documento
      if (ptr - BUFFER_SIZE >= doc -> offset) {
        ptr = ptr - BUFFER_SIZE;
        mover = 1;
      }
      else 
        ptr = doc -> offset; 
    }

    else {
      
      // nao printa de novo o que ja printou, caso a opcao digitada seja invalida
      mover = 0;
      printf("\nOpcao invalida, digite: ");
    }
  }  

  fclose(f_lib);
  return 0;
}

