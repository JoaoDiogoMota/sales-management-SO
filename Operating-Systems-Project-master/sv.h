#ifndef SV_H
#define SV_H
#include <unistd.h>   /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>    /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#define TAM 1024

void iniciaServidor();

int readline(int fildes, char *buf, int nbyte);

void criaFicheirosVendas();

#endif
