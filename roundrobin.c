#include <stdio.h>
int main(){
        int n, tq;
        printf("Enter the number of processes : ");
        scanf("%d",&n);
        
	int pid[n], at[n], bt[n], rt[n], ct[n], tat[n], wt[n];
        int totalWaitingTime=0,totalTurnAroundTime=0;
        
	for(int i=0; i<n; i++){
                pid[i] = i+1;
                printf("P%d (at bt) : ",i+1);
                scanf("%d %d",&at[i], &bt[i]);
                rt[i] = bt[i];
        }
        printf("Enter time quantum : ");
        scanf("%d",&tq);

        int time = 0, completed = 0;
        int queue[100],visited[n];
        int front = 0, rear = 0;

        for(int i=0; i<n; i++) { visited[i] = 0; }

        int gantt[1000];
        int ganttCount = 0, contextSwitches = 0;

        while(completed < n){
                for(int i=0; i<n; i++){
                        if(at[i] <= time && visited[i] == 0){
                                queue[rear++] = i;
                                visited[i] = 1;
                        }
                }
                if(front == rear){
                        int next = -1;

                        for(int i=0; i<n; i++){
                                if(rt[i] > 0 && visited[i] == 0){
                                        if(next == -1 || at[i] < at[next]){
                                                next = i;
                                        }
                                }
                        }

                        time = at[next];
                        queue[rear++] = next;
                        visited[next] = 1;
                }

                int i = queue[front++];
                if(ganttCount > 0 && gantt[ganttCount - 1] != i) { contextSwitches++; }
                gantt[ganttCount++] = i;

                if(rt[i] > tq){
                        time += tq;
                        rt[i] -= tq;
                }
                else{
                        time += rt[i];
                        rt[i] = 0;
                        ct[i] = time;
                        completed++;
                }
                for(int j=0; j<n; j++){
                        if(at[j] <= time && visited[j] == 0){
                                queue[rear++] = j;
                                visited[j] = 1;
                        }
                }
                if(rt[i] > 0) { queue[rear++] = i; }
        }
        for(int i=0; i<n; i++){
                tat[i] = ct[i] - at[i];
                totalTurnAroundTime += tat[i];
                wt[i] = tat[i] - bt[i];
                totalWaitingTime += wt[i];
        }

        printf("\nGantt Chart : ");
        for(int i=0; i<ganttCount; i++) { printf("P%d ",gantt[i]+1); }
        printf("\nAverage waiting time : %.2f\n",(float)totalWaitingTime/n);
        printf("Average turn around time : %.2f\n",(float)totalTurnAroundTime/n);
        printf("Context switches : %d\n",contextSwitches);
        return 0;
}
