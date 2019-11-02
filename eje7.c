#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10

int numbers[N];

pthread_mutex_t lock; 

void *sortLast(void *input){

    for(int i=N-1;i>=0;i--){
        for(int j=N-1;j>=N-i;j--){
            if(numbers[j]< numbers[j-1]){
                if(N % 2 != 0)
                    if(i==N/2+1)
                        pthread_mutex_lock(&lock);
                int aux = numbers[j-1];
                numbers[j-1] = numbers[j];
                numbers[j] = aux;
                if(N % 2 != 0)
                    if(i==N/2+1)
                        pthread_mutex_unlock(&lock);
            }
        }
    }
}

void *sortInit(void *input){

    for(int i=0;i<N;i++){
        for(int j=0;j<N-i-1;j++){
            if(numbers[j]>numbers[j+1]){
                if(N % 2 != 0)
                    if(i==N/2+1)
                        pthread_mutex_lock(&lock);
                int aux = numbers[j+1];
                numbers[j+1] = numbers[j];
                numbers[j] = aux;
                if(N % 2 != 0)
                    if(i==N/2+1)
                        pthread_mutex_unlock(&lock);
            }
        }
    }
}

void *getArrayNumber(void *input) {
    
    printf("Llenado del arreglo, ingrese %d, ingresandolo uno por uno \n",N);
    for(int i=0;i<N;i++){
        printf("Ingrese el numero %d :",i);
        scanf("%d",&numbers[i]);
    }
} 

void printArray(){
    for(int i=0;i<N;i++){
        printf("%d->",numbers[i]);
    }
    printf("\n");
}

int main(){
    pthread_t scanner;
    
    if (pthread_mutex_init(&lock, NULL) != 0) 
    { 
        printf("La inicialozacion el mutex fallo\n"); 
        return 1; 
    } 
    
    pthread_create(&scanner,NULL,getArrayNumber,(void *)NULL);
    pthread_join(scanner,NULL);
    
    printArray();
    
    pthread_t first;
    pthread_t last;
    
    pthread_create(&first,NULL,sortInit,NULL);
    pthread_create(&last,NULL,sortLast,NULL);
    
    pthread_join(first,NULL);
    pthread_join(last,NULL);
    
    printArray();
    
    pthread_mutex_destroy(&lock);
    return 0;
}