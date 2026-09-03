#include <stdio.h> 
#include <dirent.h> 
#include <sys/stat.h> 

int main(){

    DIR *dir; 
    struct dirent *entry; 
    struct stat st;

    dir = opendir("."); 
    if (dir == NULL) 
    { 
        printf("Unable to open directory\n"); 
        return 1; 
    }

    printf("Name\t\tType\t\tSize\tPermissions\n"); 
    while ((entry = readdir(dir)) != NULL){ 
        stat(entry->d_name, &st); 
        printf("%-15s", entry->d_name); 
        
	if (entry->d_type == DT_DIR) { printf("Directory\t"); }
        else if (entry->d_type == DT_REG) { printf("File\t\t"); }
        else { printf("Other\t\t"); }

        printf("%ld\t", st.st_size); 
        printf("%o\n", st.st_mode & 0777); 
    } 

    closedir(dir); 
}
