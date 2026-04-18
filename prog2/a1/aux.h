#ifndef AUX_H
#define AUX_H

// funcoes auxiliares
int gbv_finder(const Library *lib, const char *docname, int *id);
int gbv_data(Library *lib, int i, FILE *doc, const char *docname, long offset);
int gbv_writer(FILE *f_lib, FILE *doc);

#endif