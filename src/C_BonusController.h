#ifndef BONUSCONTROLLER_H
#define BONUSCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

void insertBonus(Dictionary *D, Schema_Bonus data)
{
    PSB *trav;
    int hashVal = hash(data.bonusID);

    for (trav = &(D->BonusD[hashVal]); strcmp(data.bonusName, (*trav)->data.bonusName)!=0 && *trav != NULL; trav = &(*trav)->next)
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
        printf("Bonus Inserted Successfully\n");
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

void deleteBonus(Dictionary *D, ID bonusID)
{
    PSB *trav, temp;
    int hashVal = hash(bonusID);

    for (trav = &(D->BonusD[hashVal]); *trav != NULL && (*trav)->data.bonusID != bonusID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("Bonus ID not found\n");
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]++;
        printf("Bonus Deleted Successfully\n");
    }
}

Schema_Bonus* searchBonus(Dictionary D, ID bonusID)
{
    PSB trav, temp;
    int hashVal = hash(bonusID);

    for (trav = D.BonusD[hashVal]; trav != NULL && trav->data.bonusID != bonusID; trav = trav->next)
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

#endif