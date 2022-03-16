#ifndef BONUSCONTROLLER_H
#define BONUSCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

bool insertBonus(Dictionary *D, Schema_Bonus data)
{
    PSB *trav;
    int hashVal = hash(data.bonusID);

    for (trav = &(D->BonusD[hashVal]); strcmp(data.bonusName, (*trav)->data.bonusName) != 0 && *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSB *)malloc(sizeof(Schema_Bonus));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;
        }
        D->count[3]++;
        return true;
    }
    else
    {
        return false;
    }
}

bool updateBonus(Dictionary *D, Schema_Bonus data, Schema_Bonus *pointer)
{
    if (data.bonusID != pointer->bonusID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteBonus(Dictionary *D, ID bonusID)
{
    PSB *trav, temp;
    int hashVal = hash(bonusID);

    for (trav = &(D->BonusD[hashVal]); *trav != NULL && (*trav)->data.bonusID != bonusID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        return false;
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]++;
        return true;
    }
}

Schema_Bonus *searchBonus(Dictionary D, ID bonusID, char period[])
{
    PSB trav, temp;
    int hashVal = hash(bonusID);

    for (trav = D.BonusD[hashVal]; trav != NULL && trav->data.bonusID != bonusID && strcmp(trav->data.period, period) != 0; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // Schema_Bonus *data = (Schema_Bonus *)malloc(sizeof(Schema_Bonus));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        printf("Bonus ID not found\n");
        return NULL;
    }
}

void debugBonus(Dictionary D)
{
    PSB trav;
    int i;

    printf("DICTIONARY BONUS\n");
    printf("%4s | %4s\n", "row", "ID");
    for (i = 0; i < DICT_SIZE; i++)
    {
        printf("%4d | ", i);
        for (trav = D.BonusD[i]; trav != NULL; trav = trav->next)
        {
            printf("%d -> ", trav->data.bonusID);
        }
        printf("\n", i);
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("End of Dictionary\n");
    }
}

void displayAllBonus(Dictionary D)
{
    PSB trav;
    int i;

    printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "____",
           "_________",
           "____________",
           "___________",
           "_______",
           "_______");
    printf("BONUS\n");
    printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "____",
           "_________",
           "____________",
           "___________",
           "_______",
           "_______");
    printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
           "#",
           "BONUS ID",
           "EMPLOYEE ID",
           "BONUS NAME",
           "AMOUNT",
           "PERIOD");

    for (i = 0; i < DICT_SIZE; i++)
    {
        for (trav = D.BonusD[i]; trav != NULL; trav = trav->next)
        {
            printf("%4d | %14d | %12d | %8d | %7d | %8d | %9d | %-7s\n",
                   i,
                   trav->data.bonusID,
                   trav->data.employeeID,
                   trav->data.bonusName,
                   trav->data.amount,
                   trav->data.period);
        }
    }

    if (trav == NULL && i == DICT_SIZE - 1)
    {
        printf("%-4s | %-9s | %-12s | %-11s | %-7s | %-7s\n",
               "____",
               "_________",
               "____________",
               "___________",
               "_______",
               "_______");
        printf("End of Dictionary\n");
    }
}

#endif