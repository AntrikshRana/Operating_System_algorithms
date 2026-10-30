#include <stdio.h>

int main() {
    int frames, n, ref[100], mem[20], last_used[20];
    int faults = 0;

    printf("Enter number of frames available : ");
    scanf("%d", &frames);
    printf("Enter number of page requests: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);

    for (int i = 0; i < frames; i++) { mem[i] = -1; last_used[i] = -1; }

    for (int i = 0; i < n; i++) {
        int pos = -1;
        for (int j = 0; j < frames; j++)
            if (mem[j] == ref[i]) { pos = j; break; }

        if (pos != -1) {
            last_used[pos] = i;            /* hit: refresh usage time */
        } else {
            int victim = 0;
            for (int j = 0; j < frames; j++) {
                if (mem[j] == -1) { victim = j; break; }          /* empty frame */
                if (last_used[j] < last_used[victim]) victim = j; /* least recent */
            }
            mem[victim] = ref[i];
            last_used[victim] = i;
            faults++;
        }
    }

    printf("Total number of page faults : %d\n", faults);
    return 0;
}