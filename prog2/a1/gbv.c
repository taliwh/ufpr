#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int qtd; 
  long offset; //diretorio(metadado?)
} bloco; 

//funcoes AUXILIARES

int gbv_finder(Library *lib, const char *docname, int *id) {
  if (!lib || !docname) {
    printf("erro: parametros nulos\n");
    return 1;
  }

  for(int i = 0; i < lib -> count; i++)
    if(!strcmp(lib -> docs[i].name, docname)) {
      *id = i;
      return 0;
    }

  return -1;
}

int gbv_data(Library *lib, int i, FILE *doc, const char *docname, long offset) {
  if (!lib || !docname) {
    printf("erro: parametros nulos\n");
    return 1;
  }

  fseek(doc, 0, SEEK_END);

  strcpy(lib -> docs[i].name, docname); 
  lib -> docs[i].size = ftell(doc);     
  lib -> docs[i].offset = offset;     
  lib -> docs[i].date = time(NULL); 
  
  rewind(doc);
  return 0;
}

// escreve o doc na lib
int gbv_writer(FILE *f_lib, FILE *doc) {
  if (!f_lib || !doc) {
    printf("erro: parametros nulos\n");
    return 1;
  }

  char cont[BUFFER_SIZE]; //buffer q armazena
  size_t qtd; //qtd de coisa lida do doc;

  while ((qtd = fread(cont, 1, sizeof(cont), doc)) > 0)
    if (fwrite(cont, 1, qtd, f_lib) != qtd) {
      perror("erro: falha ao escrever no arquivo");
      return 1;
    }
  
  if (!feof(doc)) {   //caso o fread dentro do while tenha dado erro
    perror("erro: falha ao ler o arquivo");
    return 1;
  }

  return 0;
}

int gbv_create(const char *filename) {
  FILE *f = fopen(filename, "wb");
  if (!f) {
    perror("erro: falha ao abrir arquivo");
    return 1;
  }

  bloco sb;
  sb.qtd = 0;
  sb.offset = sizeof(sb); 

  if (!fwrite(&sb, sizeof(sb), 1, f)) {   
    perror("erro: falha ao escrever no arquivo");
    fclose(f);
    return 1;
  }

  fclose(f);
  return 0;
}

int gbv_open(Library *lib, const char *filename) {
  if (!lib || !filename) {
    printf("erro: parametros nulos\n");
    return 1;
  }

  FILE *f = fopen(filename, "rb");
  if (!f) { 
    if (gbv_create(filename)) { //se n conseguiu criar, tenta criar de nv
      perror("erro: falha ao criar arquivo");
      return 1;
    }
    f = fopen(filename, "rb"); //se n conseguiu abrir nem oq criou, ai ja era
    if (!f) {
      perror("erro: falha ao abrir arquivo");
      return 1;
    }
  }

  bloco sb; 
  if (fread(&sb, sizeof(sb), 1, f) != 1) { //verifica se conseguiu ler  o sb 
    perror("erro: falha ao ler");
    fclose(f);
    return 1;
  }

  lib -> count = sb.qtd; //pega qtd de doc

  if (sb.qtd) { //se nao ta vazio
    lib -> docs = malloc(sizeof(Document) * sb.qtd); //aloca os docs
    if (!lib -> docs) {
      perror("erro: falta de memoria");
      fclose(f);
      return 1;
    }
    fseek(f, sb.offset, SEEK_SET); //aponta pra onde deve ficar os documentos a serem lidos
    if (fread(lib -> docs, sizeof(Document), sb.qtd, f) != sb.qtd) { // coloca os docs do arq dentro da lib
      perror("erro: falha ao ler arquivo");
      free(lib -> docs);
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
  if (!lib || !archive || !docname) {
    printf("erro: parametros nulos\n");
    return 1;
  }
  
  if (strlen(docname) + 1 > MAX_NAME) {
    printf("erro: o nome do documento eh muito longo\n");
    return 1;
  }

  //cria ponteiros pro doc e pra lib
  FILE *doc = fopen(docname, "rb");
  if (!doc) {
    perror("erro: falha ao abrir arquivo");
    return 1;
  }

  FILE *f_lib = fopen(archive, "rb+");
  if (!f_lib) {
    perror("erro: falha ao abrir arquivo");
    fclose(doc);
    return 1;
  }

  //le o super bloco
  bloco sb;
  if (fread(&sb, sizeof(bloco), 1, f_lib) != 1) { 
    perror("erro: falha ao ler arquivo");
    fclose(doc);
    fclose(f_lib);
    return 1;
  }

  //procura se tem um arquivo com mesmo nome
  int i;
  gbv_finder(lib, docname, &i);
  if (i == -1) {
    //aumenta o vetor de docs da lib caso o arquivo seja novo
    Document *rlc = realloc(lib -> docs, sizeof(Document) * (lib -> count + 1));
    if (!rlc) {
      perror("erro: falta de memoria");
      fclose(doc);
      fclose(f_lib); 
      return 1;
    }
    lib -> docs = rlc;
    lib -> count++;
  }

  if (gbv_data(lib, lib->count - 1, doc, docname, sb.offset)) {
    fclose(doc);
    fclose(f_lib);
    return 1;
  }

  //coloca o ponteiro da lib no comeco do diretorio p/ inserir o doc
  fseek(f_lib, sb.offset, SEEK_SET);
  
  //escreve o doc na lib
  if (gbv_writer(f_lib, doc)) {
    fclose(doc);
    fclose(f_lib);
    return 1;
  }

  //atualiza o super bloco
  sb.qtd = lib -> count;
  sb.offset = ftell(f_lib);

  //atualiza o endereco do diretorio
  if (fwrite(lib -> docs, sizeof(Document), lib -> count, f_lib) != lib -> count) {
    perror("erro: falha ao escrever no arquivo");
    fclose(doc);
    fclose(f_lib);
    return 1;
  }

  //coloca o sb atualizado de novo
  rewind(f_lib);
  if (fwrite(&sb, sizeof(bloco), 1, f_lib) != 1) {
    perror("erro: falha ao escrever no arquivo");
    fclose(doc);
    fclose(f_lib);
    return 1;
  }
  
  fclose(doc);
  fclose(f_lib);
  return 0;
}





int gbv_remove(Library *lib, const char *docname)
int gbv_list(const Library *lib)
int gbv_view(const Library *lib, const char *docname)
int gbv_order(Library *lib, const char *archive, const char *criteria)
