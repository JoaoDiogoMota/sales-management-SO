#ifndef AG_H
#define AG_H
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAM 1024

int readline(int fildes, char *buf, int nbyte);

int contain(char* m , char** buf);

void agregador();

#endif
