#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(){
        DIR *dir;
        struct dirent *entry;
	struct stat file;

        dir = opendir(".");

        if(dir == NULL){
                printf("Couldn't open directory.\n");
                return 1;
        }

        printf("Directory Contents:\n");

        while((entry = readdir(dir)) != NULL){
        	stat(entry->d_name, &file);
		printf("%s	%ld Bytes\n",entry->d_name,file.st_size);
	}

        closedir(dir);

        return 0;
}
