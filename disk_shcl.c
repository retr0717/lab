#include <stdio.h>
#include <stdlib.h>

void fcfs(int diskQueue[], int n);
void scan(int diskQueue[], int n, int start);
void cscan(int diskQueue[], int n, int start);
void sort(int diskQueue[], int n);

int main() {
  int diskQueue[20], n, start, choice;

  while (1) {
    printf("Disk Scheduling Algorithms\n");
    printf("1. FCFS\n");
    printf("2. SCAN\n");
    printf("3. C-SCAN\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 4) {
      break;
    }

    printf("Enter the size of Queue: ");
    scanf("%d", &n);
    printf("Enter the Queue: ");
    for (int i = 1; i <= n; i++) {
      scanf("%d", &diskQueue[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &diskQueue[0]);

    switch (choice) {
    case 1:
      fcfs(diskQueue, n + 1);
      break;
    case 2:
      printf("Enter the initial head position: ");
      scanf("%d", &start);
      scan(diskQueue, n + 1, start);
      break;
    case 3:
      printf("Enter the initial head position: ");
      scanf("%d", &start);
      cscan(diskQueue, n + 1, start);
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  }

  return 0;
}

void fcfs(int diskQueue[], int n) {
  int seekTime = 0, diff;

  printf("\nMovement of Cylinders\n");
  for (int i = 0; i < n - 1; i++) {
    diff = abs(diskQueue[i + 1] - diskQueue[i]);
    seekTime += diff;
    printf("Move from %d to %d with seek time %d\n", diskQueue[i],
           diskQueue[i + 1], diff);
  }

  printf("\nTotal Seek Time: %d", seekTime);
  printf("\nAverage Seek Time = %f", (float)seekTime / (n - 1));
  printf("\n");
}

void scan(int diskQueue[], int n, int start) {
  int pos, diff, seekTime = 0, current;

  diskQueue[0] = start;
  sort(diskQueue, n);

  for (int i = 0; i < n; i++) {
    if (diskQueue[i] == start) {
      pos = i;
      break;
    }
  }

  printf("\nMovement of Cylinders\n");
  for (int i = pos; i < n - 1; i++) {
    diff = abs(diskQueue[i + 1] - diskQueue[i]);
    seekTime += diff;
    printf("Move from %d to %d with seek time %d\n", diskQueue[i],
           diskQueue[i + 1], diff);
  }
  current = diskQueue[n - 1];
  for (int i = pos - 1; i >= 0; i--) {
    diff = abs(current - diskQueue[i]);
    seekTime += diff;
    printf("Move from %d to %d with seek time %d\n", current, diskQueue[i],
           diff);
    current = diskQueue[i];
  }

  printf("\nTotal Seek Time: %d", seekTime);
  printf("\nAverage Seek Time = %f", (float)seekTime / (n - 1));
  printf("\n");
}

void cscan(int diskQueue[], int n, int start) {
  int pos, diff, seekTime = 0, current;

  diskQueue[0] = start;
  sort(diskQueue, n);

  for (int i = 0; i < n; i++) {
    if (diskQueue[i] == start) {
      pos = i;
      break;
    }
  }

  printf("\nMovement of Cylinders\n");
  for (int i = pos; i < n - 1; i++) {
    diff = abs(diskQueue[i + 1] - diskQueue[i]);
    seekTime += diff;
    printf("Move from %d to %d with seek time %d\n", diskQueue[i],
           diskQueue[i + 1], diff);
  }
  current = 0;
  printf("Move from %d to %d with seek time %d\n", diskQueue[n - 1], current,
         0);
  for (int i = 0; i < pos; i++) {
    diff = abs(diskQueue[i] - current);
    seekTime += diff;
    printf("Move from %d to %d with seek time %d\n", current, diskQueue[i],
           diff);
    current = diskQueue[i];
  }

  printf("\nTotal Seek Time: %d", seekTime);
  printf("\nAverage Seek Time = %f", (float)seekTime / (n - 1));
  printf("\n");
}

void sort(int diskQueue[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      if (diskQueue[j] > diskQueue[j + 1]) {
        int tmp = diskQueue[j];
        diskQueue[j] = diskQueue[j + 1];
        diskQueue[j + 1] = tmp;
      }
    }
  }
}

/*
 Enter the size of Queue: 5
Enter the Queue: 55 58 39 18 90
Enter the initial head position: 50

FCFS Disk Scheduling Algorithm
Total Seek Time: 120
Average Seek Time = 24.000000

SCAN Disk Scheduling Algorithm
Total Seek Time: 112
Average Seek Time = 22.400000

C-SCAN Disk Scheduling Algorithm
Total Seek Time: 79
Average Seek Time = 15.800000
 */
