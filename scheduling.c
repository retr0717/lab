#include <stdio.h>
#include <stdlib.h>

struct Process {
  int id, burstTime, arrivalTime, priority;
  int waitTime, turnaroundTime, remainingTime;
};

// Function Prototypes
void fcfs(struct Process[], int);
void sjf(struct Process[], int);
void roundRobin(struct Process[], int, int);
void priorityScheduling(struct Process[], int);
void calculateWaitTimeAndTAT(struct Process[], int);
void resetProcesses(struct Process[], int);
void displayAvgTimes(struct Process[], int);

int main() {
  int choice, n, quantum;
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  struct Process processes[n];
  for (int i = 0; i < n; i++) {
    processes[i].id = i + 1;
    printf("Enter Burst Time, Arrival Time, and Priority for Process %d: ",
           i + 1);
    scanf("%d %d %d", &processes[i].burstTime, &processes[i].arrivalTime,
          &processes[i].priority);
    processes[i].remainingTime = processes[i].burstTime;
  }

  while (1) {
    printf("\nScheduling Menu:\n");
    printf("1. First-Come, First-Served (FCFS)\n");
    printf("2. Shortest Job First (SJF)\n");
    printf("3. Round Robin\n");
    printf("4. Priority Scheduling\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    resetProcesses(processes, n); // Reset times before each scheduling choice

    switch (choice) {
    case 1:
      fcfs(processes, n);
      break;
    case 2:
      sjf(processes, n);
      break;
    case 3:
      printf("Enter time quantum: ");
      scanf("%d", &quantum);
      roundRobin(processes, n, quantum);
      break;
    case 4:
      priorityScheduling(processes, n);
      break;
    case 5:
      exit(0);
    default:
      printf("Invalid choice!\n");
    }
  }
  return 0;
}

// Function to reset waiting, turnaround, and remaining times for each
// scheduling choice
void resetProcesses(struct Process processes[], int n) {
  for (int i = 0; i < n; i++) {
    processes[i].waitTime = 0;
    processes[i].turnaroundTime = 0;
    processes[i].remainingTime = processes[i].burstTime;
  }
}

// First-Come, First-Served (FCFS)
void fcfs(struct Process processes[], int n) {
  calculateWaitTimeAndTAT(processes, n);
  printf("\nFCFS Scheduling:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
           processes[i].id, processes[i].waitTime, processes[i].turnaroundTime);
  }
  displayAvgTimes(processes, n);
}

// Shortest Job First (SJF)
void sjf(struct Process processes[], int n) {
  struct Process temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (processes[i].burstTime > processes[j].burstTime) {
        temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }
  calculateWaitTimeAndTAT(processes, n);
  printf("\nSJF Scheduling:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
           processes[i].id, processes[i].waitTime, processes[i].turnaroundTime);
  }
  displayAvgTimes(processes, n);
}

// Round Robin
void roundRobin(struct Process processes[], int n, int quantum) {
  int time = 0, completed = 0;
  while (completed < n) {
    for (int i = 0; i < n; i++) {
      if (processes[i].remainingTime > 0 && time >= processes[i].arrivalTime) {
        if (processes[i].remainingTime > quantum) {
          time += quantum;
          processes[i].remainingTime -= quantum;
        } else {
          time += processes[i].remainingTime;
          processes[i].waitTime =
              time - processes[i].burstTime - processes[i].arrivalTime;
          processes[i].remainingTime = 0;
          completed++;
        }
      }
      if (time < processes[i].arrivalTime) {
        time = processes[i].arrivalTime;
      }
    }
  }
  printf("\nRound Robin Scheduling:\n");
  for (int i = 0; i < n; i++) {
    processes[i].turnaroundTime =
        processes[i].burstTime + processes[i].waitTime;
    printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
           processes[i].id, processes[i].waitTime, processes[i].turnaroundTime);
  }
  displayAvgTimes(processes, n);
}

// Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
  struct Process temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (processes[i].priority > processes[j].priority) {
        temp = processes[i];
        processes[i] = processes[j];
        processes[j] = temp;
      }
    }
  }
  calculateWaitTimeAndTAT(processes, n);
  printf("\nPriority Scheduling:\n");
  for (int i = 0; i < n; i++) {
    printf("Process %d: Waiting Time = %d, Turnaround Time = %d\n",
           processes[i].id, processes[i].waitTime, processes[i].turnaroundTime);
  }
  displayAvgTimes(processes, n);
}

// Helper function to calculate waiting and turnaround times
void calculateWaitTimeAndTAT(struct Process processes[], int n) {
  processes[0].waitTime = 0;
  for (int i = 1; i < n; i++) {
    processes[i].waitTime =
        processes[i - 1].waitTime + processes[i - 1].burstTime;
  }
  for (int i = 0; i < n; i++) {
    processes[i].turnaroundTime =
        processes[i].burstTime + processes[i].waitTime;
  }
}

// Function to display average waiting and turnaround times
void displayAvgTimes(struct Process processes[], int n) {
  int totalWait = 0, totalTurnaround = 0;
  for (int i = 0; i < n; i++) {
    totalWait += processes[i].waitTime;
    totalTurnaround += processes[i].turnaroundTime;
  }
  printf("Average Waiting Time = %.2f\n", (float)totalWait / n);
  printf("Average Turnaround Time = %.2f\n", (float)totalTurnaround / n);
}
