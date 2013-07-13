/*#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <windows.h>
*/

/*
    int a;
    scanf("%d", &a);
    getchar();
    return a;
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
/*#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <windows.h>
*/

/*
    int a;
    scanf("%d", &a);
    getchar();
    return a;
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
Ce programme montre la conversion d'une chaine hexadecimale
representant un float sur 4 octets (= 8 lettres), dans la representation
IEEE 754-1985 : http://en.wikipedia.org/wiki/IEEE_754-1985
*/

/*
Prend un parametre un float et renvoie la chaine de caracteres hexadecimaux correspondante
*/
char* genererChaine(float nombre)
{
    void *pt = malloc(sizeof(float));
    assert(pt != NULL);

    char *chaine = malloc(100); // taille arbitraire mais en toute logique tres suffisante
    assert(chaine != NULL);

    *((float*)pt) = nombre;

    /*printf("genererChaine:\n"
           "En float : %f\n"
           "En hexa : %X\n\n", *((float*)pt), *((int*)pt));*/

    snprintf(chaine, 100, "%X", *((int*)pt));
    return chaine;
}


/*
Prend en parametre une chaine de caractere et renvoie le float correspondant.
La fonction se base sur le fait qu'un unsigned long et un float ont la meme occupation memoire
(4 octets avec Windows XP 32 bits).

A voir ce qu'il se passe en 64 bits et  comment l'adapter.
*/
float obtenirFloat(char* chaine)
{
    float nombre= 0;

    if(sizeof(float) != sizeof(unsigned long))
    {
        puts("Probleme !");
        puts("Les floats et les unsigned longs n'ont pas la meme occupation memoire");

        printf("sizeof(float) = %d\n"
                "sizeof(int) = %d\n"
                "sizeof(long) = %d\n", sizeof(float), sizeof(int), sizeof(long) );
    }
    else
    {
        unsigned long hexa = strtoul(chaine, 0, 16);
        float *pt = (float*)&hexa;
        nombre = *pt;

        /*printf("obtenirFloat :"
               "\nhexa = %X\n"
               "nombre = %f\n\n", hexa, nombre);*/

    }

    return nombre;
}


/*

int main(void)
{

    char* chaine = genererChaine(3.14);
    printf("'%s' = %f\n\n", chaine, obtenirFloat(chaine));
    free(chaine);

    chaine = genererChaine(59897.562);
    printf("'%s' = %f\n\n", chaine, obtenirFloat(chaine));
    free(chaine);

    chaine = genererChaine(666e-10);
    printf("'%s' = %.20f\n\n", chaine, obtenirFloat(chaine));
    free(chaine);





    union
    {
        unsigned char chaine[sizeof(float)];
        unsigned int hexa;
        float energie;
    } combine;

    combine.chaine[3] = 0x45;
    combine.chaine[2] = 0x2d;
    combine.chaine[1] = 0xb6;
    combine.chaine[0] = 0x32;

    printf("'%s' a l'adresse %p\n", combine.chaine, combine.chaine);
    printf("'%X' a l'adresse %p\n", combine.hexa, &combine.hexa);
    printf("'%f' a l'adresse %p\n", combine.energie, &combine.energie);




    return 0;
}
*/

/*
char *value = "\x45\x2d\xb6\x32";

typedef union ENERGY
{
    unsigned char bytes[4];
    float f32;
} ENERGY;

int main(void)
{
    ENERGY energie;
    energie.bytes[3] = *(value + 0);
    printf("%x\n", energie.bytes[0]);
    energie.bytes[2] = *(value + 1);
    printf("%x\n", energie.bytes[1]);
    energie.bytes[1] = *(value + 2);
    printf("%x\n", energie.bytes[2]);
    energie.bytes[0] = *(value + 3);
    printf("%x\n", energie.bytes[3]);

    printf("%f", energie.f32);

    return 0;
}
*/



