#include <stdio.h>
#include <string.h>
#include <stddef.h>     // for size_t
#include <sys/types.h>
#include <errno.h>
#include <assert.h>
#include <winsock2.h>


/**
* Mise en evidence qu'un pointeur et un tableau sont differents
*/
void exemple_1(void)
{
    int tableau[] = {0,1,2,3,4,5};

    printf("tableau       = %x\n", tableau);
    printf("&tableau      = %x\n\n", &tableau);
}

void exemple_1bis(void)
{
    int tableau[] = {0,1,2,3,4,5};

    printf("&tableau[0]   = %x\n", &tableau[0]);
    printf("&tableau      = %x\n\n", &tableau);
}

void exemple_2(void)
{
    int *pointeur = calloc(6 , sizeof(int));

    printf("pointeur      = %x\n", pointeur);
    printf("&pointeur     = %x\n\n", &pointeur);
}


/**
* Test des conflits de types
*/
void equi_1(int tab[]);

void equi_1(int * pt)
{
    printf("%d\n", *pt);
    return;
}

void equi_2(int* tab[]);    // au lieu de faire un tableau de int,
                            // on fait un tableau de int*

void equi_2(int* *pt)      // par analogie, on fait un pointeur sur un int*
{
    printf("%d\n", **pt);
    return;
}

void equi_3(int (*ptab)[]);  // pointeur sur tableau de type incomplet, qui peut etre complete
void equi_3(int (*ptab)[4]); // si on specifie la taille, elle doit etre la meme partout
//void equi_3(int (*ptab)[5]); // ainsi, cette ligne genere une erreur

void equi_3(int tab[][4])
{
    printf("%d\n", tab[0][0]);
    return;
}

//void equi_4(int (*ptab)[]); // erreur car ici, il y a un conflit des types

void equi_4(int ** ppt)
{
    printf("%d\n", **ppt);
    return;
}


/**
* Pointeur sur type incomplet
*/
void avec_taille(int (*ptab)[3])
{
    printf("Avec %d\n", ptab[0][0]);
}

void sans_taille(int (*ptab)[])
{
    printf("Sans %d\n", (*ptab)[0]);
//    printf("Sans %d\n", ptab[0][0]); // erreur car taille inconnue implique pas d'arithmetique de pointeur
}

/**
* Main
*/
int main2(void)
{
    puts("Mise en evidence");
    exemple_1();
    exemple_1bis();
    exemple_2();

    puts("Equivalences");
    int tab[] = {42, 43, 44};
    equi_1(tab);

    int* tab_de_ptr[] = {&tab[0], &tab[1], &tab[2]};
    equi_2(tab_de_ptr);

    puts("Type incomplet");
    int (*p_sur_tab)[] = &tab;      // pointeur incomplet sur  "tableau de int"
    int (*p_sur_tab3)[3] = &tab;    // ok car tab est bien de longueur 3 (type int[3])
    int (*p_sur_tab5)[5] = &tab;    // warning car l'objet pointe n'est pas de type int[5]

    avec_taille(p_sur_tab);
    avec_taille(p_sur_tab3);
    avec_taille(p_sur_tab5);    // warning car le parametre n'est pas du type attendu

    sans_taille(p_sur_tab);
    sans_taille(p_sur_tab3);
    sans_taille(p_sur_tab5);

    return 0;
}


/* 
// Autre exemple avec une fonction, issu de la converstion
// http://www.developpez.net/forums/d1254135/c-cpp/c/debuter/copie-tableau-fichier/


#include <stdlib.h>
#include <stdio.h>

int copie_originale(int **tab , size_t col, size_t row)
{
    size_t i, j;

    for(i=0 ; i<row ; i++)
    {
        for (j=0 ; j<col ; j++)
        {
            printf("%d\t", tab[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int copie_alternative(int (*tab)[] , size_t col, size_t row)
{
    size_t i, j;
    for(i=0 ; i<row ; i++)
    {
        for (j=0 ; j<col ; j++)
        {
            printf("%d\t", (*tab+i*col)[j]);
        }
        printf("\n");
    }
    return 0;
}

int main(void)
{
    int tabtab[4][5] = { {15, 1, 12, 8, 56}, {1, 1, 2, 8, 6}, {515, 31, 142, 28, 526}, {135, 21, 132, 833, 563} };

    int * tabpt[5];
    tabpt[0] = (int*) tabtab[0]; // j'explicite le cast implicite
    tabpt[1] = tabtab[1];
    tabpt[2] = tabtab[2];
    tabpt[3] = tabtab[3];
    tabpt[4] = tabtab[4];

    puts("copie_originale OK : ");
    copie_originale(tabpt, 5, 4);

    puts("\ncopie_alternative OK : ");
    copie_alternative(tabtab, 5, 4);

    puts("copie_originale KO ! : ");
    //copie_originale(tabtab, 5, 4); // warning pour des types incompatibles
                                    // plante le programme

    puts("\ncopie_alternative KO ! : ");
    copie_alternative(tabpt, 5, 4); // warning idem , affiche n'importe quoi

    char monChar = '0';
    printf("%d", monChar - '0');
    monChar = '1';
    printf("%d", monChar - '0');

    return 0;
}

*/