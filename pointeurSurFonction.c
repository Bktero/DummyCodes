#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bonjour(char **s)
{
    *s = malloc(1000 * sizeof(char));
    strcpy(*s, "bonjour");
    printf("\t%s : %s @ %p\n", __func__, *s, *s);
}

void aurevoir(char **s)
{
    *s = malloc(1000 * sizeof(char));
    strcpy(*s, "au revoir");
    printf("\t%s : %s @ %p\n", __func__, *s, *s);
}

void cestfini(char **s)
{
    *s = malloc(1000 * sizeof(char));
    strcpy(*s, "c'est fini");
    printf("\t%s : %s @ %p\n", __func__, *s, *s);
}

void modificateur(void (*f)(char **), char **chaine)
{
    f(chaine);
}


void action(void)
{
    puts("Debut.......\n\n");

    void (*f)(char **) = bonjour;
    char *chaine = NULL;

    // Utilisation du pointeur sur fonction
    printf("Avant %s @ %p \n", chaine, chaine);
    f(&chaine);
    printf("Apres 1er pointeur : %s @ %p \n\n", chaine, chaine);

    // Liberation pour eviter fuite memoire
    free(chaine);
    chaine = NULL;

    // Modification du pointeur sur fonction
    f = aurevoir;
    f(&chaine);
    printf("Apres 2e pointeur : %s @ %p \n", chaine, chaine);

    // Liberation pour eviter fuite memoire
    free(chaine);
    chaine = NULL;

    // Pointeur sur fonction pour definir le comportement d'une fonction
    printf("\n\n\nAvant 1er modificateur : %s @ %p \n", chaine, chaine);
    modificateur(bonjour, &chaine);
    printf("Apres 1er modificateur : %s @ %p \n\n", chaine, chaine);

    // Liberation pour eviter fuite memoire
    //free(chaine);
    //chaine = NULL;
    // Voir l'effet sur les adresses de ne pas liberer la memoire

    // Appel avec un pointeur et non une fonction en parametre
    modificateur(f, &chaine);
    printf("Apres 2e modificateur : %s @ %p \n", chaine, chaine);


    // Liberation pour eviter fuite memoire
    free(chaine);
    chaine = NULL;

    // Pointeur sur fonction qui prend en parametre un pointeur sur fonction
    void (*fm)(void (*)(char **), char **) = modificateur;

    printf("\n\n\nAvant la fin : %s @ %p \n", chaine, chaine);
    fm(cestfini, &chaine);
    printf("A la fin : %s @ %p \n", chaine, chaine);

    puts("\n\n.......Fin");
}




