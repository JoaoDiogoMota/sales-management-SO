#include <unistd.h>
#include<fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>



int mysystem(char* command){ //EXERCICIO DO GUIAO ANTERIOR
  char* exec_args[20];
  char* string;
  int i=0;

  string =strtok(command," ");

  while(string!=NULL){
    exec_args[i] = string;
    string = strtok(NULL," ");
    i++;
  }

  exec_args[i]=NULL;

  pid_t pid;
  int exec_ret;
  int status;
  int return_value;

  if((pid=fork())==0){
    exec_ret= execvp(exec_args[0],exec_args);
    _exit(exec_ret);
  }
  else{
    if(pid!=-1){
      pid_t terminated_pid =wait(&status);
      if(WIFEXITED(status)){
        return_value=WEXITSTATUS(status);
      } else{
        return_value = -1;
      }
    }else{
      return_value=-1;
    }
  }

  return 0;
}




int main(int argc, char* argv[]){
  int res =0;
  int commandinex=1;
  char command[1024];
  int input_fd;
  int output_fd;

  setbuf(stdout,NULL);

  //redirecionar stdin
  if(strcmp(argv[commandinex],"-i")==0){
    input_fd = open(argv[commandinex+1],O_RDONLY);
    res = dup2(input_fd,0);
    close(input_fd);
    commandinex+=2;
  }

  //redirecionar stdout
  if(strcmp(argv[commandinex],"-o")==0){
    output_fd = open(arv[commandinex+1],O_CREAT | O_TRUNC | _WRONLY);
    res=dup2(output_fd,1);
    close(output_fd);
    commandinex+=2;
  }

  bzero(command,2014); //limpar o que está em memoria
  while(commandinex<argc){
    strcat(command,argv[commandinex]);
    strcat(command," ");
    commandinex++;
  }

  mysystem(command);
  return 0;
}
