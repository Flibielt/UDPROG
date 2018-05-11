#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

struct jatek{
    char terkep[10][10];
    int hajok[5][5];    //A hajók koordinátái: 1. koordináta X, Y; 2. koordináta X, Y
                        //5. elem: 2- életben van, 1- egy találat, 0- süllyedt
    int elet;
};

void kiir(struct jatek*, struct jatek*);               //A térkép kiiratása
void terkepFelallitasa(struct jatek*);
void hajokElhelyezese(struct jatek*, struct jatek*);
char loves(struct jatek*, int, int);    //Lövés (X, Y) koordinátára
void koordinataAtalakitas(int*, int*);
void koordinataBekeres(struct jatek* , struct jatek* , int* , int* );

int main(int argc, char* argv[])
{
    int fd;
    int flags = 0;
    struct sockaddr_in server;
    int server_size = sizeof(server);
    int bytes;
    int rcvsize;
    int trnmsize;
    int err;
    int ip;
    char on = 1;
    char buffer[512];
    char server_addr[16];


    int port1 = 2001;
    int port2 = 2002;

    if (argc != 3)
    {
        printf("Használat: ./kliens serverIP hanyas játékos\n");
        return 0;
    }

    sprintf(server_addr, "%s", argv[1]);
    ip = inet_addr(server_addr);
    server.sin_family = AF_INET;    //IPv4
    server.sin_addr.s_addr = ip;
    //integert átalakítja host byte orderből network byte orderre


    if (argv[2][0] == '1')
    {
        printf("Egyes\n");
        server.sin_port = htons(port1);     //host byte order to network byte order
    }
    else
    {
        printf("Kettes\n");
        server.sin_port = htons(port2);
    }

    //Socket Létrehozás
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        printf("%s: Socket creation error\n", argv[0]);
        exit(1);
    }

    //Socket beállítások
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);
    setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&on, sizeof on);

    //Sockethez kapcsolódás
    err = connect(fd, (struct sockaddr *) &server, server_size);
    if (err < 0)
    {
        printf("%s: Cannot connect to the server\n", argv[0]);
        exit(2);
    }


    struct jatek sajat, ellenfel;
    terkepFelallitasa(&sajat);
    terkepFelallitasa(&ellenfel);
    hajokElhelyezese(&ellenfel, &sajat);
    kiir(&ellenfel, &sajat);


    //Ha a játékos azt írja be, hogy exit, akkor a kilepes i-re változik
    char kilepes = 'n';
    int x, y;
    x = -1;
    y = -1;

    if (argv[2][0] == '1')   //Ha ő az egyes játékos
    {
        /*
        system("clear");
        kiir(&ellenfel, &sajat);
        printf("Ellenfél élete: %d\t\t", ellenfel.elet);
        printf("Saját élet: %d\n", sajat.elet);
        printf("\nAdj meg egy X koordinátát [1-10]: ");
        scanf("%d", &x);
        if (x == -1)
            printf("Kilépés\n");

        else
        {
            while ( x < 1 || x > 11)
            {
                system("clear");
                kiir(&ellenfel, &sajat);
                printf("Nem megfelelő koordináta!\n");
                printf("Adj meg egy X koordinátát [1-10]: ");
                scanf("%d", &x);
            }
        }
        printf("Adj meg egy Y koordinátát [1-10]: ");
        scanf("%d", &y);
        if (y == -1)
            printf("Kilépés\n");
        else
        {
            while ( y < 1 || y > 11)
            {
                system("clear");
                kiir(&ellenfel, &sajat);
                printf("X koordináta: %d\n", x);
                printf("Nem megfelelő koordináta!\n");
                printf("Adj meg egy Y koordinátát [1-10]: ");
                scanf("%d", &y);
            }
        }
        system("clear");
        */
        koordinataBekeres(&ellenfel, &sajat, &x, &y);

        if (x == -1 || y == -1)
        {
            sprintf(buffer, "exit");
            kilepes = 'i';
        }
        else
        {
            koordinataAtalakitas(&x, &y);

            sprintf(buffer, "%d%d%c", x, y, 'n');
            printf("Lövés: %s\n", buffer);
        }


        bytes = strlen(buffer) + 1;

        ///Küldés
        trnmsize = send(fd, buffer, bytes, flags);
        if (trnmsize < 0)
        {
            printf("%s: Cannot send data to the server\n", argv[0]);
            exit(3);
        }

    }

    ///Most már szinkronban van a kettő

    char ellensegesLoves = 'n';

    while (ellenfel.elet != 0 && sajat.elet != 0 && kilepes == 'n')
    {       

        rcvsize = -1;
        while (rcvsize < 0)
        {
            system("clear");
            printf("Az ellenfél következik!\n");
            rcvsize = recv(fd, buffer, bytes, flags);
        }
        system("clear");


        if (strcmp(buffer, "exit") == 0)
        {
            kilepes = 'i';
            printf("Az ellenfél feladata\n");
        }
        else
        {
            ///Ekkor az x és az y még az előző lövésünk koordinátáit tartalmazzák
            if (x != -1)    //A kettes játékosnál csak a 2. körtől kell ellenőrizni
            {
                if (buffer[2] == 'n')
                {
                    ellenfel.terkep[x][y] = '-';
                    printf("Nem talált!\n");
                }
                else
                {
                    ellenfel.terkep[x][y] = 'X';
                    ellenfel.elet--;
                    if (buffer[2] == 't')
                        printf("Találat!\n");
                    else
                        printf("Ellenséges hajó elsüllyesztve!\n");
                }
            }


            //Minden karakter átalakítható integerré, de az ANSI kód lesz az érték
            //Ezért ki kell vonni a 0-t, mert így megkapjuk a szám értéket és nem az ANSI kódját
            x = buffer[0] - '0';
            y = buffer[1] - '0';
            ///Most már az ellenfél lövésének a koordinátái vannak az x és y-ban
            ellensegesLoves = loves(&sajat, x, y);


            if(sajat.elet > 0 || ellenfel.elet > 0)
            {
                koordinataBekeres(&ellenfel, &sajat, &x, &y);

                if ( x == -1 || y == -1)
                {
                    sprintf(buffer, "exit");
                    kilepes = 'i';
                }
                else
                {
                    koordinataAtalakitas(&x, &y);

                    sprintf(buffer, "%d%d%c", x, y, ellensegesLoves);
                    printf("Lövés: %s\n", buffer);
                }


                bytes = strlen(buffer) + 1;

                ///Küldés
                trnmsize = send(fd, buffer, bytes, flags);
                if (trnmsize < 0)
                {
                    printf("%s: Cannot send data to the server\n", argv[0]);
                    exit(3);
                }
            }

        }


    }

    if (sajat.elet != 0 && strcmp(buffer, "exit") != 0)
    {
        printf("Győzelem!\n");
    }
    else if (sajat.elet == 0)
    {
        printf("Vereség!\n");

    }


    //Kapcsolat bontása
    close(fd);
    return 0;
}


