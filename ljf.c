#include <stdio.h>
#include <limits.h>

int main(){
        int n;
        printf("Enter the number of processes : ");
        scanf("%d",&n);

        int pid[n], at[n], bt[n];
        int ct[n], tat[n], wt[n];
        int done[n], chart[n];

        for(int i=0; i<n; i++) { done[i] = 0; }

        for(int i=0; i<n; i++){
                pid[i] = i+1;
                printf("P%d (at bt) : ",pid[i]);
                scanf("%d %d",&at[i], &bt[i]);
        }

        int time=0, completed=0, total_TAT=0, total_WT=0, ganttCount=0;
        int maxBT, index;
	int current_time = 0;

	while(completed < n){
		maxBT = -1;
		index = -1;

		for(int i=0; i<n; i++){
			if(done[i] == 0 && at[i] <= current_time){
				if(bt[i] > maxBT){
					index = i;
				}
			}
		}
		if(index == -1){
			current_time++;
		}
		else{
			chart[ganttCount] = index;
			ganttCount++;

			ct[index] = current_time + bt[index];
			tat[index] = ct[index] - at[index];
			wt[index] = tat[index] - bt[index];
			
			total_TAT+=tat[index];
			total_WT+=wt[index];
				
			current_time = ct[index];
			done[index] = 1;
			completed++;
		}
	}

        printf("\nGantt chart : ");
        for(int i=0; i<n; i++) { printf("P%d ",pid[chart[i]]); }
        printf("\nAverage waiting time : %.2f",(float)total_WT/n);
        printf("\nAverage turn around time : %.2f\n",(float)total_TAT/n);

}
