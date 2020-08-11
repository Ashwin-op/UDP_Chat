#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int serverSocket, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    serverSocket = socket(PF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    addr_size = sizeof serverStorage;

    while (1)
    {
        nBytes = recvfrom(serverSocket, buffer, 1024, 0, (struct sockaddr *)&serverStorage, &addr_size);

        printf("Received from client: %s\n", buffer);

        printf("Type a sentence to send to client: ");
        fgets(buffer, 1024, stdin);
        // printf("You typed: %s\n", buffer);

        nBytes = strlen(buffer) + 1;

        sendto(serverSocket, buffer, nBytes, 0, (struct sockaddr *)&serverStorage, addr_size);
    }

    return 0;
}