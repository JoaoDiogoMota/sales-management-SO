#include "ma.h"

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
 * @return int - numero de bytes lidos
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
 * indica o número de linhas de um file Descriptor
 * @param fp - file descriptor
 * @return int - número de linhas
 */

int numLine(int fp){
  char buffer[TAM];
  int m;
  int n = 0;
  lseek(fp,0,SEEK_SET); /** vai ler desde o início do ficheiro */

  while((m = readline(fp,buffer,TAM)) > 0) {
    n++;
  }

return n;
}


/**
 * adiciona artigos ao inventário do sistema
 * permite alterar os nomes dos artigos, bem como os respetivos preços
 */

void manutencaoArtigos(){

  char buf[TAM];
  off_t ultimapos = 0;

  int fp = open("artigos.txt", O_CREAT | O_RDWR | O_APPEND, 0666);

  if (fp == -1){
      printf("Erro ao abrir o ficheiro 'Artigos.txt' \n");
      exit(-1);
  }

  ultimapos = lseek(fp,0,SEEK_SET);
  if (ultimapos == -1){
    printf("Erro no lseek ultimapos\n");
  }

  int f = open("strings.txt", O_CREAT | O_RDWR | O_APPEND, 0666);

  if (f == -1){
      printf("Erro ao abrir o ficheiro 'Strings.txt' \n");
      exit(-1);
  }

  int n = numLine(fp) + 1;

  while(readline(0,buf,TAM) > 0){
    char* c[3];
    char* token;
    int index = 0;

    token = strtok(buf," ");
    while (token != NULL){
      c[index] = (char*) malloc(20*sizeof(char));
      strcpy(c[index],token);
      token= strtok(NULL," ");
      index++;
    }

    if (buf[0] == 'i'){ /** Inserção de um novo artigo */
      off_t tmp = lseek(f,0,SEEK_CUR);
      if (tmp == -1){
        printf("Erro no lseek tmp\n");
      }
      write(f,c[1],strlen(c[1]));
      write(f,"\n",1);

      char* stringDestino = malloc(20*sizeof(char));

      printf("O código do artigo é: %04d\n",n);
      sprintf(stringDestino,"%04d %06lld %04d",n,tmp,atoi(c[2]));

      write(fp,stringDestino,strlen(stringDestino));
      write(fp,"\n",1);

      n++;

      free(stringDestino);
    }
    else if(buf[0] == 'n'){ /** Alteração do nome de um artigo */
        char buffer[TAM];
        char* art[3];
        lseek(fp,0,SEEK_SET); /** vai ler desde o início do ficheiro */
        int m;
        int r = 0;
      while((m = readline(fp,buffer,TAM)) > 0) {
          int i = 0;
          ultimapos += m;
          buffer[m] = '\0';
          art[i] = strtok(buffer," ");

          while (art[i] != NULL){
            i++;
            art[i] = strtok(NULL," ");
          }

          if(strcmp(art[0],c[1]) == 0){
            r = 1;
            off_t pos = lseek(f,0,SEEK_CUR); /** qual o offset da posição em strings */

            if (pos == -1){
              printf("Erro no lseek pos\n");
            }
            write(f,c[2],strlen(c[2]));
            write(f,"\n",1);

            int teste = open("artigos.txt", O_WRONLY, 0666);

            off_t nov = lseek(teste,(long)(ultimapos-m+5),SEEK_SET);

            if (nov == -1){
              printf("Erro no lseek nov\n");
            }

            char* posi = malloc (3*sizeof(char));
            sprintf(posi,"%06lld",pos);
            write(teste,posi,strlen(posi));

            nov = lseek(teste,0,SEEK_SET);
            ultimapos = lseek(fp,0,SEEK_SET);
            close(teste);
            free(posi);
            break;
          }
        }
        if (r == 0) printf ("Não existe esse código de artigo\n"); /** não encontrou o código */

      }
      else if(buf[0] == 'p'){
        char buffer[TAM]; /** onde se guarda o que se lê do ficheiro ARTIGOS*/
        char* art[3]; /** onde se coloca cada elemento de buffer */
        lseek(fp,0,SEEK_SET); /** vai ler desde o início do ficheiro */
        int m; /** numero de bytes lidos */
        int r = 0; /** se encontrou ou não o código */
        while((m = readline(fp,buffer,TAM)) > 0) {
          int i = 0;
          ultimapos += m;
          buffer[m] = '\0';
          art[i] = strtok(buffer," ");

          while (art[i] != NULL){
            i++;
            art[i] = strtok(NULL," ");
          }

          if(strcmp(art[0],c[1]) == 0){

            r = 1; /** encontrou o código */

            int teste = open("artigos.txt", O_WRONLY, 0666);

            off_t nov = lseek(teste,(long)(ultimapos-m+12),SEEK_SET);

            if (nov == -1){
              printf("Erro no lseek nov\n");
            }

            char precot[7];
            sprintf(precot,"%04d",atoi(c[2]));

            write(teste,precot,strlen(precot));
            write(teste,"\n",1);

            nov = lseek(teste,0,SEEK_SET);
            ultimapos = lseek(fp,0,SEEK_SET);
            close(teste);
            break;
          }
        }
    }
      else printf("Não foi introduzida uma ação correta\n");

  }

  close(fp);
  close(f);

}

int main (int argc, char* argv[]){

  signal(SIGINT,trataINT); /** preparação do processo para a receção de um sinal */

  manutencaoArtigos();

return 0;
}
