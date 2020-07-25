int main(int agrc, char* argv[]){
  int fd = open("fifo",O_WRONLY);
  if(fd==-1){
    perror("Open");
  }else{
    printf("[DEBUG] Opened FIFO for writing\n");
  }
  if(write(fd,argv[1],strlen(argv[1])==1){
    perror("Write");
  }
  close(fd);
  return 0;
}
