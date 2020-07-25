#include <unistd.h>
#include<stdio.h>

int main(int argc, char** argv){
int ret;
char* exec_args[] = {"/bin/ls","-l",NULL}; //Para o execv

// printf("mesg 1\n"); PARA TESTE

//ret=execl("/bin/ls","/bin/ls","-l",NULL);
//ret=execlp("ls","/bin/ls","-l",NULL);
ret=execv(exec_args[0],exec_args);

// printf("mesg 2\n"); PARA TESTE
  return 0;
}

//so imprime o primeiro print porque troca o programa atual
