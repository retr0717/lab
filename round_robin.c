#include <stdio.h>

// Process structure
typedef struct {
    int pid;        // Process ID
    int burst;      // Burst Time
    int remaining;  // Remaining Burst Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
} Process;

// Function to perform Round Robin scheduling
void round_robin(Process processes[], int n, int quantum) {
    int currentTime = 0;    // Current time
    int completed = 0;       // Number of completed processes
    int totalWaiting = 0;    // Total waiting time
    int totalTurnaround = 0; // Total turnaround time

    // Iterate until all processes are completed
    while (completed < n) {
        // Iterate through processes
        for (int i = 0; i < n; i++) {
            // Execute process if it has remaining burst time
            if (processes[i].remaining > 0) {
                // Execute process for quantum or remaining burst time, whichever is smaller
                int executionTime = (processes[i].remaining < quantum) ? processes[i].remaining : quantum;
                
                // Update remaining burst time and current time
                processes[i].remaining -= executionTime;
                currentTime += executionTime;
                
                // If process is completed, calculate turnaround time and increment completed count
                if (processes[i].remaining == 0) {
                    processes[i].turnaround = currentTime;
                    completed++;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;
                    totalWaiting += processes[i].waiting;
                    totalTurnaround += processes[i].turnaround;
                }
            }
        }
    }

    // Print the final result in table format
    printf("Process\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst, processes[i].turnaround, processes[i].waiting);
    }

    // Calculate and print average waiting time and average turnaround time
    double avgWaiting = (double)totalWaiting / n;
    double avgTurnaround = (double)totalTurnaround / n;
    printf("\nAverage Waiting Time: %.2f\n", avgWaiting);
    printf("Average Turnaround Time: %.2f\n", avgTurnaround);
}

// Main function
int main() {
    int n, quantum;

    // Input number of processes and time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Input process details
    Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
        processes[i].remaining = processes[i].burst; // Initialize remaining burst time
    }

    // Perform Round Robin scheduling and print the final result along with average waiting time and average turnaround time
    round_robin(processes, n, quantum);

    return 0;
}
