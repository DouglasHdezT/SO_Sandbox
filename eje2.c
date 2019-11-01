#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long *factorial(long n){
    long *result=(long*)malloc(1*sizeof(long));
    long i =1, f=1;
    while(i<=n){
       f=f*i;
       i=i+1; 
    }
    result[0] = f;
    printf("El factorial de %ld es %ld\n",n,f);
    return result;
}
void *factorial_(void *args){
    long n = *((long*)args);
    return (void*)factorial(n);
}
int main(int args, char **argv){
    long n = 0;
    //long m = 10;
    printf("Ingrese un numero: ");
    scanf("%ld",&n);
    pthread_t thread[1];
    pthread_create(&thread[0],NULL,factorial_,&n);
    //pthread_create(&thread[1],NULL,factorial,&m);
    pthread_join(thread[0],NULL);
    //pthread_join(thread[1],NULL);
    return 0;
}