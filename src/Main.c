#include <stdio.h>
#include <stdbool.h>
#include "H_Interface.h"

int main()
{
    Dictionary D;
    initDictionary(&D);
    
    if (pullDictionaries(&D))
    {
        printf("Dictionaries pulled successfully\n");
    }
    else
    {
        printf("Dictionaries failed to pull\n");
    }

    // Debug Insert Default
    // insertDefault(Dictionary *D);

    showMenu(&D);

    return 0;
}
