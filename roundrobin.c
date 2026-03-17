#include <stdio.h>

int main() {
    int n, i, tq, remain;
    int bt[20], rt[20], wt[20], tat[20];
    int time = 0;
    float avg_wt = 0, avg_tat = 0;


    int gantt_p[100];
    int gantt_t[100];
    int k = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for P%d: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;
    gantt_t[k] = 0;

    while(remain != 0) {
        for(i = 0; i < n; i++) {

            if(rt[i] > 0) {
                gantt_p[k] = i + 1;

                if(rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    wt[i] = time - bt[i];
                    remain--;
                }
                else {
                    time += tq;
                    rt[i] -= tq;
                }

                k++;
                gantt_t[k] = time;
            }
        }
    }

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }


    printf("\nProcess\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat/n);


    printf("\nGantt Chart:\n");

    for(i = 0; i < k; i++)
        printf("-------");
    printf("-\n|");


    for(i = 0; i < k; i++)
        printf("  P%d  |", gantt_p[i]);

    printf("\n");


    for(i = 0; i < k; i++)
        printf("-------");
    printf("-\n");

    for(i = 0; i <= k; i++)
        printf("%d\t", gantt_t[i]);

    printf("\n");

    return 0;
}
