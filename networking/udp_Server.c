
// UDP server in C

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
  int server_fd;
  struct sockaddr_in server_address, client_address;
  char buffer[MAX_BUFFER_SIZE];
  socklen_t client_len = sizeof(client_address);

  // Create socket
  if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Set up server address
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to the address and port
  if (bind(server_fd, (struct sockaddr *)&server_address,
           sizeof(server_address)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }

  printf("UDP server is listening on port %d...\n", PORT);

  // Wait for incoming messages from client
  while (1) {
    ssize_t len = recvfrom(server_fd, buffer, MAX_BUFFER_SIZE, 0,
                           (struct sockaddr *)&client_address, &client_len);
    if (len < 0) {
      perror("Recvfrom failed");
      continue;
    }

    buffer[len] = '\0'; // Null-terminate the received data
    printf("Received message from client: %s\n", buffer);

    // Send the response back to the client
    const char *response = "Hello from server!";
    if (sendto(server_fd, response, strlen(response), 0,
               (struct sockaddr *)&client_address, client_len) < 0) {
      perror("Sendto failed");
    }
  }

  close(server_fd);
  return 0;
}
