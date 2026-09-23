#include <stdio.h>

int main(){
    int ganttChart[10], time[11];
    int ganttCount = 10;

    for(int i=0; i<ganttCount; i++) ganttChart[i] = i;
    for(int i=0; i<11; i++) time[i] = i;

    for(int i=0; i<ganttCount; i++) printf("| P%-2d ",ganttChart[i]);
    printf("|\n");
    for(int i=0; i<11; i++) printf("%-5d ",time[i]);
}