#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>
//ESTA A CORRER MAL

int main(){
  pid_t pid;
  int status; //usada pelo wait
  int i=0;
  while(i<10){
      if((pid=fork())==0){
      printf("filho %d   pid: %d\n",i,getpid());
      _exit(i);
    }
i++;
}
    while(i<10){
      pid_t tP = wait(&status);

      if(WIFEXITED(status)){
      printf("Pai:processo %d exited. exit code: %d\n",tP,WEXITSTATUS(status));
    }else{
     printf("pai processo %d exited\n",tP);
   }
  }
  return 0;
}
