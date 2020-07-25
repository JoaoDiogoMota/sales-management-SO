#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t pid;
  int status; //usada pelo wait
  int i=0;

  while(i<10){
    if((pid=fork())==0){
      printf("filho %d\n",i);
      printf("filho - pid %d\n",getpid());
      printf("filho - pid pai %d\n",getppid());
      _exit(i);
    }
    else{
      pid_t tP = wait(&status);
      printf("Processo %d fechado. exit code:%d \n",tP,WEXITSTATUS(status));
    }
    sleep(1);
i++;
  }
  return 0;
}
