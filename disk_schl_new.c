#include <stdio.h>
#include <stdlib.h>

void FCFS() {
  int seekTime = 0, diff = 0, size = 0;
  printf("Enter the size ");
  scanf("%d", &size);

  int diskQueue[size + 1];

  printf("\nEnter the queue items\n");
  for (int i = 1; i < size + 1; i++) {
    scanf("%d", &diskQueue[i]);
  }
  int head = 0;
  printf("Enter the head pos : ");
  scanf("%d", &head);

  diskQueue[0] = head;

  for (int i = 0; i < size; i++) {
    diff = abs(diskQueue[i + 1] - diskQueue[i]);

    seekTime += diff;

    printf("\nHandle move from %d to %d with seek time %d\n", diskQueue[i],
           diskQueue[i + 1], diff);
  }

  printf("Head movements : %d\n", seekTime);
  printf("Avg Seek time : %f\n", (float)seekTime / (size));
}

void sort(int diskQueue[], int size) {
  int temp = 0;
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (diskQueue[i] > diskQueue[j]) {
        temp = diskQueue[i];
        diskQueue[i] = diskQueue[j];
        diskQueue[j] = temp;
      }
    }
  }
}

void Scan() {
  int seekTime = 0, diff = 0, size = 0;
  printf("Enter the size ");
  scanf("%d", &size);
  size += 2;
  int diskQueue[size];

  printf("\nEnter the queue items\n");
  for (int i = 0; i < size - 2; i++) {
    scanf("%d", &diskQueue[i]);
  }

  printf("Enter the cylinder size : ");
  scanf("%d", &diskQueue[size - 1]);
  diskQueue[size - 1] = diskQueue[size - 1] - 1;
  int head = 0;
  printf("Enter the head pos : ");
  scanf("%d", &head);

  diskQueue[size - 2] = head;

  sort(diskQueue, size - 1);

  int current = head;
  int pos = 0;

  // find pos of head item.
  for (int i = 0; i < size - 1; i++) {
    if (diskQueue[i] == head) {
      pos = i;
      break;
    }
  }

  // move from pos to 0.
  for (int i = pos - 1; i >= 0; i--) {
    diff = abs(diskQueue[i] - current);
    seekTime += diff;
    printf("\nMove ment of head from %d to %d with seektime %d\n", current,
           diskQueue[i], diff);
    current = diskQueue[i];
  }

  diff = abs(0 - current);
  seekTime += diff;
  printf("\nMove ment of head from %d to %d with seektime %d\n", current, 0,
         diff);

  // move from 0 to size-1.
  current = 0;
  for (int i = pos + 1; i < size; i++) {
    diff = abs(diskQueue[i] - current);
    seekTime += diff;
    printf("\nMove ment of head from %d to %d with seektime %d\n", current,
           diskQueue[i], diff);
    current = diskQueue[i];
  }

  printf("\nTotal seek time : %d\n", seekTime);
  printf("\nAvg seek time : %f\n", (float)seekTime / (size - 2));
}

void CScan() {
  int seekTime = 0, diff = 0, size = 0;
  printf("Enter the size ");
  scanf("%d", &size);
  size += 2;
  int diskQueue[size];

  printf("\nEnter the queue items\n");
  for (int i = 0; i < size - 2; i++) {
    scanf("%d", &diskQueue[i]);
  }

  printf("Enter the cylinder size : ");
  scanf("%d", &diskQueue[size - 1]);
  diskQueue[size - 1] = diskQueue[size - 1] - 1;
  int head = 0;
  printf("Enter the head pos : ");
  scanf("%d", &head);

  diskQueue[size - 2] = head;

  sort(diskQueue, size - 1);

  int current = head;
  int pos = 0;

  // find pos of head item.
  for (int i = 0; i < size - 1; i++) {
    if (diskQueue[i] == head) {
      pos = i;
      break;
    }
  }

  // move from head to size -1.
  current = head;
  for (int i = pos + 1; i < size; i++) {
    diff = abs(diskQueue[i] - current);
    seekTime += diff;
    printf("\nMove ment of head from %d to %d with seektime %d\n", current,
           diskQueue[i], diff);
    current = diskQueue[i];
  }

  // move to 0.
  diff = abs(current - 0);
  seekTime += diff;
  printf("\nMove ment of head from %d to %d with seektime %d\n", current, 0,
         diff);

  // move from 0 to pos - 1.
  current = 0;
  for (int i = 0; i < pos; i++) {
    diff = abs(diskQueue[i] - current);
    seekTime += diff;
    printf("\nMove ment of head from %d to %d with seektime %d\n", current,
           diskQueue[i], diff);
    current = diskQueue[i];
  }

  printf("\nTotal seek time : %d\n", seekTime);
  printf("\nAvg seek time : %f\n", (float)seekTime / (size - 2));
}

int main() {
  // FCFS();
  // Scan();
  CScan();

  return 0;
}
