#include <stdio.h>

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int main() {
  int bt[10], p[10], n, wt[10], tat[10];
  float avgWT = 0, avgTAT = 0;

  printf("Enter the total number of processes: ");
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    printf("Enter the burst time of P%d: ", i + 1);
    scanf("%d", &bt[i]);
    p[i] = i + 1; // Process ID initialization
  }

  // Sort processes based on burst time (using selection sort)
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (bt[i] > bt[j]) {
        swap(&bt[i], &bt[j]);
        swap(&p[i], &p[j]);
      }
    }
  }

  // Calculate Waiting Time (WT) and Turnaround Time (TAT)
  wt[0] = 0; // First process WT is always 0
  for (int i = 1; i < n; i++) {
    wt[i] = wt[i - 1] + bt[i - 1];
    avgWT += wt[i];
  }

  for (int i = 0; i < n; i++) {
    tat[i] = wt[i] + bt[i];
    avgTAT += tat[i];
  }

  // Calculate average waiting time and average turnaround time
  avgWT /= n;
  avgTAT /= n;

  // Print the results
  printf("\nProcess\tBT\tWT\tTAT\n");
  for (int i = 0; i < n; i++) {
    printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);
  }
  printf("\n");

  printf("Average Turnaround Time: %.2f\n", avgTAT);
  printf("Average Waiting Time: %.2f\n", avgWT);

  return 0;
}

/*
 Enter the total number of processes: 3
Enter the burst time of P1: 5
Enter the burst time of P2: 3
Enter the burst time of P3: 8

Process	BT	WT	TAT
P2	3	0	3
P1	5	3	8
P3	8	8	16

Average Turnaround Time: 9.00
Average Waiting Time: 3.67
 */
