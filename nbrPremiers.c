#include <stdio.h>
#include<math.h>
#include <stdlib.h>
#define NOMBRE_MAX 10000

int main(void)
{
    int nombre_choisi = 0;
    int liste_nombre_premier[NOMBRE_MAX]={0};
    int i = 0;
    int test = 2;

    // Initialisation
    for(i=0;i<NOMBRE_MAX; liste_nombre_premier[i]=i,i++)
        ;

    printf("Ce programme permet d\'afficher tous les nombres premier jusqu\'a un nombre que vous aurez choisi\n\n\n");
    printf("Choisissez un nombre ( < 10 000): ");
    scanf("%d",&nombre_choisi);

    if(nombre_choisi >= 10000)
    {
        puts("Le nombre choisi est trop grand et donc ramene a 9999");

        system("pause");
        nombre_choisi = 9999;
    }
    else
    puts("ok");


    // Elimination
    for(test=2 ; test*test <= nombre_choisi ; test++)
    {
        //printf("Elimination des multiples de %d\n", test );
        for(i=0;i<=nombre_choisi; i++)
        {
            //printf("%d mod %d = %d\n", liste_nombre_premier[i], test, liste_nombre_premier[i]%test);
            if(liste_nombre_premier[i]%test==0 && test!=liste_nombre_premier[i])
                liste_nombre_premier[i]=0; // elimination
        }
    }

    // Affichage
    for(i=0;i<=nombre_choisi; printf("%d\t",liste_nombre_premier[i++]))
        ;

    return 0;
}
