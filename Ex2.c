#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <string.h>
#include<sys/wait.h> 


typedef struct Node{
    struct Node* sig;
    int value;
    char* tabs; 
} Node;

Node* QPointer = NULL;

Node* createNode(int signal, char* tabs){
    Node* n= (Node*) malloc(sizeof(Node));
    n->value = signal;
    n->tabs = tabs;
    n->sig = NULL;
}

void push(Node* node){
    if(QPointer == NULL){
        QPointer = node;
    }else{
        Node* aux = QPointer;
        while(aux->sig != NULL){
            aux = aux->sig;
        }

        aux->sig = node;
    }
}

void printList(){
    Node* aux = QPointer;
    while(aux != NULL){
        printf("%s%d\n",aux->tabs, aux->value);    
        aux = aux->sig;
    }
    printf("---------\n");
    }

int main()
{
    int N = 2;
    char tabs[N];

    push(createNode(getpid(), ""));

    for(int i=0; i<N; i++){
        if(fork()){
            strcat(tabs, "\t");
            push(createNode(getpid(), tabs));
        }
        
    }
    wait(NULL);
    printList();
    free(QPointer);

    return 0;
}