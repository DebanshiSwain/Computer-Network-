#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <IP_Address> <Port_Number>\n", argv[0]);
        exit(1);
    }

    int sockfd;
    char buf[1024];
    struct sockaddr_in server;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0)
    {
        perror("Error in opening socket");
        exit(1);
    }

    // Name: Debanshi Swain
    // Section: CSE B2
    // SIC: 24BCSF25
    // Roll No: 23
    // Date: 08/09/26

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));

    while (1)
    {
        printf("Enter the Message: ");

        if (fgets(buf, sizeof(buf), stdin) == NULL)
        {
            break;
        }

        buf[strcspn(buf, "\n")] = '\0';

        if (strcmp(buf, "exit") == 0)
        {
            printf("Closing client...\n");
            break;
        }

        int sent_bytes = sendto(sockfd, buf, strlen(buf) + 1, 0,
                                (struct sockaddr *)&server,
                                sizeof(server));

        if (sent_bytes < 0)
        {
            perror("Send failed");
        }
    }

    close(sockfd);
    return 0;
}
