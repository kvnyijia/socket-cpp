#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include <arpa/inet.h>      // Needed by inet_addr
using namespace std;

int main() {
  // Step 0: Determine the server address and port number
  int PORT_NUMBER = 8080;
  const char *SERVER_ADDRESS = "127.0.0.1";

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
  // serverAddr.sin_addr.s_addr = INADDR_ANY;             //IP
  socklen_t serverAddrLen = sizeof(serverAddr);

  // Step 3: Bind the socket to the server address and port number
  int status = (int) bind(sockfd, (struct sockaddr *)&serverAddr, serverAddrLen);
  if (status < 0) {
    std::cerr << "Error binding socket to server address" << std::endl;
    return 1;
  }

  // Step 4: Listen for incoming connections
  status = listen(sockfd, SOMAXCONN);
  if (status < 0) {
    std::cerr << "Error listening for incoming connections" << std::endl;
    return 1;
  }

  while (true) {
    // Step 5: Accept incoming connections and handle them
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSockfd < 0) {
      std::cerr << "Error accepting incoming connection" << std::endl;
      continue;
    }

    // Step 6: Handle incoming data from the client
    char buffer[1024];
    int recvSize = recv(clientSockfd, buffer, sizeof(buffer), 0);
    if (recvSize < 0) {
      std::cerr << "Error receiving data from client" << std::endl;
      close(clientSockfd);
      continue;
    }
    buffer[recvSize] = '\0';
    std::cout << "Received message from client: " << buffer << std::endl;

    // Step 7: Send a response back to the client
    const char *response = "Hiiiiiiiiii, client!";
    int responseLen = strlen(response);
    status = send(clientSockfd, response, responseLen, 0);
    if (status < 0) {
      std::cerr << "Error sending data to client" << std::endl;
      close(clientSockfd);
      continue;
    }

    // Step 8: Close the connection with the client
    close(clientSockfd);
  }
  
  // Step 9: Close the server socket
  close(sockfd);

  return 0;
}

/*
int main() {
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT_NUMBER);
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
  // serverAddr.sin_addr.s_addr = INADDR_ANY;             //IP


  connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
  char buffer[1024] = "Hello, server!";
  send(sockfd, buffer, strlen(buffer), 0);

  char buffer2[1024];
  int recvSize = recv(sockfd, buffer2, sizeof(buffer2), 0);
  buffer2[recvSize] = '\0';
  std::cout << "Received message from server: " << buffer2 << std::endl;

  close(sockfd);
}

*/