#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(int argc, char* argv[]){
int p[2];
char* line[] = {"linha1\n", "linha2\n","linha3\n","linha4\n","linha5\n"};
char buf;
int num_lines=5;
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

        while(read(p[0], &buf,1)>0){
        printf("%c",buf);
}
        close(p[0]);

        _exit(0);

    default:
        //codigo pai
        close(p[0]);

        for(int i=0;i<num_lines;i++){
        write(p[1],line[i],sizeof(line[i]));
        printf("PAI: escrevi no pipe\n");
      }

        close(p[1]);

        wait(&status);
  }
  return 0;
}
