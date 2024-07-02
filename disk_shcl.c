#include <stdio.h>
#include <stdlib.h>

void fcfs(int diskQueue[], int n);
void scan(int diskQueue[], int n, int start, int size);
void cscan(int diskQueue[], int n, int start, int size);
void sort(int diskQueue[], int n);

int main() {
  int diskQueue[20], n, start, size, choice;

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

    switch (choice) {
    case 1:
      printf("Enter the initial head position: ");
      scanf("%d", &diskQueue[0]);

      fcfs(diskQueue, n + 1);
      break;
    case 2:
      printf("Enter the initial head position: ");
      scanf("%d", &start);
      printf("Enter the size of the cylinder: ");
      scanf("%d", &size);
      scan(diskQueue, n + 1, start, size);
      break;
    case 3:
      printf("Enter the initial head position: ");
      scanf("%d", &start);
      printf("Enter the size of the cylinder: ");
      scanf("%d", &size);
      cscan(diskQueue, n + 1, start, size);
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

void scan(int diskQueue[], int n, int start, int size) {
  int pos, diff, seekTime = 0, current;

  diskQueue[n] = start; // Extend diskQueue to include the start position
  n++;                  // Increase the size of diskQueue by 1

  sort(diskQueue, n);

  // Find the position of the start in the sorted array
  for (int i = 0; i < n; i++) {
    if (diskQueue[i] == start) {
      pos = i;
      break;
    }
  }

  printf("\nMovement of Cylinders\n");

  // Moving from start to 0
  current = start;
  for (int i = pos; i >= 0; i--) {
    diff = abs(diskQueue[i] - current);
    seekTime += diff;
    printf("Move from %d to %d with seek time %d\n", current, diskQueue[i],
           diff);
    current = diskQueue[i];
  }

  // Moving from 0 to size - 1
  current = 0;
  for (int i = pos + 1; i < n; i++) {
    diff = abs(diskQueue[i] - current);
    seekTime += diff;
    printf("Move from %d to %d with seek time %d\n", current, diskQueue[i],
           diff);
    current = diskQueue[i];
  }

  diff = abs((size - 1) - current); // Moving from size - 1 to the last element
  printf("Move from %d to %d with seek time %d\n", current, size - 1, diff);
  seekTime += diff;

  printf("\nTotal Seek Time: %d\n", seekTime);
  printf("Average Seek Time = %f\n", (float)seekTime / (n - 1));

  // Restore diskQueue to original state (optional)
  diskQueue[n - 1] = start;
}

void cscan(int diskQueue[], int n, int start, int size) {
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
  current = size - 1;
  diff = abs(size - 1 - diskQueue[n - 1]);
  seekTime += diff;
  printf("Move from %d to %d with seek time %d\n", diskQueue[n - 1], current,
         diff);
  diff = current;
  seekTime += diff;
  printf("Move from %d to %d with seek time %d\n", current, 0, diff);
  current = 0;
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
 Output:

 Disk Scheduling Algorithms
 1. FCFS
 2. SCAN
 3. C-SCAN
 4. Exit
 Enter your choice: 1
 Enter the size of Queue: 5
 Enter the Queue: 55 58 39 18 90
 Enter the initial head position: 50
 Movement of Cylinders
 Move from 50 to 55 with seek time 5
 Move from 55 to 58 with seek time 3
 Move from 58 to 39 with seek time 19
 Move from 39 to 18 with seek time 21
 Move from 18 to 90 with seek time 72
 Total Seek Time: 120
 Average Seek Time = 24.000000

 Enter your choice: 2
 Enter the size of Queue: 5
 Enter the Queue: 55 58 39 18 90
 Enter the initial head position: 50
 Enter the size of the cylinder: 200
 Movement of Cylinders
 Move from 50 to 39 with seek time 11
 Move from 39 to 18 with seek time 21
 Move from 18 to 0 with seek time 18
 Move from 0 to 55 with seek time 55
 Move from 55 to 58 with seek time 3
 Move from 58 to 90 with seek time 32
 Move from 90 to 199 with seek time 109
 Total Seek Time: 249
 Average Seek Time = 49.800000

 Enter your choice: 3
 Enter the size of Queue: 5
 Enter the Queue: 55 58 39 18 90
 Enter the initial head position: 50
 Enter the size of the cylinder: 200
 Movement of Cylinders
 Move from 50 to 55 with seek time 5
 Move from 55 to 58 with seek time 3
 Move from 58 to 90 with seek time 32
 Move from 90 to 0 with seek time 90
 Move from 0 to 18 with seek time 18
 Move from 18 to 39 with seek time 21
 Total Seek Time: 169
 Average Seek Time = 33.800000
 */

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
