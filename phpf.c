#include <stdio.h>
#include <limits.h>

int main(){
        int n;
        printf("Enter the number of processes : ");
        scanf("%d",&n);

        int pid[n], at[n], bt[n], priority[n], rt[n];
        int ct[n], tat[n], wt[n];
        int chart[n * 100];

        for(int i=0; i<n; i++){
                pid[i] = i+1;
                printf("P%d (at bt priority) : ",pid[i]);
                scanf("%d %d %d",&at[i], &bt[i], &priority[i]);
                rt[i] = bt[i];
        }

        int time=0, completed=0;
        int total_TAT=0, total_WT=0, ganttCount=0;
        int min, index;

        while(completed < n){
                min = INT_MAX;
                index = -1;

                for(int i=0; i<n; i++){
                        if(at[i] <= time && rt[i] > 0){
                                if(priority[i] < min){
                                        min = priority[i];
                                        index = i;
                                }
                        }
                }

                if(index == -1){
                        time++;
                }
                else{
                        if(ganttCount == 0 || chart[ganttCount-1] != index){
                                chart[ganttCount] = index;
                                ganttCount++;
                        }

                        rt[index]--;
                        time++;

                        if(rt[index] == 0){
                                ct[index] = time;
                                tat[index] = ct[index] - at[index];
                                wt[index] = tat[index] - bt[index];

                                completed++;
                                total_TAT += tat[index];
                                total_WT += wt[index];
                        }
                }
        }

        printf("\nGantt chart : ");
        for(int i=0; i<ganttCount; i++) { printf("P%d ",pid[chart[i]]); }
        printf("\nAverage waiting time : %.2f",(float)total_WT/n);
        printf("\nAverage turn around time : %.2f\n",(float)total_TAT/n);

}
