#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int end = 0;

    printf("Terminal Hechiza v1.0\n");
    printf("Teclea exit para salir\n");
    printf("Advertencia: Puede llegar a ser adictiva\n\n\n\n");
    
    do
    {
        printf(">_ ");
        int hijo = vfork();

        if(hijo == 0){
            

            char command[50] = "";
            char *args[50] = {NULL};
            char **pointer = args;
            char *env_args[] = { "PATH=/bin", "USER=me", NULL };

            char input[100];
            int cont = 0;
            char* delim =" "; 

            scanf("%s", input);
            strcat(command, "/bin/");
            strcat(command, input);

            if(strcmp(input, "exit")== 0){
                printf("Adios\n");
                end = 1;
                exit(0);
            }

            pointer[0] = command;

            scanf("%[^\n]s", input);

            char *ptr = strtok(input, delim);

            while(ptr != NULL)
            {
                cont++;
                pointer[cont] = ptr;
                ptr = strtok(NULL, delim);
            }

            pointer[cont+1] = NULL;


            if(execve(command, args, env_args)==-1){
                printf("Error en el comando o en sus argumentos. %s\n", command);
            }
            exit(0);
        }
    } while (end  == 0);
    


    return 0;
}
