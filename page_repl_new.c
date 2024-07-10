#include <stdio.h>
struct Freq {
  int count;
  int index;
}; // Struct freq is defined but not used

int isEmpty(int farry[], int fno) {
  for (int i = 0; i < fno; i++) {
    if (farry[i] == -1) {
      return 1;
    }
  }
  return 0;
}

int check_frame(int farry[], int pno, int fno) {
  for (int i = 0; i < fno; i++) {
    if (farry[i] == pno) {
      return 1;
    }
  }
  return 0;
}

void FIFO(int farry[], int parr[], int fno, int pno) {
  int hit = 0, pf = 0;

  for (int i = 0; i < pno; i++) {
    if (isEmpty(farry, fno)) {
      if (!check_frame(farry, parr[i], fno)) {
        farry[i] = parr[i];
        pf++;
        printf("\nPage Fault at %d\n", parr[i]);
      } else {
        printf("\nPage Hit at %d\n", parr[i]);
        hit++;
      }

    } else {
      if (!check_frame(farry, parr[i], fno)) {
        // shift to left.
        for (int j = 0; j < fno - 1; j++) {
          farry[j] = farry[j + 1];
        }
        farry[fno - 1] = parr[i];
        pf++;
      } else {
        printf("\nPage Hit at %d\n", parr[i]);
        hit++;
      }
    }
  }

  printf("Page Fault : %d\n", pf);
  printf("Page Hit : %d\n", hit);
}

int findIndex(int farry[], int parr[], int fno, int pno, int i) {
  struct Freq freq[fno];

  for (int j = 0; j < fno; j++) {
    freq[j].count = 0;
    freq[j].index = j;
  }

  for (int j = 0; j < fno; j++) {
    for (int k = i; k < pno; k++) {
      if (farry[j] == parr[k]) {
        break;
      } else {
        freq[j].count++;
      }
    }
  }

  int small = freq[0].count, index = 0;
  for (int j = 1; j < fno; j++) {
    if (freq[j].count > small) {
      small = freq[j].count;
      index = j;
    }
  }

  for (int j = 0; j < fno; j++) {
    printf("\nFreq : %d \tIndex : %d\n", freq[j].count, freq[j].index);
  }

  printf("\nindex : %d\n", index);

  return index;
}

void LFU(int farry[], int parr[], int fno, int pno) {
  int hit = 0, pf = 0;
  for (int i = 0; i < pno; i++) {
    if (isEmpty(farry, fno)) {
      if (!check_frame(farry, parr[i], fno)) {
        farry[i] = parr[i];
        pf++;
        printf("\nPage Fault at %d\n", parr[i]);
      } else {
        printf("\nPage Hit at %d\n", parr[i]);
        hit++;
      }

    } else {
      if (!check_frame(farry, parr[i], fno)) {
        int index = findIndex(farry, parr, fno, pno, i);
        farry[index] = parr[i];
        printf("\nindex : %d\n", index);
        pf++;
        printf("\nPage Fault in else at %d\n", parr[i]);
      } else {
        printf("\nPage Hit in else at %d\n", parr[i]);
        hit++;
      }
    }
  }

  printf("Page Fault : %d\n", pf);
  printf("Page Hit : %d\n", hit);
}

void LRU(int farry[], int parr[], int fno, int pno) {
  int hit = 0, pf = 0;

  for (int i = 0; i < pno; i++) {
    if (isEmpty(farry, fno)) {
      if (!check_frame(farry, parr[i], fno)) {
        farry[i] = parr[i];
        pf++;
        printf("\nPage Fault at %d\n", parr[i]);
      } else {
        printf("\nPage Hit at %d\n", parr[i]);
        hit++;
      }

    } else {
      if (!check_frame(farry, parr[i], fno)) {
        // shift to left.
        int start = i;
        for (int k = 0; k < fno; k++) {
          farry[k] = parr[start--];
        }

        pf++;
      } else {
        printf("\nPage Hit at %d\n", parr[i]);
        hit++;
      }
    }
  }

  printf("Page Fault : %d\n", pf);
  printf("Page Hit : %d\n", hit);
}

int main() {
  int pno, fno;
  printf("Enter the no of pages : ");
  scanf("%d", &pno);
  printf("Enter the no of frames : ");
  scanf("%d", &fno);

  int farry[fno], parr[pno], hit = 0, pf = 0;

  for (int i = 0; i < fno; i++) {
    farry[i] = -1;
  }

  printf("Enter the page nos : ");
  for (int i = 0; i < pno; i++) {
    scanf("%d", &parr[i]);
  }

  // FIFO(farry, parr, fno, pno);
  //  LFU(farry, parr, fno, pno);
  LRU(farry, parr, fno, pno);
  return 0;
}
