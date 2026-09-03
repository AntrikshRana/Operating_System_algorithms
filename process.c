#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	pid_t pid = fork();

	if(pid < 0) printf("Failed\n");

	else if(pid == 0){
		printf("\n-----Child Process-----\n");

		printf("%d is Child Process ID\n", getpid());
		printf("%d is Parent Process ID\n", getppid());
	}

	else if(pid > 0){
		wait(NULL);
		printf("\n-----Parent Process-----\n");

		printf("%d id Parent Process ID\n", getpid());
		printf("%d is Child Process ID\n", pid);
	}
}
