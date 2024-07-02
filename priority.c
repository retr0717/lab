#include <stdio.h>

void main() {
  int n, i, j, temp;
  float twt = 0, ttt = 0;

  printf("Enter the number of processes: ");
  scanf("%d", &n);

  int bt[n], priority[n], wt[n], tt[n];

  for (i = 0; i < n; i++) {
    printf("Enter burst time of process %d: ", i + 1);
    scanf("%d", &bt[i]);
    printf("Enter priority of process %d: ", i + 1);
    scanf("%d", &priority[i]);
  }

  // Sort the processes based on priority (in ascending order)
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (priority[i] > priority[j]) {
        temp = priority[i];
        priority[i] = priority[j];
        priority[j] = temp;

        temp = bt[i];
        bt[i] = bt[j];
        bt[j] = temp;
      }
    }
  }

  wt[0] = 0; // Waiting time for the first process is 0

  // Calculate waiting time for each process
  for (i = 1; i < n; i++) {
    wt[i] = wt[i - 1] + bt[i - 1];
    twt = twt + wt[i];
  }

  // Calculate turnaround time for each process
  for (i = 0; i < n; i++) {
    tt[i] = wt[i] + bt[i];
    ttt = ttt + tt[i];
  }

  printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

  for (i = 0; i < n; i++) {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], priority[i], wt[i],
           tt[i]);
  }

  float awt = twt / n;
  float att = ttt / n;

  printf("\nAverage Waiting time is:%f", awt);
  printf("\nAverage turnaround is :%f", att);
}

/*
OUTPUT
======
Enter the number of processes: 5
Enter burst time of process 1: 10
Enter priority of process 1: 3
Enter burst time of process 2: 5
Enter priority of process 2: 0
Enter burst time of process 3: 14
Enter priority of process 3: 2
Enter burst time of process 4: 6
Enter priority of process 4: 1
Enter burst time of process 5: 20
Enter priority of process 5: 4

Process	Burst Time	Priority	Waiting Time	Turnaround Time
1	5		0		0		5
2	6		1		5		11
3	14		2		11		25
4	10		3		25		35
5	20		4		35		55

Average Waiting time is:15.200000
Average turnaround is :26.200001
*/
