#include <unistd.h>
#include<fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char** argv){
  int input_fd = open("/etc/passwd",O_RDONLY);
  int output_fd = open("saida.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);
  int error_fd = open("erros.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666);

  dup2(input_fd,0);
  dup2(output_fd,1);
  dup2(error_fd,2);

  close (input_fd);
  close (output_fd);
  close (error_fd);

  int fdin = dup(0);
  int dout=dup(1);
  int fderror=dup(2);

  int res=0;
  int i=0;
  int lines=12;
  char buffer;
  char line[1024];

  while(lines>0){
    while(read(0,&buffer,1) != 0){
      line[i] = buffer;
      i++;
      if(buffer == '\n'){
       break;
     }
    }

  write(1,line,i);
  write(2,line,i);

  printf("after write line\n");
  fflush(stdout);

  i=0;
  lines--;
}

  return 0;
}
