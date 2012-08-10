#include <stdio.h>

// Prototypes
unsigned position_of_min(int[], unsigned int, unsigned int);
void recursive_sort(int tableau[], unsigned int length);
void display_tableau(int tableau[], unsigned int length);

// Fonctions
unsigned int position_of_min(int tableau[], unsigned int length, unsigned int position)
{
    unsigned int tpos=position;
    unsigned int i=position;

    for(i=position;i<length;i++)
    {
        if(tableau[i] < tableau[tpos])
        {
            tpos=i;
        }
    }
    return tpos;
}

void recursive_sort(int tableau[], unsigned int length)
{
    // Au moins 2 elements
    if(length<2)
    {
        printf("Tableau trop petit pour etre trier\n");
        return;
    }

    // Recuperation du min
    unsigned int mpos = position_of_min( tableau, length, 0 );
    int min = tableau[mpos];

    // Echange
    tableau[mpos] = tableau[0];
    tableau[0] = min;

    // Trier le reste du tableau
    if(length>=3)
        recursive_sort( tableau+1, length-1 );
}

void display_tableau(int tableau[], unsigned int length)
{
    unsigned int i=0;
    printf("|");
    for(i=0;i<length;i++)
    {
        printf(" %4d |", tableau[i]);
    }
    printf("\n\n");
}

// Main
int main(void)
{

    int tab[]={1000,900,15,78,9,-666,5,10,9874};
    unsigned int len = sizeof(tab)/sizeof(tab[0]);

    printf("Taille de tableau : %d\n\nAvant\n", len);
    display_tableau(tab, len);

    puts("\n\nApres :");

    recursive_sort(tab, len);
    display_tableau(tab, len);

    return 0;
}
