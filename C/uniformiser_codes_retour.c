#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


// Macros pour cacher le cast dans le main()
#define CODE(variable, type) ( * (type*)code_retour )
#define OBTENIR_CODE(fonction, type) ( * (type*)code_retour = fonction )
#define CODE_TYPE(type) ( * (type*)code_retour )


// Fausses fonctions drivers
char driver_char(void)
{
    return 111;
}

double driver_double(void)
{
    return 3.15;
}


// Gestion pour uniformiser les retours varies en TRUE / FALSE
bool gestion_erreur(void* code, char data_type)
{
    switch(data_type)
    {
    case 'c':
        if (* (char*)code == 110)
            return false;
        else
            return true;

    case 'd':
        if (* (double*)code == 3.14)
            return true;
        else
            return false;
    default:
        return false;
    }
}

// Main
int main(void)
{
    void * code_retour = malloc( 10 * sizeof(double) );

    //* (char*)code_retour = driver_char();
    CODE_TYPE(char) = driver_char();
    bool un = gestion_erreur(code_retour, 'c');

    //* (double*)code_retour = driver_double();
    OBTENIR_CODE(driver_double(), double);
    bool deux = gestion_erreur(code_retour, 'd');

    printf("Un = %s\n"
           "Deux = %s", un ? "True" : "False", deux ? "True" : "False");

    return 0;
}

