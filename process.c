#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int child_status;
  if (fork() == 0) {
    printf("Hello from child \n");
    exit(0);
  } else {
    printf("Hello from parent \n");
    wait(&child_status);
    printf("Child has terminated\n");
  }
  return 0;
}

/*int main() {
  printf("L0\n");
  if (fork() == 0) {
    printf("Entered first fork\n");
    printf("L1\n");
  }
  if (fork() == 0) {
    printf("Entered second fork\n");
    printf("L2\n");
  }

  printf("Bye\n");
}*/

/*int main() {
  pid_t child_pid;
  int n = 5;
  for (int i = 0; i < n; i++) {
    printf("parent process %d \n", getppid());
    child_pid = fork();
    printf("parent process %d \n", getppid());
    if (child_pid < 0) {
      printf("Error on creating child process\n");
      exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
      printf("child process %d is created by parent process %d\n", getpid(),
             getppid());

      exit(EXIT_SUCCESS);
    }
  }

  for (int i = 0; i < n; i++) {
    wait(NULL);
    printf("Parent process %d is finished creating child process %d\n",
           getppid(), getpid());
  }

  return 0;
}
*/

/*int main() {
  int parent_pid, child_pid;
  child_pid = fork();

  if (child_pid < 0) {
    printf("Fork failed");
  } else if (child_pid == 0) {
    printf("Child process hello %d\n", getpid());
  } else {
    printf("Parent pid %d\n", getppid());
    wait(NULL);
    printf("child process exited\n");
    printf("Child process %d parent pid : %d\n", getpid(), getppid());
  }
}
*/
