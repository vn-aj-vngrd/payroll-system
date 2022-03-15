#ifndef JOBCONTROLLER_H
#define JOBCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

void insertJobInformation(Dictionary *D, Schema_JobInformation data)
{
    PSJI *trav;
    int hashVal = hash(data.employmentID);

    for (trav = &(D->JobInformationD[hashVal]); *trav != NULL; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        trav = (PSJI *)malloc(sizeof(Schema_JobInformation));
        if (*trav != NULL)
        {
            (*trav)->data = data;
            (*trav)->next = NULL;
        }
        D->count[3]++;
        printf("User Inserted Successfully\n");
    }
}

void updateJobInformation(Dictionary *D, Schema_JobInformation data)
{
    PSJI *trav;
    int hashVal = hash(data.employmentID);

    for (trav = &(D->JobInformationD[hashVal]); *trav != NULL && (*trav)->data.employmentID != data.employmentID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("User ID not found\n");
    }
    else
    {
        (*trav)->data = data;
        printf("User Updated Successfully\n");
    }
}

void deleteJobInformation(Dictionary *D, ID employmentID)
{
    PSJI *trav, temp;
    int hashVal = hash(employmentID);

    for (trav = &(D->JobInformationD[hashVal]); *trav != NULL && (*trav)->data.employmentID != employmentID; trav = &(*trav)->next)
    {
    }

    if (trav == NULL)
    {
        printf("User ID not found\n");
    }
    else
    {
        temp = *trav;
        *trav = (*trav)->next;
        free(temp);
        D->count[3]--;
        printf("User Deleted Successfully\n");
    }
}

Schema_JobInformation *searchJobInformation(Dictionary D, ID employmentID)
{
    PSJI trav, temp;
    int hashVal = hash(employmentID);

    for (trav = D.JobInformationD[hashVal]; trav != NULL && trav->data.employmentID != employmentID; trav = trav->next)
    {
    }

    if (trav != NULL)
    {
        // UserSchema_JobInformation *data = (UserSchema_JobInformation *)malloc(sizeof(UserSchema_JobInformation));
        // *data = trav->data;
        return &trav->data;
    }
    else
    {
        printf("User ID not found\n");
        return NULL;
    }
}

#endif