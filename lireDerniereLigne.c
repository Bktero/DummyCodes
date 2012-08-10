#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
Ce programme lit la derniere ligne d'un fichier texte.
Voici un exemple pour le fichier a lire, "fichier.txt":
----------------------------------
Ceci est un fichier d'essai.

Cette ligne suit une ligne vide.
Et pour finir,
je dis au revoir !
----------------------------------
*/

int main(void)
{
    FILE *fichier = NULL;
    int tailleLigne = 0;
    char *ligne = NULL;

    if( (fichier = fopen("fichier.txt", "r")) == NULL)
        return(EXIT_FAILURE);

    if( fseek(fichier, -1, SEEK_END) == -1)
        perror("Impossible de se positionner a la fin du fichier ");

    while( (fgetc(fichier)) != '\n' )
    {
        tailleLigne++;

        if( ferror(fichier)!=0 )
        {
            perror("Erreur lors de la lecture ");
            return(EXIT_FAILURE);
        }

        //if( fseek(fichier, ftell(fichier)-2, SEEK_SET) == -1)
        if( fseek(fichier, -2, SEEK_CUR) == -1)
        {
            perror("Erreur de fseek() ");
            return(EXIT_FAILURE);
        }
    }

    printf("Longueur de la derniere ligne : %d\n", tailleLigne);

    if( (ligne = malloc(sizeof(char)*tailleLigne+1)) == NULL)
    {
        perror("Erreur d'allocation memoire ");
        return(EXIT_FAILURE);
    }

    if( fgets(ligne, tailleLigne+1, fichier) == NULL)
    {
        puts("Impossible de recuperer la derniere ligne");
        return(EXIT_FAILURE);
    }

    printf("'%s'", ligne);
    free(ligne);

    return 0;
}
