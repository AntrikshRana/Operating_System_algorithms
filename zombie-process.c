#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
        pid_t pid = fork();

        if(pid == 0){
                printf("\n---Child Process---\n");
                printf("Child Process ID %d\n",getpid());
                printf("---Child Process Terminated---\n");

                exit(0);
        }
        else{
                printf("\n---Parent Process---\n");

                printf("Child Process ID %d\n", pid);
                sleep(20);
                printf("Child Process ID %d\n",pid);
                printf("---Parent Process Terminated---\n");
        }
}
