#include <stdbool.h>
#include <stdio.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int allocation[P][R] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

int maximum[P][R] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};

int available[R] = {3, 3, 2};

void calculateNeed(int need[P][R]) {
  for (int i = 0; i < P; i++) {
    for (int j = 0; j < R; j++) {
      need[i][j] = maximum[i][j] - allocation[i][j];
    }
  }
}

bool isSafe() {
  int work[R];
  bool finish[P] = {false};

  for (int i = 0; i < R; i++) {
    work[i] = available[i];
  }

  int need[P][R];
  calculateNeed(need);

  while (true) {
    bool found = false;

    for (int i = 0; i < P; i++) {
      if (!finish[i]) {
        bool canAllocate = true;

        for (int j = 0; j < R; j++) {
          if (need[i][j] > work[j]) {
            canAllocate = false;
            break;
          }
        }

        if (canAllocate) {
          for (int j = 0; j < R; j++) {
            work[j] += allocation[i][j];
          }
          finish[i] = true;
          found = true;
        }
      }
    }

    if (!found) {
      break;
    }
  }

  for (int i = 0; i < P; i++) {
    if (!finish[i]) {
      return false;
    }
  }
  return true;
}

bool requestResources(int process, int request[R]) {
  int need[P][R];
  calculateNeed(need);

  // Check if request is less than need
  for (int i = 0; i < R; i++) {
    if (request[i] > need[process][i]) {
      printf("Error: Process has exceeded its maximum claim.\n");
      return false;
    }
  }

  // Check if request is less than available
  for (int i = 0; i < R; i++) {
    if (request[i] > available[i]) {
      printf("Error: Resources not available.\n");
      return false;
    }
  }

  // Pretend to allocate requested resources
  for (int i = 0; i < R; i++) {
    available[i] -= request[i];
    allocation[process][i] += request[i];
    need[process][i] -= request[i];
  }

  // Check if the system is in a safe state
  if (isSafe()) {
    return true;
  } else {
    // Revert allocation if not safe
    for (int i = 0; i < R; i++) {
      available[i] += request[i];
      allocation[process][i] -= request[i];
      need[process][i] += request[i];
    }
    printf("Error: System would not be safe.\n");
    return false;
  }
}

int main() {
  int process = 1;            // Example process making the request
  int request[R] = {1, 0, 2}; // Example request

  if (requestResources(process, request)) {
    printf("The request can be granted.\n");
  } else {
    printf("The request cannot be granted.\n");
  }

  return 0;
}
