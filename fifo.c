#include <stdio.h>

int main() {
    int frames, n, ref[100], mem[20];
    int faults = 0, next = 0;

    printf("Enter number of frames available : ");
    scanf("%d", &frames);
    printf("Enter number of page requests: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);

    for (int i = 0; i < frames; i++) mem[i] = -1;

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++)
            if (mem[j] == ref[i]) { hit = 1; break; }

        if (!hit) {
            mem[next] = ref[i];            /* replace the oldest page */
            next = (next + 1) % frames;
            faults++;
        }
    }

    printf("Total number of page faults : %d\n", faults);
    return 0;
}