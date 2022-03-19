#include <stdio.h>
#include <stdbool.h>
#include "H_View.h"

int main()
{
    dPtr D;
    bool loginRequired = false, loginRet;

    /* Initialize Dictionary */
    initDictionary(&D);

    /* Pull Data from Files */
    if (pullDictionaries(D))
    {
        printf(" Dictionaries pulled successfully\n");
    }
    else
    {
        printf(" Dictionaries failed to pull\n");
    }

    /* Insert default schemas */
    // insertDefault(D);

    /* systemType 0 == Employer */
    /* systemType 1 == Employee */
    int systemType = 0;

    if (systemType == 0)
    {
        /* Log in */
        if (loginRequired)
        {
            header();
            do
            {
                system("cls");
                header();
                if (!(loginRet = login()))
                {
                    printf("\n ERROR: The username or password is incorrect\n");
                    printf(" _____________________________________________________\n\n");
                    printf(" *Press any key to continue...* ");
                    getch();
                }
            } while (!loginRet);
        }

        /* Show Employer UI */
        showEmployerMenu(D);
    }
    else
    {
        /* Show Employee UI */
        showEmployeeSalary(D);
    }

    return 0;
}