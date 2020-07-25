#ifndef MA_H
#define MA_H
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#define TAM 1024

void trataINT(int i);

int readline(int fildes, char *buf, int nbyte);

int numLine(int fp);

void manutencaoArtigos();

#endif
