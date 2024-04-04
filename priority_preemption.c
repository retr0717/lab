#include <stdio.h>
#include <limits.h>

// Process structure
typedef struct {
    int pid;        // Process ID
    int burst;      // Burst Time
    int priority;   // Priority
    int arrival;    // Arrival Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
} Process;

// Function to perform Priority Scheduling with preemption
void priority_preemptive(Process processes[], int n) {
    int currentTime = 0; // Current time
    int completed = 0;   // Number of completed processes
    int totalWaiting = 0;    // Total waiting time
    int totalTurnaround = 0; // Total turnaround time

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].burst > 0 && processes[i].priority < highestPriority && processes[i].arrival <= currentTime) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].burst > 0 && processes[i].arrival < nextArrival) {
                    nextArrival = processes[i].arrival;
                }
            }
            currentTime = nextArrival;
        } else {
            processes[highestPriorityIndex].burst--;

            if (processes[highestPriorityIndex].burst == 0) {
                processes[highestPriorityIndex].turnaround = currentTime - processes[highestPriorityIndex].arrival;
                processes[highestPriorityIndex].waiting = processes[highestPriorityIndex].turnaround - processes[highestPriorityIndex].burst;
                completed++;
                totalTurnaround += processes[highestPriorityIndex].turnaround;
                totalWaiting += processes[highestPriorityIndex].waiting;
            }
            currentTime++;
        }
    }

    // Print the final result in table format
    printf("Process\tArrival Time\tBurst Time\tPriority\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival,
               processes[i].burst, processes[i].priority, processes[i].turnaround, processes[i].waiting);
    }

    // Calculate and print average waiting time and average turnaround time
    double avgWaiting = (double)totalWaiting / n;
    double avgTurnaround = (double)totalTurnaround / n;
    printf("\nAverage Waiting Time: %.2f\n", avgWaiting);
    printf("Average Turnaround Time: %.2f\n", avgTurnaround);
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
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
    }

    // Perform Priority Scheduling with preemption
    priority_preemptive(processes, n);

    return 0;
}
