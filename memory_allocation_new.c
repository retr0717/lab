#include <stdio.h>
#include <stdlib.h>

struct Block {
  int size;
  int remaining;
};

struct Process {
  int size;
  int pid;
  int block;
};

void FirstBit() {
  int pno, bno;
  printf("Enter the no of Blocks : ");
  scanf("%d", &bno);
  printf("\nEnter the no of processes : ");
  scanf("%d", &pno);

  struct Block blocks[bno];
  struct Process processes[pno];

  printf("\nEnter the block size\n");
  for (int i = 0; i < bno; i++) {
    printf("B%d : ", i + 1);
    scanf("%d", &blocks[i].size);
    blocks[i].remaining = blocks[i].size;
  }

  printf("\nEnter the process size\n");
  for (int i = 0; i < pno; i++) {
    printf("P%d : ", i + 1);
    scanf("%d", &processes[i].size);
    processes[i].pid = i + 1;
  }

  for (int i = 0; i < pno; i++) {
    for (int j = 0; j < bno; j++) {
      if (processes[i].size <= blocks[j].remaining) {
        processes[i].block = j + 1;
        blocks[j].remaining -= processes[i].size;
        break;
      }
    }
  }

  printf("\nProcess No\tProcess Size\tBlock No\tFree\n");
  for (int i = 0; i < pno; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].size,
           processes[i].block, blocks[processes[i].block - 1].remaining);
  }
}

void BestFit() {
  int pno, bno;
  printf("Enter the no of Blocks : ");
  scanf("%d", &bno);
  printf("\nEnter the no of processes : ");
  scanf("%d", &pno);

  struct Block blocks[bno];
  struct Process processes[pno];

  printf("\nEnter the block size\n");
  for (int i = 0; i < bno; i++) {
    printf("B%d : ", i + 1);
    scanf("%d", &blocks[i].size);
    blocks[i].remaining = blocks[i].size;
  }

  printf("\nEnter the process size\n");
  for (int i = 0; i < pno; i++) {
    printf("P%d : ", i + 1);
    scanf("%d", &processes[i].size);
    processes[i].pid = i + 1;
  }

  for (int i = 0; i < pno; i++) {
    int lowest = 9999, pos = -1;
    for (int j = 0; j < bno; j++) {
      if (processes[i].size <= blocks[j].remaining &&
          blocks[j].remaining < lowest) {
        pos = j;
        lowest = blocks[j].remaining;
      }
    }

    if (pos != -1) {
      processes[i].block = pos + 1;
      blocks[pos].remaining -= processes[i].size;
    }
  }

  printf("\nProcess no\tProcess Size\tBlock No\tFree\n");
  for (int i = 0; i < pno; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].size,
           processes[i].block, blocks[processes[i].block - 1].remaining);
  }
}

void WorstFit() {
  int pno, bno;
  printf("Enter the no of Blocks : ");
  scanf("%d", &bno);
  printf("\nEnter the no of processes : ");
  scanf("%d", &pno);

  struct Block blocks[bno];
  struct Process processes[pno];

  printf("\nEnter the block size\n");
  for (int i = 0; i < bno; i++) {
    printf("B%d : ", i + 1);
    scanf("%d", &blocks[i].size);
    blocks[i].remaining = blocks[i].size;
  }

  printf("\nEnter the process size\n");
  for (int i = 0; i < pno; i++) {
    printf("P%d : ", i + 1);
    scanf("%d", &processes[i].size);
    processes[i].pid = i + 1;
  }
  for (int i = 0; i < pno; i++) {
    int highest = blocks[0].remaining, pos = -1;
    for (int j = 0; j < bno; j++) {
      if (blocks[j].remaining > highest) {
        pos = j;
        highest = blocks[j].remaining;
      }
    }
    if (pos != -1) {
      processes[i].block = pos + 1;
      blocks[pos].remaining -= processes[i].size;
    }
  }
  printf("\nProcess no\tProcess Size\tBlock No\tFree\n");
  for (int i = 0; i < pno; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].size,
           processes[i].block, blocks[processes[i].block - 1].remaining);
  }
}

int main() {
  // FirstBit();
  // BestFit();
  WorstFit();
  return 0;
}
