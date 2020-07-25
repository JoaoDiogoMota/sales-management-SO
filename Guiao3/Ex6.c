#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

int mysystem(char* command){
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

int main(int argc, char** argv){
  char comando1[] = "ls -l -a -h";
int ret;

printf("Vou retornar o mysystem para %s\n",comando1 );
ret=mysystem(comando1);
printf("Valor de retorno = %d\n", ret);

return 0;
}
