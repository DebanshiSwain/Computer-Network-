#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define TRUE 1

int main()
{
    int soc, chpid, msgsock;
    socklen_t len;
    char buf[1024], buf1[1024];
    struct sockaddr_in server, client;
    socklen_t addrlen = sizeof(client);

    /* First call to socket() function */
    soc = socket(AF_INET, SOCK_STREAM, 0);

    if (soc < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    // ---Configure settings of the server address structure---

    Name: Debanshi Swain
    Section: CSE B2
    SIC: 24BCSF25
    Roll No: 23
    Date: 02/09/26

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = 0; // OS assigns an available ephemeral port automatically

    /* Now bind the host address using bind() call */
    if (bind(soc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    /* Get and display the dynamically assigned port number */
    len = sizeof(server);

    if (getsockname(soc, (struct sockaddr *)&server, &len) < 0)
    {
        perror("\nError in getting port...");
        exit(3);
    }

    printf("\nSocket has port no: %d\n", ntohs(server.sin_port));

    /* Start listening for incoming connections */
    listen(soc, 5);

    signal(SIGCHLD, SIG_IGN); // Prevent zombie process creation on child exit

    do
    {
        /* Accept connection from client */
        msgsock = accept(soc, (struct sockaddr *)&client, &addrlen);

        if (msgsock == -1)
        {
            perror("\nError in accept...");
            exit(0);
        }
        else
        {
            {
                if ((chpid = fork()) == 0)
                // Child process
                close(soc); // Close listening socket in child

                do
                {
                    memset(buf, 0, sizeof(buf));

                    ssize_t bytes_read = read(msgsock, buf, sizeof(buf) - 1);

                    if (bytes_read <= 0) break; // Client disconnected or error

                    Name: Debanshi Swain
                    Section: CSE B2
                    SIC: 24BCSF25
                    Roll No: 23
                    Date: 02/09/26

                    printf("\nMessage from client: %s\n", buf);
                    printf("\nMessage to client: ");

                    scanf(" %[^\n]", buf1);

                    write(msgsock, buf1, strlen(buf1) + 1);

                } while (strcmp(buf1, "bye") != 0);

                close(msgsock);
                exit(0);
            }
            else
            {
                // Parent process
                close(msgsock); // Close connected socket in parent
            }
        }

    } while (TRUE);

    close(soc);
    return 0;
}