void kiir(struct jatek *g, struct jatek *s)
{
    printf("\tEllenfél\t\t\tSaját\n");
    for (int i = 0; i < 2; i++)
    {
        for (int x = 1; x < 11; x++)
            printf("%d ", x);
        printf("\t\t");
    }
    printf("\n");

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
            printf("%c ", g -> terkep[x][y]);
        printf("%d\t\t" , 10 - x);


        for (int y = 0; y < 10; y++)
            printf("%c ", s->terkep[x][y]);
        printf("%d  ", 10 - x);
        printf("\n");
    }

}

void terkepFelallitasa(struct jatek * s)
{
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
            s->terkep[x][y] = 'O';
    }

    s->elet = 10;
}

char loves(struct jatek* s, int x, int y)
{


    printf("Lövés: [%d][%d] koordinátára\n", x, y);
    if(s->terkep[x][y] == 'H')
    {
        int hajoIndex = 0;  //Az eltalált hajó indexe
        s->terkep[x][y] = 'X';

        for( int i = 0; i < 5; i++)
        {
            if (s->hajok[i][0] == x)
            {
                if (s->hajok[i][1] == y)
                {
                    printf("Találat!\n");
                    s->hajok[i][4]--;
                    hajoIndex = i;
                }
            }
            else if (s->hajok[i][2] == x)
            {
                if (s->hajok[i][3] == y)
                {
                    printf("Találat!\n");
                    s->hajok[i][4]--;
                    hajoIndex = i;
                }
            }

        }

        if (s->hajok[hajoIndex][4] == 0)
        {
            printf("Hajó elsüllyesztve!\n");
            return 's';
        }
        s->elet--;
        return 't';     //Csak szimplán találat
    }
    else
    {
        printf("Nincs találat.\n");
        if(s->terkep[x][y] == 'O')
            s->terkep[x][y] = '-';
        return 'n';
    }
}

