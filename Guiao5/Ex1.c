#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
int p[2];
char line[] = "linha1\n";
char buffer[20];
int status;

if(pipe(p)==-1){
  perror("Pipe não foi criado.");
  return -1;
}

  switch(fork()){
    case -1:
        perror("Fork não foi efetuado");
        return -1;
    case 0:
        //codigo do filho
        close(p[1]);

        read(p[0], &buffer,sizeof(buffer));
        printf("FILHO: Li do pipe a mensagem: %s \n",buffer);

        close(p[0]);

        _exit(0);

    default:
        //codigo pai
        close(p[0]);

        write(p[1],&line,sizeof(line));
        printf("PAI: escrevi no pipe\n");

        close(p[1]);

        wait(&status);
  }
  return 0;
}
