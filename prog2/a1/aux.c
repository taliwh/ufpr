// funcoes auxiliares usadas em gbv.c

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gbv.h"
#include "aux.h"

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
    perror("erro: falha ao ler arquivo");
    return -1;
  }

  return 0;
}