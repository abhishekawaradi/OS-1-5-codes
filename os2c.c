 #include <stdio.h>
int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int pid[n], at[n], bt[n], rt[n];
    int ct[n], tat[n], wt[n];
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter Arrival Time and Burst Time of P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i]; 
    }
    int time = 0, completed = 0;
    float avgWT = 0, avgTAT = 0;
    while (completed != n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                done = 0;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];
                    avgWT += wt[i];
                    avgTAT += tat[i];
 
                    rt[i] = 0;
                    completed++;
                }
            }
        }
        if (done == 1)  
            time++; 
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }
    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);
    return 0;
 }

