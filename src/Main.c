#include <stdio.h>
#include <stdbool.h>
#include "H_Interface.h"

int main()
{
    Dictionary D;
    initDictionary(&D);
    bool b = pullDictionaries(&D);
    if (b)
    {
        printf("Dictionaries pulled successfully\n");
    }
    else
    {
        printf("Dictionaries failed to pull\n");
    }

    showMenu(&D);
    return 0;
}