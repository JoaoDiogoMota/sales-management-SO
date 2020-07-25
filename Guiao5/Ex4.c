#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int exec_command(char* command){
  char*exec_args[20];
  char* string;
  int exec_ret = 0;
  int i=0;

  string = strtok(command," ");
  while(string !=NULL){
    exec_args[i]=string;
    string=strtok(NULL," ");
    i++;
  }
  exec_args[i]=NULL;
  exec_ret=execvp(exec_args[0],exec_args);
  return exec_ret;
}


int main(int argc, char* argv[]){ //VERSAO 1 com Pai e Filho
  char command1[] = "ls /etc";
  char command2[] ) "wc -l";


  int p[2];

  int status;


  if(pipe(p)!=0){
    perror("Pipe nao foi criado\n");
    return -1;
  }

  switch(fork()){

    case -1:
        perror("FOrk nao foi efetuado.\n");
        return -1;

    case 0:
        //codigo FILHO
        close(p[0]);
        dup2(p[1],1);
        close(p[1]);
        exec_command(command1);
        _exit(0);

    default:
      //codigo pai
      close(p[1]);
      dup2(p[0],0);
      close(p[0]);

      exec_command(command2);
      close(p[1]);

    wait(&status);
    if(WIFEXITED(status)){
      printf("Pai - filho terminou com %d\n",WEXITEDSTATUS(status));
    }
}
return 0;
}






int main(int argc, char* argv[]){ //VERSAO 2 com dois filhos
  char command1[] = "ls /etc";
  char command2[] ) "wc -l";


  int p[2];
  int p2[2];

  int status[2];


  if(pipe(p)!=0){
    perror("Pipe nao foi criado\n");
    return -1;
  }
    //criar prieiro processo filho
  switch(fork()){
    case -1:
        perror("FOrk nao foi efetuado.\n");
        return -1;

    case 0:
        //codigo FILHO
        close(p[0]);
        dup2(p[1],1);
        close(p[1]);
        exec_command(command1);
        _exit(0);

    default:
      //codigo pai
      close(p[1]);
}

//criar segundo processo filho (o codigo poderia ser dentro do default)
switch(fork()){
  case -1:
      perror("Fork nao foi efetuado.");
      return -1;
  case 0:
      //codigo filhos
      close(p[1]);
      dup2(p[0],0);
      close(p[0]);

      exec_command(command2);
      _exit(0);

    default:
      close(p[0]);
    }
    for(int w=0;w<2;w++){
      wait(&status[w]);
    }

}
return 0;
}
