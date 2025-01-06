
// UDP client in C

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1" // IP address of the server (localhost)
#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
  int sock;
  struct sockaddr_in server_address;
  char buffer[MAX_BUFFER_SIZE];

  // Create socket
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Set up server address
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  // Convert IP address to binary format
  if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0) {
    perror("Invalid address or address not supported");
    exit(EXIT_FAILURE);
  }

  // Send message to server
  const char *message = "Hello from client!";
  if (sendto(sock, message, strlen(message), 0,
             (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
    perror("Sendto failed");
    exit(EXIT_FAILURE);
  }

  printf("Message sent to server: %s\n", message);

  // Receive the response from the server
  ssize_t len = recvfrom(sock, buffer, MAX_BUFFER_SIZE, 0, NULL, NULL);
  if (len < 0) {
    perror("Recvfrom failed");
    exit(EXIT_FAILURE);
  }

  buffer[len] = '\0'; // Null-terminate the received data
  printf("Message from server: %s\n", buffer);

  close(sock);
  return 0;
}
