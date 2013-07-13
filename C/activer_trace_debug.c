#include <stdlib.h>
#include <stdio.h>

#define DEBUG_ENABLED

#ifdef DEBUG_ENABLED
    #define DEBUG(T) T
#else
    #define DEBUG(T)
    // ou
    //#define DEBUG(T) ;
    /* Note :
    Une macro telle que : #define DEBUG(T) //
    ne sert a rien. En effet, la macro ne produit pas un symbole valide
    et de plus les commentaires sont elimines avec l'expansion des macros
    par le pre-processeur.
    Voir : http://www.developpez.net/forums/d1238428/c-cpp/c/commentaire-conditionnel-c/
    */
#endif

int main(void)
{
    DEBUG( printf("Message 1\n") );

    #ifdef DEBUG_ENABLED
    printf("Message 2\n");
    #endif

    return 0;
}
