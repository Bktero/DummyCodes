#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>     /* for size_t */
#include <sys/types.h>
#include <errno.h>

#include <winsock2.h>
#include <ws2tcpip.h> /* pour getaddrinfo() */


#define PORT 80

#define PRINT_ERRNO printf("Errno = %d = %s.\n", errno, strerror(errno))
#define PRINT_WSA_ERROR printf("Erreur WSA = %d.\n", WSAGetLastError())

#define TAILLE_BUFFER_RECEPTION 1024

/* Ce programme se connecte a un site internet
et recupere une page grace a une requete http 'GET'.
Il enregistre le contenu de cette page dans le fichier ./page.html
*/

int
demarrer_sockets_windows(void)
{
    int err = 0;
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2); // WORD et MAKEWORD sont definis dans windef.h

    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0)
    {
        printf("La fonction WSAStartup a echoue.\n");
        PRINT_WSA_ERROR;
        return err;
    }
    else if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Probleme de version des sockets Winsock. "
               "Version demandee : 2.2 ; version obtenue %d.%d\n",
                LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
        return 1;
    }
    else
    {
        printf("WSAStarup OK avec Winsock en version 2.2.\n");
        return 0;
    }
}

void
eteindre_sockets_windows(void)
{
    // Dechargement de la DLL socket windows
    if( WSACleanup() == SOCKET_ERROR)
        printf("WSACleanup KO, mais on ferme quand meme.\n");
}

SOCKET*
connexion_a(const char *hostname)
{
    SOCKET *psock = NULL;
    struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin;
    memset( &sin, 0, sizeof(sin)); // mettre tous les champs a 0

    // Creation du socket
    if( (psock = malloc(sizeof(SOCKET)) ) == NULL )
    {
        printf("Erreur d'allocation memoire pour le socket.\n");
        PRINT_ERRNO;
        return NULL;
    }

    if( (*psock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET )
    {
        printf("Creation impossible du socket.\n");
        PRINT_ERRNO;
        return NULL;
    }

    // Recuperation des informations sur le serveur (conversion URL -> IP)
    if( (hostinfo = gethostbyname(hostname))== NULL )
    {
        printf ("Erreur : l'hote %s n'est pas reconnu.\n", hostname);
        PRINT_WSA_ERROR;
        return NULL;
    }

    #warning "La fonction gethostbyname est depreciee. Il faut la remplacer par getaddrinfo"
    /*
    // http://www.developpez.net/forums/d1239023-2/c-cpp/c/debuter/recuperer-page-web/#post6782938
    struct addrinfo *info_about_host = NULL;
    int err_wsa =  0;
    getaddrinfo(hostname, NULL, NULL, &info_about_host);
    */

    // Connexion du socket sur la structure adrese
    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; // l'adresse se trouve dans le champ h_addr de la structure hostinfo
    sin.sin_port = htons(PORT); // on utilise htons pour le port
    sin.sin_family = AF_INET;

    if(connect(*psock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        printf("Erreur lors de la connexion.\n");
        PRINT_ERRNO;
        return NULL;
    }

    printf("Connexion reussie a %s.\n", hostname);
    return psock;
}

int main(int argc, char *argv[])
{
    argv=NULL;
    argc=0;

    SOCKET *psock = NULL;

    /**********************************************************************************************/
    /** L'utilisateur initialise ces 2 variables a sa convenance **********************************/
    //const char *hote = "http://www.developpez.com";
    const char *hote = "http://www.developpez.com";

    const char *commande_get = "GET /actu/45408/jQuery-2-ne-supportera-plus-les-versions-obsoletes-d-IE-la-branche-1-9-continuera-d-exister-en-parallele/ HTTP/1.1 \n"
    "Host: www.developpez.com\n\n";

    // Voir http://www.developpez.net/forums/d1239023-2/c-cpp/c/debuter/recuperer-page-web/#post6780524
    /**********************************************************************************************/


    // Pour commencer
    if( demarrer_sockets_windows() != 0)
    {
        puts("Impossible de demarrer la bibliotheque de sockets.\n");
        return EXIT_FAILURE;
    }

    // Connexion
    if( (psock = connexion_a(hote)) == NULL)
    {
        puts("Impossible de se connecter a l'hote.\n");
        return EXIT_FAILURE;
    }

    // Recuperation de la page
    if( send(*psock, commande_get, (int)strlen(commande_get)+1, 0) < 0)
    {
        printf("Erreur lors de l'envoi de la commande.\n");
        PRINT_ERRNO;
        return errno;
    }

    char buffer[TAILLE_BUFFER_RECEPTION+1] = {0};
    int nb_recus = TAILLE_BUFFER_RECEPTION;

    FILE *fichier = fopen("page.html", "w");
    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier pour sauvegarder les donnes.\n");
        PRINT_ERRNO;
        return errno;
    }

    while(nb_recus==TAILLE_BUFFER_RECEPTION)
    {
        // Reception tant que des donnes sont disponibles dans le socket
        // Si on recoit moins de TAILLE_BUFFER_RECEPTION,
        // alors cela sous entend qu'il n'y a plus rien a lire
        nb_recus = recv(*psock, buffer, TAILLE_BUFFER_RECEPTION, 0);

        if(nb_recus < 0)
        {
            printf("Erreur lors de la reception des donnees.\n");
            PRINT_ERRNO;
            return errno;
        }
        else
        {
            // Ecriture dans le fichier de sortie
            size_t nb_ecrits = fwrite(buffer, 1, (size_t)nb_recus, fichier);
            printf("Recus dans le buffer : %d ;"
                   " sauvegardes dans le fichier : %d.\n", nb_recus, nb_ecrits);
        }
    }

    // Pour finir
    fclose(fichier);
    closesocket(*psock);
    free(psock);
    eteindre_sockets_windows();
    puts("Fin acces succes !");

    return 0;
}

