#include<stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t pid;
  int status; //usada pelo wait
  int i=0;

while(i<10 && (pid=fork())==0){
    printf("filho %d   pid: %d\n",i,getpid());
    fork();
      _exit(i);

i++;
}

  return 0;
}
