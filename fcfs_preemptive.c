#include <stdio.h>

// Process structure
typedef struct {
    int pid;        // Process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int waiting;    // Waiting Time
    int turnaround; // Turnaround Time
} Process;

// Function to swap two processes
void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform FCFS scheduling
void fcfs(Process processes[], int n) {
    int totalTime = 0; // Total time elapsed
    float totalWaitingTime = 0, totalTurnaroundTime = 0; // Total waiting and turnaround time

    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }

    // Calculate waiting and turnaround time
    for (int i = 0; i < n; i++) {
        if (totalTime < processes[i].arrival) {
            totalTime = processes[i].arrival;
        }
        processes[i].waiting = totalTime - processes[i].arrival;
        totalWaitingTime += processes[i].waiting;
        totalTime += processes[i].burst;
        processes[i].turnaround = totalTime - processes[i].arrival;
        totalTurnaroundTime += processes[i].turnaround;
    }

    // Print process details and average waiting and turnaround time
    printf("Process\t Arrival Time\t Burst Time\t Waiting Time\t Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", processes[i].pid, processes[i].arrival, processes[i].burst,
               processes[i].waiting, processes[i].turnaround);
    }

    // Calculate and print average waiting time and average turnaround time
    float avgWaitingTime = totalWaitingTime / n;
    float avgTurnaroundTime = totalTurnaroundTime / n;
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}

// Main function
int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process details
    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
    }

    // Perform FCFS scheduling
    fcfs(processes, n);

    return 0;
}
