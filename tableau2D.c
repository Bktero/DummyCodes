#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
Ce fichier contient des fonctions pour gérer un tableau à 2 dimensions
et joue avec les const à différents niveaux des étoiles.
*/


void test(const char * const *const *pt_tableau, int lignes, int colonnes)
{
    int s;
    char const  *const *const  tableau =  *pt_tableau;

    // Niveau 0
    // --> autorisé car aucun const ne s'applique a pt_tableau et n'a pas d'effet une fois sortie de f()
    pt_tableau = NULL;

    // Niveau 1 d'indirection
    tableau = NULL;
    *pt_tableau = NULL;

    // Niveau 2 d'indirection
    for(s=0;s<lignes;s++)
    {
        *(tableau+s) = malloc( sizeof(char[colonnes]) );
        strcpy( *(tableau+s), "BOUM !"); // ne devrait pas provoquer une erreur de compilation ?
    }

    // Niveau 3 d'indirection
    for(s=0;s<5;s++)
        *( *(tableau) + 0 ) = 'C';
}


typedef char** TABLEAU;

TABLEAU creer(int taille)
{
    return malloc( sizeof(char*) * taille );
}

void allouer(TABLEAU *pt_tab, int lignes, int colonnes)
{
    TABLEAU tab = *pt_tab;
    int s;

    for(s=0; s<lignes; s++)
        *(tab+s) = malloc( sizeof(char) * colonnes );
}

void remplir(TABLEAU *pt_tab, int lignes, int colonnes)
{
    int s;
    TABLEAU tab = *pt_tab;
    for(s=0; s<lignes; s++)
        snprintf( *(tab+s), colonnes, "chaine %d", s);
}

#include <assert.h>
void afficher(TABLEAU tab, int lignes)
{
    int s;
    assert(tab != NULL);
    for(s=0; s<lignes; s++)
        printf("Ligne %d = '%s'\n", s, *(tab+s) );
    printf("\n\n");
}

void liberer(TABLEAU *pt_tab, int lignes)
{
    TABLEAU tab = *pt_tab;
    int s;

    for(s=0; s<lignes; s++)
        free( *(tab+s) );

    free(tab);
    *pt_tab  = NULL; // pas possible de le faire sur la copie locale evidemment
}

int main(void)
{
    int lig = 5, col = 10;
    TABLEAU tableau = creer(lig);
    allouer(&tableau, lig, col);
    remplir(&tableau, lig, col);

    afficher(tableau, lig);

    test(  (const char *const *const *)&tableau, lig, col);

    liberer( &tableau, lig);
    printf("%p\n\n", tableau);
    afficher(tableau, lig);

    return 0;
}