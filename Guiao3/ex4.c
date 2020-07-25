#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

int main(int argc, char** argv){

  execv("ex3",argv);
  return 0;
}
