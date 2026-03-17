#include <stdio.h>

int main() {
    int n, i, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], rt[n], wt[n], tat[n], ct[n], p[n];

    for(i = 0; i < n; i++) {
        printf("\nProcess %d Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        p[i] = i + 1;
    }

    printf("\nChoose SJF Type:");
    printf("\n1. Non-Preemptive SJF");
    printf("\n2. Preemptive SJF (SRTF)");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    float avg_wt = 0, avg_tat = 0;

    switch(choice) {
        case 1: {
            int completed = 0, time = 0;

            int visited[n];
            for(i = 0; i < n; i++)
                visited[i] = 0;

            while(completed < n) {
                int min_bt = 9999, min_index = -1;

                for(i = 0; i < n; i++) {
                    if(at[i] <= time && visited[i] == 0) {
                        if(bt[i] < min_bt) {
                            min_bt = bt[i];
                            min_index = i;
                        }
                    }
                }

                if(min_index == -1) {
                    time++;
                } else {
                    time += bt[min_index];
                    ct[min_index] = time;
                    tat[min_index] = ct[min_index] - at[min_index];
                    wt[min_index] = tat[min_index] - bt[min_index];

                    avg_wt += wt[min_index];
                    avg_tat += tat[min_index];

                    visited[min_index] = 1;
                    completed++;
                }
            }

            break;
        }


        case 2: {
            int completed = 0, time = 0;

            while(completed < n) {
                int min_rt = 9999, min_index = -1;

                for(i = 0; i < n; i++) {
                    if(at[i] <= time && rt[i] > 0) {
                        if(rt[i] < min_rt) {
                            min_rt = rt[i];
                            min_index = i;
                        }
                    }
                }

                if(min_index == -1) {
                    time++;
                } else {
                    rt[min_index]--;
                    time++;

                    if(rt[min_index] == 0) {
                        completed++;
                        ct[min_index] = time;
                        tat[min_index] = ct[min_index] - at[min_index];
                        wt[min_index] = tat[min_index] - bt[min_index];

                        avg_wt += wt[min_index];
                        avg_tat += tat[min_index];
                    }
                }
            }

            break;
        }

        default:
            printf("Invalid Choice!");
            return 0;
    }

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}
