#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

#define MAX_LINE_SIZE 1024
#define MAX_COMMANDS


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

int main(int argc, char* argv[]){

char buffer[MAX_LINE_SIZE];
char* commands[MAX_COMMANDS];
char* command;
char* line;
int n;
int pipes[MAX_COMMANDS-1][2];
int number_of_commands;
int status[MAX_COMMANDS];

//ler comando no stdin
n=read(0,buffer,MAX_LINE_SIZE);

//remover \n
buffer[n-1]='\0';

//ciclo para estar continuamente a ler do stdin
//acaba em EOF ou quando chamarmos o _exit
while(n>0 && strcmp(buffer,"exit"!=0){
  if(n>1){
    //parsing dos comandos
    line=strdup(buffer);
    number_of_commands=0;

    //usamos o strsep para separar os comandos como delimitador "|"
    for(number_of_commands=0;(command=strsep(&line,"|"))!=NULL; number_of_commands++){
      commands[number_of_commands]=strdup(command);
    }

    //caso 1: só temos 1 comando
    if(number_of_commands==1){
      switch(fork()){
        case -1:
          perror("Fork not made.");
          return -1;

        case 0:
          //código filhos
          //nao precisamos de redirecionar nada(a nao ser que tenha sido especificamentepassado pelo comando)
          exec_command(comands[0]);
          _exit(0);
      }
    }
    else{
      //caso 2: temos multiplos comandos
      for(int c=0;c<number_of_commandsc++){
        //Caso 2.1: processo inicial - nao redireciona stdin
      if(c==0){
        //Criar pipe que vai ligar os processos c e c+1
        if(pipe(pipes[c])!=0){
          perror("Pipe not created.");
          return -1;
        }
        //criar processo filho
        switch(fork()){
          case -1:
            perror("Fork not mande.")
            return -1;
          case 0:
            //código filho
            //fechar extremo de leitura no filho
            close(pipes[c][0]);

            //Ligar stdout do primeiro comando ao extremo de escrita do primeiro pipe
            dup2(pipes[c][1],1);
            close(pipes[c][1]);

            //executar comando
            exec_command(commands[c]);
            _exit(0);
          default:
            //codigo pai
            //fechar o extremo de escrita no Pai
            close(pipes[c][1]);

      }

      //caso 2.2: processo terminal - nao redireciona stdout
    } else if(c==number_of_commands-1){
      //criar processo filho
      switch(fork()){
        case -1:
          perror("Fork not made.");
          return -1;
        case 0:
          //codigo filho
          //É boa politica verificar se ocorrem erros!
          //TODO: experimentar descomentar este close para ver o erro.
          //Explicacao: este descritor ja tinha sido fechado pelo Pai
          //if(close(pipes[c-1][1] != 0){perror("close erros");}

          //Ligar stdin do comando ao extremo de leitura do pipe(criado pelo processo anterior)
          dup2(pipes[c-1][0],0);
          close(pipes[c-1][0]);

          //executar comandos
          exec_command(commads[c]);
          _exit(0);
        default:
          //codigo Pai//fechar o extremo de escrita no Pai
          close(pipes[c-1][0]);

      }
      caso 2.3 processo do meio -redireciona stdin e stdout
    }else{
      //criar o pipe que vai ligar os processos c e c+1
      if(pipe(pipes[c])!=0){
        perror("Pipe not created.");
        return -1;
      }
      //criar processo filho
      swtich(fork()){
        case -1:
          perror("Fork not made.");
          return -1;
        case 0:
          //codigo filho
          //fechar o extremo de leitura no filho(do pipe que cabaei de criar - sou produtor)
          close(pipes[c][0]);

          //ligar o stdout do comando ao extremo de escrita do pipe(que acabei de criar- sou produtor)
          dup2(pipes[c][1],1);
          close(pipes[c][1]);

          //ligar o stdin do comando ao extremo de leitura do pipe anterior- sou consumidor

          dup2(pipes[c-1][0],0);
          close(pipes)
      }
    }






  }
}


}
