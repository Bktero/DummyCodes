#include <stdlib.h>
#include <stdio.h>

/*
Essais d'utilisation de qsort()
*/

int isGreater(const void *pa, const void *pb)
{
    if( *(int*)pa> *(int*)pb )
        return 1;
    else if( *(int*)pa < *(int*)pb )
        return -1;
    else
        return 0;
}

int isLower(const void *pa, const void *pb)
{
    if( *(int*)pa < *(int*)pb )
        return 1;
    else if( *(int*)pa > *(int*)pb )
        return -1;
    else
        return 0;
}

void print_array(int *array, int length)
{
    int i = 0;
    while(i<length)
    {
        printf("%5d ", array[i]);
        i++;
    }
    putchar('\n');
}

int main(void)
{
    int tab[] = {15, 1, 12, 8, 56};
    print_array( &tab[0], sizeof(tab) / sizeof(tab[0]) );

    qsort(&tab[0], 5, 4, isLower );
    print_array( &tab[0], sizeof(tab) / sizeof(tab[0]) );

    qsort(&tab[0], 5, 4, isGreater );
    print_array( &tab[0], sizeof(tab) / sizeof(tab[0]) );

    return 0;
}
