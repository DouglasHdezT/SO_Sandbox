#include <signal.h>
#include <stdio.h>

/* typedef struct Node{
    Node* sig;
    char* value;
} Node; */

static volatile sig_atomic_t sig_caught = 0;

void handle_sighup(int signum){
    /* in case we registered this handler for multiple signals */
    if (signum == SIGHUP) {
        sig_caught = 1;
    }

    printf("%d\n", signum);
}

void signals(){
    signal(SIGHUP, handle_sighup);
    signal(SIGINT, handle_sighup);
    signal(SIGQUIT, handle_sighup);

    //9 - 17
    signal(SIGKILL,handle_sighup);
    signal(SIGUSR1,handle_sighup);
    signal(SIGSEGV,handle_sighup);
    signal(SIGUSR2,handle_sighup);
    signal(SIGPIPE,handle_sighup);
    signal(SIGALRM,handle_sighup);
    signal(SIGTERM,handle_sighup);
    signal(SIGCHLD,handle_sighup);

    //18 - 24
    signal(SIGCONT, handle_sighup);
    signal(SIGSTOP, handle_sighup);
    signal(SIGTSTP, handle_sighup);
    signal(SIGTTIN, handle_sighup);
    signal(SIGTTOU, handle_sighup);
    signal(SIGURG, handle_sighup);
    signal(SIGXCPU, handle_sighup);

    //25 - 32
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
        if (sig_caught) {
            sig_caught = 0;
            printf("caught a SIGHUP.  I should re-read settings.\n");
        }
    }

    return 0;
}
