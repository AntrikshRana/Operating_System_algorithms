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
                printf("%s	%d\n",entry->d_name,entry->d_type);
        }

        closedir(dir);

        return 0;
}
