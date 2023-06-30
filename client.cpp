#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[]) {
  // Step 0: Determine the server address and port number
  int PORT_NUMBER = 8080;
  char *SERVER_ADDRESS = "127.0.0.1";
  if (argc > 1) {
    SERVER_ADDRESS = (char *) malloc(strlen(argv[1])+1);
    strcpy(SERVER_ADDRESS, argv[1]);
  }

  // Step 1: Create a TCP socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Step 2: Set the server address and port number
  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT_NUMBER);
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

  // Step 3: Connect to the server
  int status = connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  if (status < 0) {
    std::cerr << "Error connecting to server" << std::endl;
    return 1;
  }

  // Step 4: Send data to the server
  const char *message = "Hellooooooooooo, server!";
  int messageLen = strlen(message);
  status = send(sockfd, message, messageLen, 0);
  if (status < 0) {
    std::cerr << "Error sending data to server" << std::endl;
    return 1;
  }

  // Step 5: Receive data from the server
  char buffer[1024];
  int recvSize = recv(sockfd, buffer, sizeof(buffer), 0);
  if (recvSize < 0) {
    std::cerr << "Error receiving data from server" << std::endl;
    return 1;
  }
  buffer[recvSize] = '\0';
  std::cout << "Received message from server: " << buffer << std::endl;

  // Step 6: Close the socket
  close(sockfd);

  return 0;
}
