#include <stdio.h>
#include <limits.h>

// Process structure
typedef struct {
    int pid;        // Process ID
    int burst;      // Burst Time
    int priority;   // Priority
    int arrival;    // Arrival Time
    int turnaround; // Turnaround Time
} Process;

// Function to perform Priority Scheduling with preemption
void priority_preemptive(Process processes[], int n) {
    int currentTime = 0; // Current time
    int completed = 0;   // Number of completed processes
    int highestPriorityIndex; // Index of process with highest priority

    while (completed < n) {
        // Find the process with the highest priority that has arrived
        highestPriorityIndex = -1;
        int highestPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (processes[i].burst > 0 && processes[i].priority < highestPriority && processes[i].arrival <= currentTime) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        // If no process is available at current time, move time to the next process arrival time
        if (highestPriorityIndex == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].burst > 0 && processes[i].arrival < nextArrival) {
                    nextArrival = processes[i].arrival;
                }
            }
            currentTime = nextArrival;
        } else {
            // Execute the process with the highest priority
            processes[highestPriorityIndex].burst--;

            // If process is completed, calculate turnaround time and increment completed count
            if (processes[highestPriorityIndex].burst == 0) {
                processes[highestPriorityIndex].turnaround = currentTime - processes[highestPriorityIndex].arrival;
                completed++;
            }
            currentTime++;
        }
    }

    // Print the final result in table format
    printf("Process\tArrival Time\tBurst Time\tPriority\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival,
               processes[i].burst, processes[i].priority, processes[i].turnaround);
    }
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
