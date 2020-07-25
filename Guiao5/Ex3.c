#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

#define MAX_LINE_SIZE 1024

//Para ajudar
ssize_t readln(int fildes,void *buf,size_t nbyte){
  ssizete_t res=0;
  int i=0;

  while(i<nbytes && (res=read(fildes,&buf[i],1))>0){
    if(((char*)buf)[i]=='\n'){
      return i+1;
    }
    i+=res;
  }
  return i;
}


int main(int argc, char* argv[]){
  int res=0;
int p[2];
char buffer[MAX_LINE_SIZE];
int pid;
int status;

if(pipe(p)==-1){
  perror("Pipe nao foi criado\n");
  return -1;
}

switch(((pid=fork())==0))){
  case -1:
      perror("FOrk nao foi efetuado.\n");
      return -1;
  case 0:
    //codigo FILHO
    close(p[1]);
    dup2(p[0],0);
    close(p[0]);
    res=execlp("wc","/bin/wc",NULL);
    _exit(0);

  default:
    //codigo pai
    close(p[0]);
    //ctrl+d envia um EOF
    while((res=readln(0,buffer,MAX_LINE_SIZE))>0){
      write(p[1],buffer,res);
    }
    //fechar extremidade de escrita
    close(p[1]);

    wait(&status);
    if(WIFEXITED(status)){
      printf("Pai - filho terminou com %d\n",WEXITEDSTATUS(status));
    }
}
return 0;
}
