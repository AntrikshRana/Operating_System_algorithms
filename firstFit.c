#include <stdio.h>
#include<stdlib.h>

int main() {
    int n; printf("Enter the number of blocks : "); scanf("%d",&n);
    int m; printf("Enter the number of processes : "); scanf("%d",&m);

    int *block = malloc(n*sizeof(int));
    int *process = malloc(m*sizeof(int));

    printf("Block Sizes : "); for(int _=0; _<n; _++) scanf("%d",&block[_]);
    printf("Processes : "); for(int _=0; _<m; _++) scanf("%d",&process[_]);

    int *allocation = malloc(m*sizeof(int)); for(int _=0; _<m; _++) allocation[_] = -1;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(block[j] >= process[i]) {
                block[j] -= process[i];
                allocation[i] = j;
                break;
            }
        }
    }

    printf("%-10s %-10s %-10s\n","Process Number", "Process Size", "Block Number");
    for(int i=0; i<m; i++) {
        printf("%-10d %-10d ",i+1,process[i]);
        if(allocation[i] != -1) printf("%-10d", allocation[i]+1);
        else printf("%-10s", "Not Allocated");
        printf("\n");
    }

    free(allocation); free(block); free(process);
    return 0;
}