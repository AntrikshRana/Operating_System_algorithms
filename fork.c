#include <stdio.h>
#include <unistd.h>

int main(){
	fork();

	if(fork() && fork()){
		fork();
	}

	fork();

	printf("Printing Statement\n");
}
