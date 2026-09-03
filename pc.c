#include <stdio.h>
#include <dirent.h>


int main(){
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");

	if(dir == NULL){
		printf("Couldn't open directory.\n");
		return 1;
	}

	printf("Directory Contents:\n");

	while((entry = readdir(dir)) != NULL){
		printf("%s\n", entry->d_name);
	}

	closedir(dir);

	return 0;
}
