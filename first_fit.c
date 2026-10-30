#include <stdio.h>

int main() {
    int nb, np, block[50], proc[50], used[50] = {0};

    printf("Enter number of free blocks available : ");
    scanf("%d", &nb);
    for (int i = 0; i < nb; i++) scanf("%d", &block[i]);

    printf("Enter number of processes : ");
    scanf("%d", &np);
    for (int i = 0; i < np; i++) scanf("%d", &proc[i]);

    printf("\nOutput:\n");
    for (int i = 0; i < np; i++) {
        int idx = -1;
        for (int j = 0; j < nb; j++) {
            if (used[j] || block[j] < proc[i]) continue;
            idx = j; break;   /* first block that is big enough */
        }
        if (idx != -1) {
            used[idx] = 1;
            printf("%d - %d\n", proc[i], idx + 1);
        } else {
            printf("%d - no free block allocated\n", proc[i]);
        }
    }
    return 0;
}