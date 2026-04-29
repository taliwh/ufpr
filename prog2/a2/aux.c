// funcoes auxiliares usadas em gbv.c

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gbv.h"
#include "aux.h"

// retorna 0 se conseguiu achar um documento na lib e sinaliza seu indice no vetor
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

// retorna 0 se conseguiu colocar as informacoes do documento em seu metadado
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

// escreve o documento na biblioteca
int gbv_writer(FILE *f_lib, FILE *doc) {
  if (!f_lib || !doc) {
    fprintf(stderr, "erro: parametros nulos\n");
    return -1;
  }

  // buffer para armazenar o conteudo lido do documento
  char cont[BUFFER_SIZE]; 

  // quantidade de coisa a ser lida do documento
  int qtd; 

  while ((qtd = fread(cont, 1, sizeof(cont), doc)) > 0)
    if (fwrite(cont, 1, qtd, f_lib) != qtd) {
      perror("erro: falha ao escrever no arquivo");
      return -1;
    }
  
  // caso o fread do while tenha dado erro
  if (!feof(doc)) {   
    perror("erro: falha ao ler arquivo");
    return -1;
  }

  return 0;
}