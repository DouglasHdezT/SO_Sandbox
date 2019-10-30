#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>

int step = 1;

void handle_sighup(int signum){
    
    if(signum == 4){
        //printf("Soy una senal de: %d\n", getpid());
        return;
    }
    if(signum == 5){
        //printf("Soy el tata con una senal de: %d\n", getpid());
        return;
    }
    if(signum==2){
        step = step * -1;
    }
    if(signum==15){
        exit(0);
    }
}



int main(){
    signal(SIGTRAP, handle_sighup);
    signal(SIGILL, handle_sighup);
    signal(SIGTERM, handle_sighup);
    signal(SIGINT, handle_sighup);
    
    int n = 4;
    int ppid = getpid();
    pid_t pids[n];
    int *head = &pids[0];
    int *tail = &pids[n];
    int cpos = -1;
    
    int *run = head;
    
    int child = -1;
    for(int i=0;i<n;i++){
        child = fork();
        if(child > 0){
            pids[i] = child;

        }
        if(child==0){
            cpos = i;
            pause();
            break;
        }
    }
    

    int cont = 0;

    while(1){

        if(ppid== getpid()){
            kill(pids[cont], 4);
            //pause();
            
            for (long i = 0; i < 300000000; i++){
                
            }

            cont=cont + step;

            if(cont >= n){
                cont = 0;
            }
            if(cont <0 ){
                cont = n-1;
            }

            
            
            
        }else{
            printf("soy el hijo %d: %d\n", cpos,getpid());
            kill(getppid(), 5);
            pause();
        }
            
    }

    
    return 0;
    
}
