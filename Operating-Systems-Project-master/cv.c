#include "cv.h"

char* nomeR;
char* nomeW;
int wp, rp;

/**
 * ação que vai ser tomada aquando da receção do sinal
 * vai terminar o processo, pois encontrou um end-of-file
 * @param int - sinal recebido na função
 */
void trataINT(int i){
    if(i == SIGINT){
      unlink(nomeR);
      unlink(nomeW);
      printf("\nReached End Of File, exiting..\n");
      exit(0);
    }
}

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
 * estabelece comunicação entre o cliente e o servidor
 */

void clienteVendas(){
  char buf[80];
  char buffer[80];
  char guarda[80];
  char * myfifo = "myfifo";
  int n,r,p;
  off_t pos = 0;

  int fp = open(myfifo, O_WRONLY,0666); /** abre-se extremo de escrita */

  if (fp == -1){
    perror("Erro a abrir o pipe\n");
    exit(-1);
  }

  printf("Opened fifo for writing\n");

  int log = open("log.txt",O_RDONLY, 0600);
  if (log == -1){
    perror("Erro ao abrir o ficheiro 'log.txt'\n");
    exit(-1);
  }
  int k = 1;
  while(k && (n = readline(0,buf,sizeof(buf))) > 0 ){  /** lê do terminal e escreve no fifo */
        if((r = readline(log,buffer,sizeof(buffer))) > 0){
          pos = lseek(log,0,SEEK_SET);
          r = 0;
          while((p = readline(log,buffer,sizeof(buffer))) > 0 && k){
            char* clien;
            clien = strdup(strtok(buffer," "));
            if(strcmp(buf,buffer) == 0){
              r = 1;
              printf("Insira um código diferente\n");
            }
          }
          if (r == 0){
            printf("Autenticação aceite\n");
            /** vai escrever o nome dos dois fifos que vai criar */
            strcpy(guarda,buf);
            write(fp,guarda,n); 
            k = 0;
          }
        }
        else{
          printf("Autenticação aceite\n");
          
          strcpy(guarda,buf);
          write(fp,guarda,n); 
          k = 0;
        }
        pos = lseek(log,0,SEEK_SET);

      }

  close(log);

  nomeR = strdup(guarda);
  nomeW = strdup(guarda);
  strcat(nomeR,"read");
  strcat(nomeW,"write");

  mkfifo(nomeR,0666); /** cria o pipe para leitura do cliente */
  mkfifo(nomeW,0666); /** cria o pipe para escrita do cliente */

  char* ready = malloc(40*sizeof(char*));

  char* msg = "Estabeleceligação";
  sprintf(ready,"%s %s %s\n",msg,nomeR,nomeW);


  write(fp,ready,strlen(ready)); /** vai enviar a mensagem para o servidor */

  int rp = open(nomeR, O_RDONLY, 0666); /** abre-se extremo de leitura */

  int wp = open(nomeW, O_WRONLY, 0666); /** abre-se o extremo de escrita */


  int x = fork();
  if (x == 0){

    int c;
    char comunica[100];
    while((c = readline(rp,comunica,sizeof(comunica))) > 0){
      write(1,comunica,c);
      write(1,"\n",1);
    }

    unlink(myfifo);
    exit(0);
  }
    int l;
    char term[20];
    while((l = readline(0,term,sizeof(term))) > 0){
      write(wp,term,l);
    }

  close(fp);
  exit(1);
}


int main(int argc, char* argv[]){

  signal(SIGINT,trataINT);

  clienteVendas();

return 0;
}
