#include <stdio.h>

void fcfs(int bt[], int n);

int main() {
  int bt[20], n;

  printf("Enter the total number of processes: ");
  scanf("%d", &n);

  printf("Enter burst times for each process:\n");
  for (int i = 0; i < n; i++) {
    printf("P%d: ", i + 1);
    scanf("%d", &bt[i]);
  }

  fcfs(bt, n);

  return 0;
}

void fcfs(int bt[], int n) {
  int wt[20], tat[20];
  float twt = 0, ttat = 0;

  // Calculate Waiting Time (WT) for each process
  wt[0] = 0; // First process has 0 waiting time
  for (int i = 1; i < n; i++) {
    wt[i] = wt[i - 1] + bt[i - 1];
    twt += wt[i];
  }

  // Calculate Turnaround Time (TAT) for each process
  for (int i = 0; i < n; i++) {
    tat[i] = wt[i] + bt[i];
    ttat += tat[i];
  }

  // Calculate averages
  float avgWT = twt / n;
  float avgTAT = ttat / n;

  // Print the results
  printf("\nProcess\tBT\tWT\tTAT\n");
  for (int i = 0; i < n; i++) {
    printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
  }
  printf("\n");

  printf("Average Turnaround Time: %.2f\n", avgTAT);
  printf("Average Waiting Time: %.2f\n", avgWT);
}

/*
Enter the total number of processes: 3
Enter burst times for each process:
P1: 5
P2: 3
P3: 8

Process	BT	WT	TAT
P1	5	0	5
P2	3	5	8
P3	8	8	16

Total Turnaround Time: 29.00
Total Waiting Time: 13.00
Average Turnaround Time: 9.67
Average Waiting Time: 4.33
*/
