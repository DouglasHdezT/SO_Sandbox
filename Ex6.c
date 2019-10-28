#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node* sig;
    int value;
} Node;

static volatile sig_atomic_t sig_caught = 0;
Node* QPointer = NULL;

/*
    List handler
*/

Node* createNode(int signal){
    Node* n= (Node*) malloc(sizeof(Node));
    n->value = signal;
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
    while(aux->sig != NULL){
        printf("%d->", aux->value);    
        aux = aux->sig;
    }

    printf("FIN\n");
}

void handle_sighup(int signum){
    push(createNode(signum));
}

void signals(){
    signal(SIGHUP, handle_sighup);
    signal(SIGINT, handle_sighup);
    signal(SIGQUIT, handle_sighup);
    signal(SIGILL, handle_sighup);
    signal(SIGTRAP, handle_sighup);
    signal(SIGABRT, handle_sighup);
    signal(SIGBUS, handle_sighup);
    signal(SIGFPE, handle_sighup);
}

int main(int argc, char* argv[]) 
{
    signals();

    while(1) {
        if (sig_caught) {
            sig_caught = 0;
            printf("caught a SIGHUP.  I should re-read settings.\n");
        }
    }

    return 0;
}
