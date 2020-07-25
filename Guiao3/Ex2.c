#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv){
int ret;
pid_t pid;
int status;

if((pid=fork())==0){
  ret=execl("/bin/ls","/bin/ls","-l",NULL);
}else{ //assumindo que vai correr tudo bem
  pid_t terminated_pid=wait(&status);
  printf("pai: processo %d acabou com o resultado %d\n",terminated_pid,WEXITSTATUS(status));
}

  return 0;
}
