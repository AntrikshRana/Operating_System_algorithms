#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    pid_t pid = fork();

    if (pid == 0) {
        printf("\n--- Child Process ---\n");
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());

        sleep(10);

        printf("\n--- After Parent Termination ---\n");
        printf("Child Process ID: %d\n", getpid());
        printf("New Parent Process ID: %d\n", getppid());

        printf("--- Child Process Terminated ---\n");
        exit(0);
    }
    else {
        printf("\n--- Parent Process ---\n");
        printf("Parent Process ID: %d\n", getpid());
        printf("Child Process ID: %d\n", pid);

        sleep(2);

        printf("--- Parent Process Terminated ---\n");
        exit(0);
    }

    return 0;
}