void hajokElhelyezese(struct jatek* g, struct jatek* s)
{
    int x, y, felhasznaloiX, felhasznaloiY = 0;
    char tablanVan = 'i';

    for (int i = 0; i < 5; i++)
    {

        for (int k = 0; k < 2; k++)
        {
            system("clear");
            kiir(g, s);
            printf("%d. hajó:\n", i + 1);
            printf("%d. rész:\n", k + 1);
            printf("Adj meg egy X koordinátát: ");
            scanf("%i", &felhasznaloiX);
            printf("Adj meg egy Y koordinátát: ");
            scanf("%i", &felhasznaloiY);
            x = 10 - felhasznaloiY;
            y = --felhasznaloiX;

            //A játékos nem helyezhet egynél több hajót egy helyre és
            //a hajóknak egybefüggőknek kell lenniük

            if(x < 0 || x > 9 || y < 0 || y > 9)
                tablanVan = 'n';

            while(s->terkep[x][y] == 'H' || (k == 1 && ((abs(s->hajok[i][0] - x) + abs(s->hajok[i][1] - y)) != 1)) || tablanVan != 'i')
            {
                system("clear");
                kiir(g, s);
                printf("%d. hajó:\n", i + 1);
                printf("%d. rész:\n", k + 1);
                printf("Ez a koordináta nem megfelelő!\n");
                if(s->terkep[x][y] == 'H')
                {
                    printf("Ez a koordináta már foglalt!\n");
                }
                else if (tablanVan != 'i')
                {
                    printf("A koordináta nincs a táblán\n");
                }
                else
                {
                    printf("A hajó egybefüggő kell, hogy legyen!\n");
                }
                printf("Adj meg egy X koordinátát: ");
                scanf("%i", &felhasznaloiX);
                printf("Adj meg egy Y koordinátát: ");
                scanf("%i", &felhasznaloiY);
                x = 10 - felhasznaloiY;
                y = --felhasznaloiX;

                if(x < 0 || x > 9 || y < 0 || y > 9)
                    tablanVan = 'n';
                else
                    tablanVan = 'i';
            }

            s->hajok[i][0+(2*k)] = x;
            s->hajok[i][1+(2*k)] = y;
            s->terkep[x][y] = 'H';
        }
    }
    system("clear");
}

void koordinataAtalakitas(int* x, int* y)
{
    int userX, userY;
    userX = *x;
    userY = *y;

    *x = 10 - userY;
    *y = --userX;
}

void koordinataBekeres(struct jatek *g, struct jatek *s, int *x, int *y)
{
    system("clear");
    kiir(g, s);
    printf("Ellenfél élete: %d\t\t", g->elet);
    printf("Saját élet: %d\n", s->elet);
    printf("\nAdj meg egy X koordinátát [1-10]: ");
    scanf("%d", x);
    if (*x == -1)
        printf("Kilépés\n");

    else
    {
        while ( *x < 1 || *x > 10)
        {
            system("clear");
            kiir(g, s);
            printf("Nem megfelelő koordináta!\n");
            printf("Adj meg egy X koordinátát [1-10]: ");
            scanf("%d", x);
        }

        printf("Adj meg egy Y koordinátát [1-10]: ");
        scanf("%d", y);
        if (*y == -1)
            printf("Kilépés\n");

        else
        {
            while ( *y < 1 || *y > 10)
            {
                system("clear");
                kiir(g, s);
                printf("X koordináta: %d\n", *x);
                printf("Nem megfelelő koordináta!\n");
                printf("Adj meg egy Y koordinátát [1-10]: ");
                scanf("%d", y);
            }
        }

    }

}

