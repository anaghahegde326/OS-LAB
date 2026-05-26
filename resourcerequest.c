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

    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Maximum Matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Total Resources:\n");
    for(int j = 0; j < m; j++)
        scanf("%d", &total[j]);

    for(int j = 0; j < m; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++)
            sum += alloc[i][j];
        avail[j] = total[j] - sum;
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int p, request[MAX];

    printf("\nEnter process number making request: ");
    scanf("%d", &p);

    printf("Enter request vector:\n");
    for(int j = 0; j < m; j++)
        scanf("%d", &request[j]);

    for(int j = 0; j < m; j++) {
        if(request[j] > need[p][j]) {
            printf("Error: Request exceeds maximum need\n");
            return 0;
        }
    }

    for(int j = 0; j < m; j++) {
        if(request[j] > avail[j]) {
            printf("Resources not available. Process must wait\n");
            return 0;
        }
    }

    for(int j = 0; j < m; j++) {
        avail[j] -= request[j];
        alloc[p][j] += request[j];
        need[p][j] -= request[j];
    }

    for(int j = 0; j < m; j++)
        work[j] = avail[j];

    for(int i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {
                int j;
                for(j = 0; j < m; j++)
                    if(need[i][j] > work[j])
                        break;

                if(j == m) {
                    for(int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nRequest CANNOT be granted (unsafe state)\n");
            return 0;
        }
    }

    printf("\nRequest CAN be granted\nSafe sequence: ");
    for(int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);

    printf("\n");

    return 0;
}
