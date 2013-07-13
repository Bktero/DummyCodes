/*
stail

stail is a simplified version of the well-knowed 'tail' command.


//----------------------------------------------------------------------------------
Simplified BSD License

Copyright (c) 2012-2013, Pierre GRADOT
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies, 
either expressed or implied, of the FreeBSD Project.
//----------------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Taille du buffer lors du parcours du fichier
#define TAILLE_LIGNE 200

// Prototypes des fonctions
void usage(void);
int stail(const char* nomFichier, const unsigned int nbr);

// Programme
int main (int argc, const char * argv[])
{ 
    // Declarations des variables
    int codeRetour=1;
    unsigned int nbr = 0;
    
    // Recuperation des arguments et affichage avec stail() si OK
    if(3!=argc)
    {
        puts("Nombre d'arguments invalides");
        usage();
        codeRetour = EXIT_FAILURE;
    }
    else
    {
        //nbr = atoi(argv[2]);
        // Verification que le dernier argument est un nombre
         char *erreurConv;
        nbr = (unsigned int) strtoul(argv[2], &erreurConv, 10);
        if (*erreurConv != '\0')
        {
            puts("Le dernier argument doit etre un nombre entier");
            usage();
            codeRetour = EXIT_FAILURE;
        }
        else
        {
           codeRetour = stail(argv[1], nbr);
        }
    }
    
    //Fin du programme
    return codeRetour;
    
}//main



void usage(void)
{
    puts("--------------------------------------------------------");
    puts("La commande stail affiche la fin d'un fichier");
    puts("stail prend deux arguments en parametres");
    puts("\t- Le premier est le nom du fichier a afficher");
    puts("\t- Le second est le nombre de lignes a afficher");
    puts("--------------------------------------------------------");
}//usage 


int stail(const char* nomFichier, const unsigned int nbr)
{
    int nbAffichees = nbr;
    
    // Indice de parcours
    int i=0;
    
    // Indicateur d'erreur lors du parcours du fichier / sert aussi de code retour
    int doNotDisplay=0;
    
    // Tampon des positions de debut de lignes
    int *t_positions = malloc(sizeof(int)*100);
    
    // Nombre de lignes dans le fichier
    int nbLignes = 0;
    
    // Tampon de la ligne courante
    char *t_ligne = malloc(sizeof(char)*TAILLE_LIGNE);
    
    FILE *pt_fic = fopen(nomFichier, "r");
    if(NULL==pt_fic)
    {
        printf("Impossible d'ouvrir le fichier %s : (%d) %s\n", nomFichier, errno, strerror(errno));

        // On positionne le code retour
        doNotDisplay=1;
    }
    else
    {        
        // La premiere ligne commence maintenant
        *(t_positions+i)=ftell(pt_fic);        
        if(1L==*(t_positions+i))
        {
            perror("Erreur lors de la lecture");
            doNotDisplay=1;
        }
        i+=1;
        
        // Flag de lecture
        int keepReading=1;
        
        // Boucler sur le fichier pour determiner les positions des debuts de lignes
        while( 1 == keepReading )
        {
            // Lecture d'une nouvelle ligne
            t_ligne = fgets(t_ligne, TAILLE_LIGNE, pt_fic);
            
            // On continue a lire ?
            if(t_ligne==NULL)
            {
                // Stopper la lecture
                keepReading=0;
                
                // On determine la cause de l'erreur
                if(0 != feof(pt_fic))
                {
                    // Fin du fichier atteinte
                    //puts("Fichier parcouru avec succes");
                }
                else
                {
                    // Autre erreur
                    perror("Erreur lors de la lecture");
                    
                    // On n'affichera pas le fichier
                    doNotDisplay=1;
                }
            }
            else
            {
                // Ligne lu en entier ou buffer trop petit ?
                if(NULL==strrchr(t_ligne, '\n'))
                {
                    //DEBUG
                    //printf("(%dd)%s", i, t_ligne);
                    
                    // Buffer trop petit pour contenir la ligne entiere : on continue a lire sans memoriser la position
                }
                else
                {                    
                    //DEBUG
                    //printf("(%d) %s", i, t_ligne);
                    
                    // Memorisation de la position
                    *(t_positions+i)=ftell(pt_fic);
                    if(1L==*(t_positions+i))
                    {
                        perror("Erreur lors de la lecture");
                        doNotDisplay=1;
                    }
                    i+=1;
                }                          
            }
        }//while
        
        
        // --------------------------------------------------------------------------------------------
        // Affichage a la facon de tail si pas d'erreur lors du parcours
        if (1!=doNotDisplay)
        {
            // Tampon de lecture
            char carac=0;
            
            // Nombre de lignes
            nbLignes = i-1;
            
            //printf("\n\nOn finit de lire le fichier. Il y a %d lignes.\nOn va maintenant afficher la fin du fichier, soit les %d dernieres lignes.\n\n", nbLignes, nbAffichees);
            
            // Enlever le flag de fin de fichier
            clearerr(pt_fic);
            
            // Se positionner au bon endroit
            if(nbLignes>nbAffichees)
            {
                fseek(pt_fic, *(t_positions+nbLignes-nbAffichees), SEEK_SET);                
            }
            else
            {
                fseek(pt_fic, *(t_positions), SEEK_SET);
            }
            
            // Affichage 
            while ( EOF!=(carac=fgetc(pt_fic)) )
            {
                putchar(carac);
            }
        }
        
        // Fermeture du fichier
        fclose(pt_fic);
        
    }//Ouverture du fichier
    
    return doNotDisplay;

}//stail   
