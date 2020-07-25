#include <unistd.h> 
#include <sys/wait.h>
#include<stdio.h>
/* chamadas ao sistema: defs e decls essenciais */
/* chamadas wait*() e macros relacionadas */


int main(){
	printf("pid-- %d\n", getpid());
	printf("pid pai -- %d\n",getppid()); 

	sleep(10);
	return 0;
}


