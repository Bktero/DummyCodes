#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
 
int main(void)
{
    const char *tout = "Du texte au debut puis un nomber a lire :42";
 
    char texte[1024] = {0};
    int nombre = 0;
    int nbConv = 0;
    int nbLus = 0;
 
    // Premiere technique --> ne marche pas super bie, on est obliges de faire 2 sscanf()
    nbConv = sscanf(tout, "%[^[0-9]]%n%d", &texte[0], &nbLus, &nombre);
    printf("Conv = %d\n", nbConv);
    printf("Texte : [%s]\n", texte);
    printf("Nombre : [%d]\n", nombre);
    nbConv = sscanf(tout + strlen(texte), "%d", &nombre);
    printf("Nombre relu : [%d]\n", nombre);
    printf("%zu %d\n\n", strlen((texte)), nbLus);


    // Premiere technique corrigee
    // Voir les explications ici :
    puts(""); 
    nbConv = sscanf(tout, "%[^0-9]%n%d", &texte[0], &nbLus, &nombre);
    printf("Conv = %d\n", nbConv);
    printf("Texte : [%s]\n", texte);
    printf("Nombre : [%d]\n", nombre);
    printf("%zu %d\n\n", strlen((texte)), nbLus);
 

    // Seconde technique
    puts("");
    nbLus = 0;
    nbConv = sscanf(tout, "%[^:] %*c %n %d", &texte[0],&nbLus,  &nombre); // %*c pour passer le double point
    printf("Conv = %d\n", nbConv);
    printf("Texte : [%s]\n", texte);
    printf("Nombre : [%d]\n", nombre);
    printf("%zu %d\n\n", strlen((texte)), nbLus);
 

    // Troisieme technique
    puts("");
    nbLus = 0;
    nbConv = sscanf(tout, "%[a-zA-Z :]%n%d", &texte[0],&nbLus,  &nombre);
    printf("Conv = %d\n", nbConv);
    printf("Texte : [%s]\n", texte);
    printf("Nombre : [%d]\n", nombre);
    printf("%zu %d\n\n", strlen((texte)), nbLus);

    //return 0;
}