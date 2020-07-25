#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_ARG_SIZE 1024

int main(int agrc, char* argv[]){
  char buf[MAX_ARG_SIZE];
  int bytes read;
  int logfile, fd, fd_write;

  //Eu podia

  //open log file for writing
  if((logfile=open("log.txt",O_CREAT | O_TRUNC | O_WRONLY,0600))==-1){
    perror("Open");
    return -1;
  }

  while(1){
    //open named pipe for reading
    if((fd=open("fifo",O_RDONLY))==-1){
      perror("Open");
      return -1;
    }else{
      printf("[DEBUG] opened fifo for reading\n");
    }

    while((bytes_read=read(fd,buf,MAX_ARG_SIZE))>0){
      write(logfile,buf,bytes_read);
      write(logfile,"\n",1);
      printf("[DEBUG] wrote %s to file \n",buf);
    }
    if(bytes_read==0){
      printf("[DEBUG] EOF\n");
    }else{
      perror("read");
    }
    close(0)
  }
  //only executed in case of an error
  close(logfile);
  close(fd_write);

  return 0;
}
