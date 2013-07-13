#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// LIRE UN FICHIER CONTENANT DES FLOTTANTS ET LE CHARGER DANS UNE MATRICE
// http://www.developpez.net/forums/d1251154/c-cpp/c/extraire-donnees-fichier-txt/#post6839003


int main(void)
{
    FILE * fic = fopen("numero.txt", "r");
    assert(fic != NULL);

    float tmp = 0;
    int ret = 0;
    int col = 0;
    int ligne = 0;

    // Determiner le nombre de lignes
    // Ici, je simplifie et sais que j'ai 5 lignes
    // Une ligne contient 5 elements, plus simple que si 241
    float mat[5][5]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};


    // Recuperation des donnees
    while( 1 )
    {
        if( (ret = fscanf(fic, "%f", &tmp)) != 1 )
        {
            puts("Que s'est il passe ?");

            if( feof(fic) )
                printf("Fin du fichier atteinte : erreur 'normale'");
            else if( ferror(fic) )
                printf("Erreur de lecture : probleme avec le fichier");
            else
                printf("Erreur de conversion : le fichier ne contient pas que des flottants");

            break; // Terminer la boucle while(1)
        }
        else
        {
            mat[ligne][col++] = tmp;
        }

        if( col == 5)
        {
            // on connait la taille d'une ligne donc pas la peine de detecter un '\n'
            col = 0;
            ligne++;
        }
    }

    // Affichage
    puts("\n\n");
    for(ligne=0; ligne<5; ligne++)
    {
        for(col=0; col<5; col++)
        {
            printf("| %3.3f |", mat[ligne][col]);
        }
        putchar('\n');
    }

    fclose(fic);

    return 0;
}
