#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */ 
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include<stdlib.h>
#define BUFFER_SIZE 1024

ssize_t readln(int fd, char *buf, size_t size){
ssize_t res =0;
int i=0;
while(i<size && (res = read(fd,&buf[i],1))>0){
	if(buf[i]=='\n'){
		i+=res;

		return i;
	}
	i+=res;
}
return i;
}

int main(){

	ssize_t tamanho;
	int fd = open("tmp_ex3", O_RDONLY , 0600);

	char* buffer = malloc(sizeof(char)*BUFFER_SIZE);

	while((tamanho=readln(fd,buffer,BUFFER_SIZE))>0){
	write(1,buffer,tamanho);

}

close(fd);
free(buffer);


	return 0;

}