#include <stdio.h>
#include <limits.h>

// Process structure
typedef struct {
    int pid;        // Process ID
    int burst;      // Burst Time
    int arrival;    // Arrival Time
    int turnaround; // Turnaround Time
    int waiting;    // Waiting Time
} Process;

// Function to perform SJF (Shortest Job First) scheduling with preemption
void sjf_preemptive(Process processes[], int n) {
    int currentTime = 0; // Current time
    int completed = 0;   // Number of completed processes

    // Iterate until all processes are completed
    while (completed < n) {
        int shortestBurstIndex = -1;
        int shortestBurst = INT_MAX;

        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (processes[i].burst > 0 && processes[i].burst < shortestBurst && processes[i].arrival <= currentTime) {
                shortestBurst = processes[i].burst;
                shortestBurstIndex = i;
            }
        }

        // If no process is available at current time, move time to the next process arrival time
        if (shortestBurstIndex == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].burst > 0 && processes[i].arrival < nextArrival) {
                    nextArrival = processes[i].arrival;
                }
            }
            currentTime = nextArrival;
        } else {
            // Execute the process with the shortest burst time
            processes[shortestBurstIndex].burst--;
            currentTime++;

            // If process is completed, calculate turnaround time and increment completed count
            if (processes[shortestBurstIndex].burst == 0) {
                processes[shortestBurstIndex].turnaround = currentTime - processes[shortestBurstIndex].arrival;
                processes[shortestBurstIndex].waiting = processes[shortestBurstIndex].turnaround - processes[shortestBurstIndex].burst;
                completed++;
            }
        }
    }

    // Print the final result in table format
    printf("Process\tArrival Time\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival,
               processes[i].burst, processes[i].turnaround, processes[i].waiting);
    }

    // Calculate and print average waiting time and average turnaround time
    int totalWaiting = 0;
    int totalTurnaround = 0;
    for (int i = 0; i < n; i++) {
        totalWaiting += processes[i].waiting;
        totalTurnaround += processes[i].turnaround;
    }
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
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
    }

    // Perform SJF scheduling with preemption
    sjf_preemptive(processes, n);

    return 0;
}