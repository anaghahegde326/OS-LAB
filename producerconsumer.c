#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < n; ++i) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[30], frames[10], time[10];
    int n, f, i, j, k, faults, counter, pos, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    // ---------- FIFO ----------
    for (i = 0; i < f; i++) frames[i] = -1;
    faults = 0; pos = 0;
    printf("\nFIFO Page Replacement:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = 1;
        if (!found) {
            frames[pos] = pages[i];
            pos = (pos + 1) % f;
            faults++;
        }
        printf("Page %d -> ", pages[i]);
        for (k = 0; k < f; k++)
            (frames[k] != -1) ? printf("%d ", frames[k]) : printf("- ");
        printf("\n");
    }
    printf("Total Page Faults (FIFO) = %d\n", faults);

    // ---------- LRU ----------
    for (i = 0; i < f; i++) frames[i] = -1;
    faults = 0; counter = 0;
    printf("\nLRU Page Replacement:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                counter++;
                time[j] = counter;
                break;
            }
        }
        if (!found) {
            if (i < f)
                frames[i] = pages[i];
            else {
                pos = findLRU(time, f);
                frames[pos] = pages[i];
            }
            counter++;
            time[i % f] = counter;
            faults++;
        }
        printf("Page %d -> ", pages[i]);
        for (k = 0; k < f; k++)
            (frames[k] != -1) ? printf("%d ", frames[k]) : printf("- ");
        printf("\n");
    }
    printf("Total Page Faults (LRU) = %d\n", faults);

    // ---------- Optimal ----------
    for (i = 0; i < f; i++) frames[i] = -1;
    faults = 0;
    printf("\nOptimal Page Replacement:\n");
    for (i = 0; i < n; i++) {
        found = 0;
        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) found = 1;
        if (!found) {
            if (i < f)
                frames[i] = pages[i];
            else {
                int future[10], flag[10];
                for (j = 0; j < f; j++) {
                    flag[j] = 0;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            future[j] = k;
                            flag[j] = 1;
                            break;
                        }
                    }
                    if (!flag[j]) future[j] = n + 1;
                }
                int max = future[0];
                pos = 0;
                for (j = 1; j < f; j++) {
                    if (future[j] > max) {
                        max = future[j];
                        pos = j;
                    }
                }
                frames[pos] = pages[i];
            }
            faults++;
        }
        printf("Page %d -> ", pages[i]);
        for (k = 0; k < f; k++)
            (frames[k] != -1) ? printf("%d ", frames[k]) : printf("- ");
        printf("\n");
    }
    printf("Total Page Faults (Optimal) = %d\n", faults);

    return 0;
}
