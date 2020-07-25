#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include<stdlib.h>

#define BUFFER_SIZE 1024
#define FILE_SIZE 10*1024*1024

int mycp(char* nome){
	int res=0;
	ssize_t rB;

	int nfd = open("nTmp_file",O_CREAT | O_WRONLY | O_TRUNC, 0600);

	int fd = open(nome,O_CREAT | O_RDONLY, 0600);

	char* buffer = malloc(sizeof(char)*BUFFER_SIZE);

	for(int i=0;i<FILE_SIZE/BUFFER_SIZE;i++)
		rB=read(fd,buffer,BUFFER_SIZE);
	

	for(int j=0; j<BUFFER_SIZE; j++)
		res+=write(nfd,buffer,rB);
	

	close(fd);
	close(nfd);
	return res;
}


int main(){
	mycp("tmp_file");
	return 0;
}