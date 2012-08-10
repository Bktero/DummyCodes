#include <stdlib.h>
#include <stdio.h>

/*
Il ne faut pas utiliser gets : la preuve.

Il suffit d'executer le programme, d'entrer "bonjour" et de voir le resultat.
'Entier' est place a la suite de 'chaine' en memoire (a quelques bits de padding pres)
et 'gets' ecrase ce qui est apres 'chaine', cad 'entier'.
*/

int main(void)
{
    struct
    {
        char chaine[4] ;
        int entier;
    } demo ;

    demo.chaine[0] = 'a';
    demo.chaine[1] = 'b';
    demo.chaine[2] = 'c';
    demo.chaine[3] = '\0';
    demo.entier = 42;

    printf("'%s' %d\n", demo.chaine, demo.entier);

    printf("Saisir une chaine : \n");
    gets(demo.chaine);

    printf("'%s' %d\n", demo.chaine, demo.entier);

    return demo.entier;
}