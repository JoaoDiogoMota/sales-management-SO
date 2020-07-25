#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include<stdlib.h>

#define BUFFER_SIZE 1024

int myCat(){
	ssize_t rB=0;
	ssize_t nRB=0;

	/*int fd = open(0, O_RDONLY,0600);

	int nfd = open(1, O_WRONLY,0600);
	*/

	char* buffer = malloc(sizeof(char)*BUFFER_SIZE);

	while((rB = read(0,buffer,BUFFER_SIZE))>0)
		nRB=write(1,buffer,rB);

	return nRB;

}

int main(){
	myCat();
	return 0;
}