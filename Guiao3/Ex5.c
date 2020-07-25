#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char** argv){
int exec_ret;
pid_t pid;
int status;

for(int i=1;i<argc;i++){
  if((pid=fork())==0){
    printf("process[%d]: going to execute the command: %s\n",getpid(),argv[i]);
    exec_ret = execlp(argv[i],argv[i], NULL);
    _exit(exec_ret);
  }
}

  for(int i=1;i<argc;i++){
    pid_t terminated_pid = wait(&status);

    if(WIFEXITED(status)){
      printf("[pai] process %d exited with value %d\n",terminated_pid,WEXITSTATUS(status));
    }
    else{
      printf("deu asneira\n");
    }
  }

return 0;
}
