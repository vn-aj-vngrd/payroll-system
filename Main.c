#include <stdio.h>
#include <stdbool.h>
#include "H_View.h"

int main()
{
    dPtr D;
    bool loginRequired = false;

    /* Initialize Dictionary  */
    initDictionary(&D);

    /* Log in  */
    if (loginRequired)
    {
        header();
        if (!login())
        {
            printf(" ERROR: The username or password is incorrect*\n");
            printf(" \n*Press any key to continue...* ");
            getch();
            return 0;
        }
    }

    /* Pull Data from Files */
    // if (pullDictionaries(D))
    // {
    //     printf(" Dictionaries pulled successfully\n");
    // }
    // else
    // {
    //     printf(" Dictionaries failed to pull\n");
    // }

    /* Insert default schemas */
    insertDefault(D);

    /* Show User Interface */
    showMenu(D);

    return 0;
}