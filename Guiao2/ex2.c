#include <unistd.h>
#include <sys/wait.h>
#include<stdio.h>

int main(){
  pid_t pid;
  int i=0;

   if((pid=fork())==0){
     printf("filho %d\n",i);
     printf("filho - pid %d\n",getpid());
     printf("filho - pid pai%d\n",getppid());
     _exit(0); //termina o processo
   }else{
     printf("pai %d\n",i);
     printf("pai - pid filho: \n%d",pid);
     printf("pai - pid %d\n",getpid());
     printf("pai - pid pai%d\n",getppid());
   }
   return 0;
}
