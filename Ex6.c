#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    struct Node* sig;
    int value;
} Node;

static volatile sig_atomic_t sig_caught = 0;
Node* QPointer = NULL;

char* translateSignal(int signum){
    char* result = "";

    switch(signum){
        case 1: result = "SIGHUP"; break;
        case 2: result = "SIGINT"; break;
        case 3: result = "SIGQUIT"; break;
        case 4: result = "SIGILL"; break;
        case 5: result = "SIGTRAP"; break;
        case 6: result = "SIGABRT"; break;
        case 7: result = "SIGBUS"; break;
        case 8: result = "SIGFPE"; break;
        case 9: result = "SIGKILL"; break;
        case 10: result = "SIGUSR1"; break;
        case 11: result = "SIGSEGV"; break;
        case 12: result = "SIGUSR2"; break;
        case 13: result = "SIGPIPE"; break;
        case 14: result = "SIGALRM"; break;
        case 15: result = "SIGTERM"; break;
        case 17: result = "SIGCHLD"; break;
        case 18: result = "SIGCONT"; break;
        case 19: result = "SIGSTOP"; break;
        case 20: result = "SIGTSTP"; break;
        case 21: result = "SIGTTIN"; break;
        case 22: result = "SIGTTOU"; break;
        case 23: result = "SIGURG"; break;
        case 24: result = "SIGXCPU"; break;
        case 25: result = "SIGXFSZ"; break;
        case 26: result = "SIGVTALRM"; break;
        case 27: result = "SIGPROF"; break;
        case 28: result = "SIGWINCH"; break;
        case 29: result = "SIGIO"; break;
        case 30: result = "SIGPWR"; break;
        case 31: result = "SIGSYS"; break;
        case 32: result = "SIGRTMIN"; break;
    }
}

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
    Node* aux = QPointer;
    while(aux != NULL){
        printf("%s->", translateSignal(aux->value));    
        aux = aux->sig;
    }

    printf("END\n");
}

void handle_sighup(int signum){
    if(signum != 2)
        push(createNode(signum));
    
    sig_caught = signum;
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
    signal(SIGKILL,handle_sighup);
    signal(SIGUSR1,handle_sighup);
    signal(SIGSEGV,handle_sighup);
    signal(SIGUSR2,handle_sighup);
    signal(SIGPIPE,handle_sighup);
    signal(SIGALRM,handle_sighup);
    signal(SIGTERM,handle_sighup);
    signal(SIGCHLD,handle_sighup);
    signal(SIGCONT, handle_sighup);
    signal(SIGSTOP, handle_sighup);
    signal(SIGTSTP, handle_sighup);
    signal(SIGTTIN, handle_sighup);
    signal(SIGTTOU, handle_sighup);
    signal(SIGURG, handle_sighup);
    signal(SIGXCPU, handle_sighup);
    signal(SIGXFSZ, handle_sighup);
    signal(SIGVTALRM, handle_sighup);
    signal(SIGPROF, handle_sighup);
    signal(SIGWINCH, handle_sighup);
    signal(SIGIO, handle_sighup);
    signal(SIGPWR, handle_sighup);
    signal(SIGSYS, handle_sighup);
    signal(SIGRTMIN, handle_sighup);
}

int main(int argc, char* argv[])
{
    signals();

    while(1) {
        if (sig_caught == 2) {
            sig_caught = 0;
            break;
        }

    }

    
    printList();
    return 0;
}
