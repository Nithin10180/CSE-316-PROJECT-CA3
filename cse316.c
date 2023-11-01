#include <stdio.h>

struct Process {
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int completed;
};

void calculateWaitingTime(struct Process processes[], int n) {
    int time = 0, i, remaining;
    for(i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed = 0;
    }
    while(1) {
        int flag = 1;
        for(i = 0; i < n; i++) {
            if(processes[i].arrival_time <= time && processes[i].remaining_time > 0) {
                flag = 0;
                if(processes[i].remaining_time > 6) {
                    time += 6;
                    processes[i].remaining_time -= 6;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].waiting_time = time - processes[i].arrival_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    processes[i].completed = 1;
                }
            }
        }
        if(flag)
            time++;
        remaining = 0;
        for(i = 0; i < n; i++)
            if(processes[i].remaining_time > 0)
                remaining++;
        if(remaining == 0)
            break;
    }
}

void calculateTurnaroundTime(struct Process processes[], int n) {
    for(int i = 0; i < n; i++)
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for(i = 0; i < n; i++) {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);

    int total_waiting_time = 0, total_turnaround_time = 0;
    for(i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nProcess\t Arrival Time\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t %d\t\t %d\t\t %d\t\t %d\n", i + 1, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time/n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time/n);

    return 0;
}