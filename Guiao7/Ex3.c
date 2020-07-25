#include<signal.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
typedef void (*sighandler_t)(int);
int pids;
int npids;
int timeout =0;


void timeout_handler(int signum){
    for(int i=0;i<npids; i++){
        printf("Timeout GREP %d\n",pids[i]);
        if(pids[i]>0){
            kill(pids[i],SIGKILL);
        }
    }
    timeout=1;
}

int spawn_grep(char* word, char* file, int i){
    int pid;
    if((pid = fork())==0){
        printf("Process %d [%d]: file %s\n",i,getpid(),file);
        sleep(15);
        if(execlp("grep","grep",word,file,NULL)<0){
            perror("exec");
        }
        _exit(0);
    }
    
}

int main(int argc, char const *argv[]) {

    if(signal(SIGALARM,timeout_handler)<0){
        perror("Signal SIGALARM");
        exit(-1);
    }
    
    int files_count = argc-2;
    npids=files_count;
    pids = malloc(sizeof(int) * npids);
    char** files = argv+2;
    
    for(int i=0; i<files_count;i++){
        pids[i] = spawn_grep(argv[1],files[i],i);
    }
    
    alarm(10);
    
    int found=0;
    int status=0;
    int pid;
    int pid_found = -1;
    while(!found && (pid = wait(&status))>0){
        if(WIFEXITED(status)){
            switch(WEXITSTATUS(status)){
                case 0:
                    printf("Process %d found the word\n",pid);
                    found=1;
                    pid_found=pid;
                    break;
                case 1:
                    printf("Process %d did not find the word\n",pid);
                    break;
            }
        }
    }
    
    if(found==1){
        for(int i=0;i<files_count;i++){
            if(pids[i] != pid_found){
                printf("Killing process %d\n",pids[i]);
                
                //evitar a possibilidade de um kill -1 (Mata todos os processos)
                if(pids[i]>0){
                    kill(pids[i],SIGKILL);
                }
                
                waitpid(pids[i],&status,0);
                
                if(WIFEXITED(status)){
                    printf("Process %d ended correctly already\n",pids[i]);
                }
                else{
                    printf("Process %d was interrupted/killed \n",pids[i]);
                }
            }
        }
    }


  return 0;
}
