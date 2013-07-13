#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>


int repLister(const char *nomRepertoire, char ***listeFichiers)
{
    DIR *repertoire = NULL;
	struct dirent *entite = NULL;
	int indice=0; // ne s'incremente que pour les fichiers affiches
	int taille=2;
 
	// Ouverture du dossier
	if(NULL== (repertoire=opendir(nomRepertoire)) )
	{
	    perror("Impossible d'ouvrir le dossier");
	    return -1;
	}
 
	// Allocation dynamique de la liste ; elle sera agrandie si besoin
    if(NULL == (*listeFichiers=malloc(taille*sizeof(char*))))
    {
        perror("Impossible d'allouer la memoire pour la liste");
	    return -2;
    }
 
    // Lister les elements + affichage
	while( (entite=readdir(repertoire)) )
	{
        if( ((entite->d_type==DT_REG) || (entite->d_type==DT_DIR))
                && strcmp(entite->d_name, ".")!=0
                && strcmp(entite->d_name, "..")!=0 )
        {
 
            if(NULL == (*((*listeFichiers)+indice) = malloc(strlen(entite->d_name)+1) ) )
            {
                perror("Impossible d'allouer la memoire un element de liste");
                return -2;
            }
 
            strcpy( *((*listeFichiers)+indice), entite->d_name);
 
            printf("%d : %s%s\n", indice, (entite->d_type==DT_DIR) ? "(dir) " : "", entite->d_name);
            indice=indice+1;
        }
        else
        {
            // Ne rien faire pour les fichiers speciaux
            // ainsi que pour les dossiers . et ..
        }
 
        // Liste pleine ?
        if(indice==taille)
        {
            taille=taille+2;
            printf("\tReallocation dans repLister avec taille = %d\n",taille);
		char **temp=NULL;
            if(NULL == (temp=realloc(*listeFichiers, taille*sizeof(char*))))
            {
		free(*listeFichiers);
                perror("Impossible de reallouer la memoire pour la liste");
                return -2;
            }
		else
		{
			*listeFichiers=temp;
		}
        }
	}
	return indice;
}



int main(void)
{
	char **liste;
	repLister("/Users/pierregradot/", &liste);
	return 0;
}
