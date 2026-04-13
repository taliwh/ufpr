#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int qtd; //qtd de docs q tem
  long offset; //aponta pro comeco do diretorio: superbloco | dados | diretorio(metadado?)
} bloco; //qual o nome disso ..
 
int gbv_create(const char *filename) {
  FILE *f = fopen(filename, "wb");
  if (!f)
    return 1;

  bloco sb;
  sb.qtd = 0;
  sb.offset = sizeof(sb); //o comeco do diretorio vai ser dps do sb

  if (!fwrite(&sb, sizeof(sb), 1, f)) {       //escreveu o sb ali no arq
    fclose(f);
    return 1;
  }

  fclose(f);
  return 0;
}

int gbv_open(Library *lib, const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (!f) { 
    if (gbv_create(filename)) //se n conseguiu criar, tenta criar de nv
      return 1;
    f = fopen(filename, "rb") //se n conseguiu abrir nem oq criou, ai ja era
    if (!f)
      return 1;
  }

  bloco sb; //sb de superbloco(?)

  if (fread(&sb, sizeof(sb), 1, f) != 1) { //verifica se conseguiu ler  o sb 
    fclose(f);
    return 1;
  }

  lib -> count = sb.qtd; //pega qtd de doc

  if (sb.qtd) { //se nao ta vazio
    lib -> docs = malloc(sizeof(Document) * sb.qtd); //aloca os docs
    if (!lib->docs) {
      fclose(f);
      return 1;
    }
    fseek(f, sb.offset, SEEK_SET); //aponta pra onde deve ficar os documentos a serem lidos
    if (fread(lib -> docs, sizeof(Document), sb.qtd, f) != sb.qtd) { // coloca os docs do arq dentro da lib
      free(lib->docs);
      fclose(f);
      return 1;
    }
  }
  else
    lib -> docs = NULL;

  fclose(f);
  return 0;
}

int gbv_add(Library *lib, const char *archive, const char *docname) {
  FILE *f = fopen(archive, "rb");
  if (!f)
    return 1;

  FILE *ptr //ponteiro q indica onde q ta o comeco io
  FILE *read; //ponvo aindanaoentendi

  bloco sb;
  if (fread(&sb, sizeof(bloco), 1, f) != 1) { //ve se consegue ler o sb pra gente usa dps
    fclose(f);
    return 1;
  }

  fseek(ptr, sb.offset, SEEK_SET); //aponta p comeco do diretorio




}




int gbv_remove(Library *lib, const char *docname)
int gbv_list(const Library *lib)
int gbv_view(const Library *lib, const char *docname)
int gbv_order(Library *lib, const char *archive, const char *criteria)
