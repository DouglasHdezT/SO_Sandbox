#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int valorRet;
int child; 
int ppid = -1;

int fxFactorial(int num){
   
   child = fork();
   if(child==0){
   	 if(num == 0){
   	 	return 1;
   	 }else{
   	 	return fxFactorial(num-1)*num; 
   	 }
   }
   if(child>0){
   	 wait(&valorRet);
	 return(valorRet+1);
   }
   
   
}
 
int main(){
  int num;
  int ppid = getpid();
  printf("Ingresa un numero para calcular su factorial : ");
  scanf("%d",&num);
  printf("------\n");
  
  int fac = fxFactorial(num);

  
  
  if(child==0){
  	printf("El factorial es: %d \n",fac);
  }
  
  return 0;
}
