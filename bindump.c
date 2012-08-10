#include <stdio.h>
#include<stdlib.h>
#include <errno.h>
#include <string.h>

typedef unsigned char octet_t;

void
print_octet_as_bin(octet_t nombre)
{
    for(int i=0; i<8; i++)
    {
        //printf("%d ", (nombre & 1 << (7-i)) >> (7-i) );
        printf("%d ", (nombre >> (7-i)) & 1 );
    }
}

int
binary_dump(const char *nom_fichier)
{
    octet_t tampon = 0;
    FILE* fh = fopen(nom_fichier, "rb");
    int code_retour = 0;

    errno = 0;

    if( fh == NULL)
    {
        printf("Impossible d'ouvrir le fichier\n"
               "ERRNO = %d = %s", errno, strerror(errno));
        code_retour = 1;
    }
    else
    {
         // Lecture en boucle
        while( fread(&tampon, sizeof(octet_t), 1, fh) == 1)
        {
            printf("%2X \t", tampon, tampon);
            print_octet_as_bin(tampon);
            printf("\n");
        }

        // Traitement de l'erreur de lecture
        if(feof(fh) != 0)
        {
            //printf("\nFin du fichier atteinte avec succes.\n");
            code_retour = 0;
        }

        if(ferror(fh) != 0)
        {
            printf("\nErreur lors de la lecture du fichier\n"
                   "ERRNO = %d = %s", errno, strerror(errno));
            code_retour = 2;
        }
    }
    return code_retour;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        puts("Ce programme prend en parametre un nom de fichier");
        return EXIT_FAILURE;
    }
    else
    {
        return binary_dump(argv[1]);
    }
}
