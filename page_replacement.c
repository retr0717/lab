#include <stdio.h>
#include <stdlib.h>

void print_ref_str(int pages[], int pCount) {
  printf("\nReference string\n");
  for (int i = 0; i < pCount; i++) {
    printf("%d  ", pages[i]);
  }
  printf("\n");
}

void print_frames(int frames[], int fCount) {
  for (int j = 0; j < fCount; j++) {
    if (frames[j] == -1)
      printf("- ");
    else
      printf("%d ", frames[j]);
  }
  printf("\n");
}

void fifo(int pages[], int frames[], int pCount, int fCount) {
  int hit = 0, fault = 0, queue = 0;

  print_ref_str(pages, pCount);

  for (int i = 0; i < pCount; i++) {
    int page = pages[i];
    int flag = 0;
    for (int j = 0; j < fCount; j++) {
      if (frames[j] == page) {
        flag = 1;
        hit++;
        break;
      }
    }
    if (flag == 0) {
      frames[queue] = page;
      fault++;
      queue = (queue + 1) % fCount;
      print_frames(frames, fCount);
    }
  }

  printf("\nHit : %d\nFault : %d\n", hit, fault);
  printf("Hit ratio : %f\n", (float)hit / pCount);
  printf("\n");
}

void lfu(int pages[], int frames[], int pCount, int fCount) {
  int frequency[30] = {0}, pos, flag, hit = 0, fault = 0;

  print_ref_str(pages, pCount);

  for (int i = 0; i < pCount; i++) {
    int page = pages[i];
    flag = 0;
    for (int j = 0; j < fCount; j++) {
      if (frames[j] == page) {
        frequency[j]++;
        flag = 1;
        hit++;
        break;
      }
    }
    if (flag == 0) {
      pos = 0;
      for (int j = 1; j < fCount; j++) {
        if (frames[j] == -1 || frequency[j] < frequency[pos]) {
          pos = j;
        }
      }
      frames[pos] = page;
      frequency[pos] = 1;
      fault++;
      print_frames(frames, fCount);
    }
  }

  printf("\nHit : %d\nFault : %d\n", hit, fault);
  printf("Hit ratio : %f\n", (float)hit / pCount);
  printf("\n");
}

int findLRU(int time[], int fCount) {
  int min = time[0], pos = 0;
  for (int k = 1; k < fCount; ++k) {
    if (time[k] < min) {
      min = time[k];
      pos = k;
    }
  }
  return pos;
}

void lru(int pages[], int frames[], int time[], int pCount, int fCount) {
  int counter = 0, faultCount = 0, pos, flag, hit = 0;

  print_ref_str(pages, pCount);

  for (int i = 0; i < pCount; ++i) {
    flag = 0;
    printf("  %d\t|\t", pages[i]);
    for (int j = 0; j < fCount; ++j) {
      if (frames[j] == pages[i]) {
        flag = 1;
        counter++;
        time[j] = counter;
        hit++;
        printf("   Hit\n\n");
        break;
      }
    }
    if (flag == 0) {
      if (i < fCount) {
        frames[i] = pages[i];
        counter++;
        time[i] = counter;
        faultCount++;
      } else {
        pos = findLRU(time, fCount);
        frames[pos] = pages[i];
        counter++;
        time[pos] = counter;
        faultCount++;
      }
      print_frames(frames, fCount);
    }
  }
  printf("Total Page Faults = %d\n", faultCount);
  printf("Hit : %d\n", hit);
  printf("Hit ratio : %f\n\n", (float)hit / pCount);
}

int main() {
  int pCount, fCount, pages[30], frames[30], time[30], choice;

  printf("Enter the number of frames : ");
  scanf("%d", &fCount);

  printf("Enter the number of pages : ");
  scanf("%d", &pCount);

  // read reference string
  printf("Enter the reference string : ");
  for (int i = 0; i < pCount; i++) {
    scanf("%d", &pages[i]);
  }

  while (1) {
    printf("1. FIFO\n2. LRU\n3. LFU\n4. Exit\n");
    printf("Enter your choice : ");
    scanf("%d", &choice);

    // initialize the frame array with -1
    for (int i = 0; i < fCount; i++) {
      frames[i] = -1;
      time[i] = 0;
    }

    switch (choice) {
    case 1:
      fifo(pages, frames, pCount, fCount);
      break;
    case 2:
      lru(pages, frames, time, pCount, fCount);
      break;
    case 3:
      lfu(pages, frames, pCount, fCount);
      break;
    case 4:
      exit(0);
    default:
      printf("Invalid choice\n");
    }
  }
  return 0;
}
