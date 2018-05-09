#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

    int fd1, fd2;
    int fdc1, fdc2;
    int flags = 0;
    struct sockaddr_in server1, server2;
    struct sockaddr_in client1, client2;
    unsigned int server_size = sizeof(server1);
    unsigned int client_size = sizeof(client1);
    int bytes = 512;
    int rcvsize;
    int trnmsize;
    int err;
    char on = 1;
    char buffer[512];

    int port1 = 2001;
    int port2 = 2002;


    server1.sin_family = server2.sin_family = AF_INET;              //IPv4
    server1.sin_addr.s_addr = server2.sin_addr.s_addr = INADDR_ANY;
    server1.sin_port = htons(port1);
    server2.sin_port = htons(port2);

    if (argc != 1)
        printf("Nem kell semmilyen paraméter");

    //Socket létrehozása
    fd1 = socket(AF_INET, SOCK_STREAM, 0 );
    if (fd1 < 0)
    {
        printf("%s: Socket creation error\n",argv[0]);
        exit(1);
    }
    fd2 = socket(AF_INET, SOCK_STREAM, 0 );
    if (fd2 < 0)
    {
        printf("%s: Socket creation error\n",argv[0]);
        exit(1);
    }
    printf("Socketek létrehozva\n");

    //Socket beállítások
    setsockopt(fd1, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
    setsockopt(fd1, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

    setsockopt(fd2, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
    setsockopt(fd2, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);
    printf("Socketek beállítva\n");

    //Binding socket
    err = bind(fd1, (struct sockaddr *) &server1, server_size);
    if (err < 0)
    {
        printf("%s: Cannot bind to the socket\n",argv[0]);
        exit(2);
    }
    err = bind(fd2, (struct sockaddr *) &server2, server_size);
    if (err < 0)
    {
        printf("%s: Cannot bind to the socket\n",argv[0]);
        exit(2);
    }
    printf("Socket binding\n");

    //Listening
    err = listen(fd1, 10);
    if (err < 0) {
        printf("%s: Cannot listen to the socket\n",argv[0]);
        exit(3);
    }

    // Accepting connection request
    fdc1 = accept(fd1, (struct sockaddr *) &client1, &client_size);
    if (fdc1 < 0)
    {
        printf("%s: Cannot accept on socket\n",argv[0]);
        exit(4);
    }
    printf("Egyes játékos csatlakozva\n");
    //Listening
    err = listen(fd2, 10);
    if (err < 0) {
        printf("%s: Cannot listen to the socket\n",argv[0]);
        exit(3);
    }

    // Accepting connection request
    fdc2 = accept(fd2, (struct sockaddr *) &client2, &client_size);
    if (fdc2 < 0)
    {
        printf("%s: Cannot accept on socket\n",argv[0]);
        exit(4);
    }
    printf("Kettes játékos csatlakozva\n");

    char kilepes = 'n';
    while (kilepes == 'n')
    {
        //Egyes játékos küld
        rcvsize = recv( fdc1, buffer, bytes, flags );
        if (rcvsize < 0)
        {
            printf("%s: Cannot receive from the socket\n",argv[0]);
            exit(5);
        }
        printf("Egyes: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            printf("buffer: %s", buffer);
            printf("Kilépés\n");
            kilepes = 'i';
        }

        bytes = strlen(buffer) + 1;
        //Továbbítás kettes játékosnak
        trnmsize = send(fdc2, buffer, bytes, flags);
        if (trnmsize < 0)
        {
            printf("%s: Cannot send data to the client.\n",argv[0]);
            exit(6);
        }

        //Kettes játékos küld
        rcvsize = recv( fdc2, buffer, bytes, flags );
        if (rcvsize < 0)
        {
            printf("%s: Cannot receive from the socket\n",argv[0]);
            exit(5);
        }
        printf("Kettes: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0)
        {
            printf("buffer: %s", buffer);
            printf("Kilépés\n");
            kilepes = 'i';
        }

        bytes = strlen(buffer) + 1;
        //Továbbítás egyes játékosnak
        trnmsize = send(fdc1, buffer, bytes, flags);
        if (trnmsize < 0)
        {
            printf("%s: Cannot send data to the client.\n",argv[0]);
            exit(6);
        }

    }

    close(fd1);
    close(fd2);
    close(fdc1);
    close(fdc2);

    return 0;
}
