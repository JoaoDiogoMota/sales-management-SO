#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
typedef void (*sighandler_t)(int);

unsigned int seconds=0;
unsigned int ctrl_c=0;

void sigint_handler(int signum){
ctrl_c++;
printf("received[%d] %ds executing ...\n",signum,seconds);
}

void sigquit_handler(int signum){
  printf("received[%d] called ctrl+c %d times ... \n",signum,ctrl_c);
  _exit(0);
}

void sigalarm_handler(int signum){
  seconds++;
  alarm(1);
}

int main(int argc, char const *argv[]) {
  signal(SIGINT,sigint_handler);
  signal(SIGQUIT,sigquit_handler);
  signal(SIGALRM,sigalarm_handler);

  alarm(1);
  while(1){
    pause();
  printf("Teste\n");
}
  return 0;
}
