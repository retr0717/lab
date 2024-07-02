#include <stdbool.h>
#include <stdio.h>

int n, m, i, j, k, alloc[20][20], max[20][20], avail[50];

void Change() {
  int work[m];    // Work array to keep track of available resources
  int safeseq[n]; // Safe sequence array
  int finish[n];  // Finish array to keep track of finished processes
  int ind = 0;    // Index for safe sequence
  int need[n][m]; // Need matrix

  // Initialize the finish array to 0
  for (int i = 0; i < n; i++) {
    finish[i] = 0;
  }

  // Initialize the work array with available resources
  for (int i = 0; i < m; i++) {
    work[i] = avail[i];
  }

  // Initialize the safeseq array to avoid garbage values
  for (int i = 0; i < n; i++) {
    safeseq[i] = -1; // -1 indicates uninitialized state
  }

  // Calculate the need matrix (maximum - allocation)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }

  // Print allocation matrix
  printf("\nAllocation Matrix: \n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", alloc[i][j]);
    }
    printf("\n");
  }

  // Print max matrix
  printf("\nMax Matrix: \n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", max[i][j]);
    }
    printf("\n");
  }

  // Print need matrix
  printf("\nNeed Matrix: \n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", need[i][j]);
    }
    printf("\n");
  }

  // Print available matrix
  printf("\nAvailable Matrix: \n");
  for (int i = 0; i < m; i++) {
    printf("%d  ", work[i]);
  }

  // Banker's Algorithm to find the safe sequence
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      if (finish[i] == 0) {
        // Check if the resource need can be satisfied with available resources
        int flag = 0;
        for (int j = 0; j < m; j++) {
          if (need[i][j] > work[j]) {
            flag = 1;
            break;
          }
        }

        // If the resource need <= available resources
        if (flag == 0) {
          // Add the process to the safe sequence
          safeseq[ind++] = i;

          // Add released resource instances to available (work)
          for (int j = 0; j < m; j++) {
            work[j] += alloc[i][j];
          }

          // Print the current state of the work array
          printf("\n");
          for (int j = 0; j < m; j++) {
            printf("%d  ", work[j]);
          }

          finish[i] = 1;
        }
      }
    }
  }

  // Print the safe sequence
  printf("\n\nSafe sequence: ");
  for (int i = 0; i < n; i++) {
    if (safeseq[i] != -1) {
      printf("%d  ", safeseq[i]);
    }
  }
  printf("\n");
}

int main() {

  // Read number of processes
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  // Read number of resources
  printf("\nEnter the number of resources: ");
  scanf("%d", &m);

  printf("\n n: %d | m: %d", n, m);

  // Read allocation matrix
  printf("\nEnter the allocation matrix:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &alloc[i][j]);

  // Read max matrix
  printf("\nEnter the max matrix:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &max[i][j]);

  // Read available matrix
  printf("\nEnter the available matrix:\n");
  for (i = 0; i < m; i++)
    scanf("%d", &avail[i]);

  // Call the Change function to determine the safe sequence
  Change();

  // Read the request
  int request[m];
  printf("\nEnter the request for resources:\n");
  for (int i = 0; i < m; i++) {
    scanf("%d", &request[i]);
  }

  // Resource allocation algorithm to predict if deadlock occurs or not
  int pid;
  printf("\nEnter the requesting process number: ");
  scanf("%d", &pid);

  // Implementing resource request algorithm
  int need[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      need[i][j] = max[i][j] - alloc[i][j];
    }
  }

  int canAllocate = 1;
  for (int i = 0; i < m; i++) {
    if (request[i] > need[pid][i] || request[i] > avail[i]) {
      canAllocate = 0;
      break;
    }
  }

  if (canAllocate) {
    for (int i = 0; i < m; i++) {
      avail[i] -= request[i];
      alloc[pid][i] += request[i];
      need[pid][i] -= request[i];
    }
    printf("The request can be granted.\n");
    Change();

  } else {
    printf("The request cannot be granted.\n");
  }

  return 0;
}

/*
 Allocation Matrix: 
2 0 0 1 
4 2 2 1 
2 1 0 3 
1 3 1 2 
1 4 3 2 

Max Matrix: 
4 2 1 2 
5 2 5 2 
2 3 1 6 
1 4 2 4 
3 6 6 5 

Need Matrix: 
2 2 1 1 
1 0 3 1 
0 2 1 3 
0 1 1 2 
2 2 3 3 

Available Matrix: 
2  2  2  1  
4  2  2  2  
5  5  3  4  
6  9  6  6  
10  11  8  7  
12  12  8  10  

Safe sequence: 0  3  4  1  2  

 * */
