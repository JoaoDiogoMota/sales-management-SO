#include "sv.h"

/**
 * ação que vai ser tomada aquando da receção do sinal
 * vai terminar o processo, pois encontrou um end-of-file
 * @param int - sinal recebido na função
 */
void trataINT(int i){
    if(i == SIGINT){
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
 * cria um pipe com nome que vai estabelecer contacto com os clientes
 * executa as ações de visualização de stock e preço, bem como atualização do stock, registando Vendas
 * executa o agregador
 */
void iniciaServidor(){

  char bf[TAM];
  char *c[3];
  off_t ultimapos = 0;
  int l;

  int st = open("stocks.txt", O_CREAT | O_RDWR | O_APPEND, 0600);

  if (st == -1){
      perror("Erro ao abrir o ficheiro 'Stocks.txt' \n");
      exit(-1);
  }

  int at = open("artigos.txt",O_RDONLY, 0600);

  if (at == -1){
      perror("Erro ao abrir o ficheiro 'Artigos.txt' \n");
      exit(-1);
  }

  while((l = readline(at,bf,TAM)) > 0) {
    int i = 0;
    ultimapos += l;
    c[i] = strtok(bf," ");

    while (c[i] != NULL){
      i++;
      c[i] = strtok(NULL," ");
    }

    off_t ultimapos2 = 0;
    int ve, r = 0;
    char bf2[TAM];
    char** ver = malloc(2*sizeof(char*));

    lseek(st,0,SEEK_SET);
    while((ve = readline(st,bf2,TAM)) > 0){
      int ind = 0;
      ultimapos2 += ve;
      ver[ind] = strtok(bf2," ");

      if(strcmp(ver[0],c[0])==0) r = 1;
    }
    if(r == 0){
      char* stringDest = malloc(10*sizeof(char));
      sprintf(stringDest,"%s %d\n",c[0],100);
      write(st,stringDest,strlen(stringDest));
      free(stringDest);
    }
  }

  char * myfifo = "myfifo";
  mkfifo(myfifo, 0666); /** cria um pipe com o nome myfifo */

  char buf[80];

  int log = open("log.txt",O_CREAT | O_WRONLY, 0666); /** cria ficheiro log.txt onde vai guardar os nomes dados pelos clientes */

  int fp = open(myfifo, O_RDONLY,0666); /** abre-se extremo de leitura */

  if(fp == -1){
    perror("Erro a abrir o pipe myfifo\n");
    exit(-1);
  }

  printf("Opened fifo for reading\n");

  int n;


  while(1){

    if((n = readline(fp,buf,sizeof(buf))) > 0){/** lê do fifo para escrever no log.txt */
      close(fp);
      int fp = open(myfifo, O_RDONLY,0666);
      write(log,buf,n);
      //close(log);

      char** receive = malloc(3*sizeof(char*)); /** vai guardar os dados que recebe da ligação */
      int index = 0;
      receive[index] = strtok(buf," ");
      while(receive[index] != NULL){
        index++;
        receive[index] = strtok(NULL," ");
      }

      int x = fork();
      if (x == 0){
        if(strcmp(receive[0],"Estabeleceligação") == 0){
          printf("%s %s %s\n",receive[0],receive[1],receive[2]);
          int wp = open(receive[1], O_WRONLY,0666); /** abre-se extremo de escrita */

          if (wp == -1){
            perror("Erro a abrir o pipe de escrita\n");
            exit(-1);
          }

          int rp = open(receive[2], O_RDONLY, 0666); /** abre-se extremo de leitura */
          if (rp == -1){
            perror("Erro a abrir o pipe de leitura\n");
            exit(-1);
          }
          int m, t;
          off_t ultimaposS = 0;
          char buffer[TAM];
          char recebe[20];
          while((t = readline(rp,recebe,sizeof(recebe))) > 0){

            char** elementos = malloc(2*sizeof(char*)); /** vai guardar os dados que recebe da ligação */
            int indice = 0;
            elementos[indice] = strtok(recebe," ");
            while(elementos[indice] != NULL){
              indice++;
              elementos[indice] = strtok(NULL," ");
            }

            if (strcmp(elementos[0], "a") == 0){
              int x = fork();

              if(x == 0){
                  execlp("./ag","./ag",NULL);
              }
              int status;
              wait(&status);

            }
          else{

           if (elementos[1] == NULL){  /** se só recebe o código do artigo */
              int sto = open("stocks.txt", O_RDONLY, 0600);
              while((m = readline(sto,buffer,TAM)) > 0){
                ultimaposS += m;
                char** ar = malloc(2*sizeof(char*));
                int index = 0;
                ar[index] = strtok(buffer," ");
                while (ar[index] != NULL){
                  index++;
                  ar[index] = strtok(NULL," ");
                }

                if (strcmp(elementos[0],ar[0]) == 0){
                    char* stock;
                    stock = strdup(ar[1]);
                    char stringS[12];
                    sprintf(stringS,"Stock: %s\n",stock);
                    write(wp,stringS,strlen(stringS));
                    ultimaposS = lseek(sto,0,SEEK_SET);
                    free(ar);
                    close(sto);
                    break;
                }
              }
              int s;
              off_t ultimaposP = 0;
              char bufa[TAM];
              int artig = open("artigos.txt", O_RDONLY, 0666);
              while((s = readline(artig,bufa,TAM)) > 0){
                ultimaposP += s;
                char** pr = malloc(3*sizeof(char*));
                int j = 0;
                pr[j] = strtok(bufa, " ");
                while(pr[j] != NULL){
                  j++;
                  pr[j] = strtok(NULL," ");
                }
                if (strcmp(elementos[0],pr[0]) == 0){

                  char* preco;
                  preco = strdup(pr[2]);
                  char stringP[14];
                  sprintf(stringP,"Preço: %s\n",preco);
                  write(wp,stringP,strlen(stringP));
                  ultimaposP = lseek(artig,0,SEEK_SET);
                  free(pr);
                  free(preco);
                  close(artig);
                  break;
                }
              }
            }
            else{
               int h;
               char buffer2[TAM];
               off_t ultimapos2 = 0;
               char *verify[3];
               int ati = open("artigos.txt",O_RDONLY, 0600);
               while((h = readline(ati,buffer2,TAM)) > 0){
                 if (ati == -1){
                     perror("Erro ao abrir o ficheiro 'Artigos.txt' \n");
                     exit(-1);
                 }
                 int ind2 = 0;
                 ultimapos2 += h;
                 verify[ind2] = strtok(buffer2," ");
                 while (verify[ind2] != NULL){
                   ind2++;
                   verify[ind2] = strtok(NULL," ");
                 }
                 if(strcmp(verify[0],elementos[0]) == 0){
                   int v = open("vendas.txt",O_CREAT | O_RDWR | O_APPEND, 0600);
                   if (v == -1){
                     perror("Erro ao abrir o ficheiro 'Vendas.txt'\n");
                     exit(-1);
                   }
                   int preco = atoi(verify[2]);
                   int quant = atoi(elementos[1]);
                   int total = preco * quant;
                   char* stringDestino2 = malloc(10*sizeof(char));
                   sprintf(stringDestino2,"%s %03d %04d\n",elementos[0],quant,total);
                   write(v,stringDestino2,strlen(stringDestino2));
                   close(v);
                   free(stringDestino2);
                   break;
                 }
               }
               lseek(at,0,SEEK_SET);

              int r;
              char buf2[TAM];
              off_t ultimapos = 0;
              lseek(st,0,SEEK_SET);
              while((r = readline(st,buf2,TAM)) > 0){
                ultimapos += r;
                char** qt = malloc(2*sizeof(char*));
                int stoc = 0;
                qt[stoc] = strtok(buf2," ");
                while(qt[stoc] != NULL){
                  stoc++;
                  qt[stoc] = strtok(NULL," ");
                }

                if(strcmp(elementos[0],qt[0]) == 0){
                  int sto = open("stocks.txt", O_WRONLY, 0666);

                  off_t nov = lseek(sto,(long)(ultimapos-r+5),SEEK_SET);

                  if (nov == -1){
                    printf("Erro no lseek nov\n");
                  }

                  char quant[5];
                  int quantidade = atoi(qt[1]) + atoi(elementos[1]);

                  sprintf(quant,"%03d",quantidade);
                  char stringSA[25];
                  sprintf(stringSA,"Stock Atualizado: %s\n",quant);
                  write(wp,stringSA,strlen(stringSA));
                  write(sto,quant,strlen(quant));
                  write(sto,"\n",1);

                  nov = lseek(sto,0,SEEK_SET);
                  ultimapos = lseek(sto,0,SEEK_SET);
                  close(sto);
                  free(qt);

                  break;
                }
              }

              }
            }
          }
        }
    }

    }

    else break;

  }

  unlink(myfifo);

  close(fp); /** fecha extremo de leitura */

  exit(1);
}


int main(){

  signal(SIGINT,trataINT);

  iniciaServidor();

  return 0;
}
