#include <stdio.h>

#define MAX 10

int main() {
    int n, m;

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int total[MAX], avail[MAX], work[MAX];
    int finish[MAX] = {0};
    int safeSeq[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Total Resources
    printf("\nEnter Total Resources:\n");
    for(int j = 0; j < m; j++) {
        scanf("%d", &total[j]);
    }

    // Calculate Available = Total - Allocated
    for(int j = 0; j < m; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += alloc[i][j];
        }
        avail[j] = total[j] - sum;
        work[j] = avail[j]; // initialize work
    }

    // Calculate Need Matrix
    printf("\nNeed Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j])
                        break;
                }

                if(j == m) {
                    for(int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is NOT in a safe state (Deadlock possible)\n");
            return 0;
        }
    }

    printf("\nAvailable Resources: ");
    for(int j = 0; j < m; j++) {
        printf("%d ", avail[j]);
    }

    printf("\nSystem is in SAFE state\nSafe sequence: ");
    for(int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");

    return 0;
}
