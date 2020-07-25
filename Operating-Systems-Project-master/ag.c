#include "ag.h"
#define TAM 1024

/**
 * lê uma linha do file descriptor
 * @param fildes - File Descriptor
 * @param buf - Buffer para armazenação
 * @param nbyte - tamanho do buffer
 * @return size_t - numero de bytes lidos
 */
int readline(int fildes, char *buf, int nbyte){
  int lidos = 0, i = 1;
  char c = 0;

  while (i && lidos < nbyte && c != '\n'){
    i = read(fildes, &c, 1);
    if (i){
      buf[lidos] = c;
      lidos++;
    }
    if(c == '\0') break;
  }
  buf[lidos-1]='\0';


return lidos;
}


/**
 * verifica se uma string se encontra numa lista de strings
 * @param m - string
 * @param buf - lista de strings
 * @return int - 0 se FALSE; 1 caso contrário
 */

int contain(char* m , char** buf){
  int i;
  int ver = 0;
  for(i = 0; buf[i] != NULL; i++){
    if(strcmp(m,buf[i]) == 0) ver = 1;
  }
  return ver;
}


/**
 * agrega todas as vendas até à data por artigo
 * guarda em "buffer" o código de cada artigo, bem como os montantes totais e quantidades totais de artigo adquirido
 */

void agregador(){

  time_t curtime;
  time(&curtime);
  char buffer[80];
  struct tm * timeinfo;

  timeinfo = localtime(&curtime);
  strftime (buffer, 80,"%Y-%m-%dT%H:%M:%S.txt",timeinfo);

  int agreg = open(buffer,O_CREAT | O_RDWR | O_APPEND, 0666);

  if (agreg == -1){
     printf("Erro ao abrir o ficheiro %s \n",buffer);
     exit(-1);
  }


  int fp = open("VENDAS.txt",O_RDONLY, 0600);

  if (fp == -1){
    printf("Erro ao abrir o ficheiro 'Vendas.txt'\n");
    exit(-1);
  }

  char buf[TAM];
  char bf[TAM];
  char** buf2 = malloc(100*sizeof(char*));
  for(int i = 0; i < 100; i++)
    buf2[i] = 0;
  int l;
  int l2;
  off_t ultimapos = 0;
  char* cod;
  int codigo = 0;

  while((l = readline(fp,buf,TAM)) > 0){
    int quantidade = 0;
    int montante = 0;
    ultimapos += l;
    cod = strtok(buf," ");
   if(contain(cod,buf2)==0){
     buf2[codigo] = strdup(cod);
     lseek(fp,0,SEEK_SET);

     while((l2 = readline(fp,bf,TAM)) > 0){
       char** cod2 = malloc(3*sizeof(char*));
       int j = 0;
       cod2[j] = strtok(bf," ");

       if(strcmp(buf2[codigo],cod2[j])==0){

         while (cod2[j] != NULL){
           j++;
           cod2[j] = strtok(NULL," ");
         }
         quantidade += atoi(cod2[1]);
         montante += atoi(cod2[2]);
       }

       free(cod2);
     }
     char *stringDestino = malloc(22*sizeof(char));
     sprintf(stringDestino,"%s %07d %07d",buf2[codigo],quantidade,montante);
     write(agreg,stringDestino,strlen(stringDestino));
     write(agreg,"\n",1);
     codigo++;
     lseek(fp,ultimapos,SEEK_SET);
   }
 }
 free(buf2);
 close(fp);
 close(agreg);
}


int main(){

  agregador();
  return 0;
}
