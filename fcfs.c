#include <stdio.h>

int main(){
	int n; printf("Enter the number of processes : ");
	scanf("%d",&n);

	int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
	int totalWaitingTime=0,totalTurnAroundTime=0;

	for(int i=0; i<n; i++){
		pid[i] = i+1;
		printf("P%d (at bt) : ",i+1);
		scanf("%d %d",&at[i], &bt[i]);
	}
	for(int i=0; i<n-1; i++){
		for(int j=0; j<n-i-1; j++){
			if(at[j] > at[j+1]){
				int temp;
				temp = at[j]; at[j] = at[j+1]; at[j+1] = temp;
				temp = bt[j]; bt[j] = bt[j+1]; bt[j+1] = temp;
				temp = pid[j]; pid[j] = pid[j+1]; pid[j+1] = temp;
			}
		}
	}
	ct[0] = at[0] + bt[0];
	for(int i=1; i<n; i++){
		if(ct[i-1] < at[i]) { ct[i] = at[i] + bt[i]; }
		else { ct[i] = ct[i-1] + bt[i]; }
	}
	for(int i=0; i<n; i++){
		tat[i] = ct[i] - at[i]; totalTurnAroundTime+=tat[i];
		wt[i] = tat[i] - bt[i]; totalWaitingTime+=wt[i];
	}
	printf("\nGantt Chart : "); for(int i=0; i<n; i++) { printf("P%d ",pid[i]); }
	printf("\nAverage waiting time : %.2f\n",(float)totalWaitingTime/n);
	printf("Average turn aroung time : %.2f\n",(float)totalTurnAroundTime/n);
}
