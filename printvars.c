#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


char *custom_env[] = {"USER=Pikachu", "PATH=/tmp", NULL};


int main(void)
{
    // TODO
    pid_t first_cpid;
    pid_t second_cpid;

    printf("Running parent process PID: %d\n\n", getpid());

    first_cpid = fork();

    if(first_cpid == 0){
        printf("Running child process PID: %d\n", getpid());

        execle("./echoall", "echoall", "Bandicoot", "Pacman", NULL, custom_env);
        perror("execle"); // Exec failed, display error
        exit(1);
    }
    else if(first_cpid > 0){
        wait(NULL);
        
        second_cpid = fork();
        
        if (second_cpid == 0) {
            printf("Running child process PID: %d\n", getpid());
            
            execlp("./echoall", "echoall", "Spyro", NULL);
            perror("execlp"); // Exec failed, display error
            exit(1);
        } 
        else if (second_cpid > 0) {
            wait(NULL);
        } 
        else {
            fprintf(stderr, "Second fork failed\n");
            exit(1);
        }
    }
    else {
        fprintf(stderr, "First fork failed\n");
        exit(1);
    }
    exit(0);
}