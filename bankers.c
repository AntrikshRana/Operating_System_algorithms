#include <stdio.h>

int main() {
    int n, m;
    int max[20][20], alloc[20][20], need[20][20];
    int total[20], avail[20], work[20];
    int finish[20] = {0}, safe[20];

    printf("Enter number of processes : ");
    scanf("%d", &n);
    printf("Enter number of resources : ");
    scanf("%d", &m);

    printf("Enter maximum requirement :\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter allocated matrix :\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Resource Vector : ");
    for (int j = 0; j < m; j++)
        scanf("%d", &total[j]);

    /* Need = Max - Allocation ; Available = Total - sum(Allocation) */
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            need[i][j] = max[i][j] - alloc[i][j];
            sum += alloc[i][j];
        }
        avail[j] = total[j] - sum;
        work[j] = avail[j];
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        /* always restart the scan from P0 after each process is selected */
        for (int i = 0; i < n; i++) {
            if (finish[i]) continue;
            int ok = 1;
            for (int j = 0; j < m; j++)
                if (need[i][j] > work[j]) { ok = 0; break; }
            if (ok) {
                for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                finish[i] = 1;
                safe[count++] = i;
                found = 1;
                break;
            }
        }
        if (!found) break;   /* no process can proceed -> unsafe */
    }

    if (count == n) {
        printf("Request can be fulfilled\n");
        printf("Safe Sequence :");
        for (int i = 0; i < n; i++) printf(" P%d", safe[i]);
        printf("\n");
    } else {
        printf("Request cannot be fulfilled\n");
        printf("System is not in a safe state (deadlock possible)\n");
    }
    return 0;
}