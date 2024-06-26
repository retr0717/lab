#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 5, x = 0;
int buffer[5];

void producer() {
  --mutex;
  ++full;
  --empty;
  printf("\nEnter Producer Value : %d", x);
  scanf("%d", &x);
  buffer[full] = x;
  ++mutex;
}

void consumer() {
  --mutex;
  x = buffer[full];
  printf("\nConsumer consumes item %d", x);
  ++empty;
  --full;
  ++mutex;
}

int main() {
  int i, n;
  printf("\n1. Press 1 for producer\n2. Press 2 for consumer\n3.Press 3 for "
         "exit\n");

  for (i = 1; i > 0; i++) {
    printf("\nEnter the choice : ");
    scanf("%d", &n);

    switch (n) {
    case 1:
      if ((mutex == 1) && (empty != 0)) {
        producer();
      } else {
        printf("Buffer is full");
      }
      break;
    case 2:
      if ((mutex == 1) && (full != 0)) {
        consumer();
      } else {
        printf("Buffer is empty!");
      }
      break;
    case 3:
      exit(0);
    default:
      printf("\nInvalid Option\n");
      break;
    }
  }
  return 0;
}
