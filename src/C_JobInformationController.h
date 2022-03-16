#ifndef JOBCONTROLLER_H
#define JOBCONTROLLER_H

#include "H_Libraries.h"
#include "H_Schema.h"
#include "H_Model.h"
#include "C_DictionaryController.h"

Schema_JobInformation createJobInformation(Dictionary D, ID employeeID)
{
    Schema_JobInformation jobInfo;

    printf("Create Employee Job Information");

    char dType[10] = "JobInformation";
    jobInfo.employmentID = getNewID(dType, D);
    jobInfo.employeeID = employeeID;

    printf("\n\tJob Position: ");
    scanf("%s", &jobInfo.jobPosition);
    fflush(stdin);

    printf("\n\tJob Location: ");
    scanf("%s", &jobInfo.jobLocation);
    fflush(stdin);

    printf("\n\tJob Phone: ");
    scanf("%s", &jobInfo.jobPhone);
    fflush(stdin);

    printf("\n\tStart Date: ");
    scanf("%s", &jobInfo.startDate);
    fflush(stdin);

    printf("\n\tDepartment: ");
    scanf("%s", &jobInfo.department);
    fflush(stdin);

    printf("\n\tJob Email: ");
    scanf("%s", &jobInfo.jobEmail);
    fflush(stdin);

    printf("\n\tBasic Salary: ");
    scanf("%lf", &jobInfo.basicSalary);
    fflush(stdin);

    printf("\n\tPagibig Deposit: ");
    scanf("%lf", &jobInfo.pagibigDeposit);
    fflush(stdin);

    return jobInfo;
}

bool insertJobInformation(Dictionary *D, Schema_JobInformation data)
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
        return true;
    }
    else
    {
        return false;
    }
}

bool updateJobInformation(Dictionary *D, Schema_JobInformation data, Schema_JobInformation *pointer)
{
    if (data.employmentID != pointer->employmentID)
    {
        return false;
    }
    else
    {
        *pointer = data;
        return true;
    }
}

bool deleteJobInformation(Dictionary *D, ID employmentID)
{
    PSJI *trav, temp;
    int hashVal = hash(employmentID);

    for (trav = &(D->JobInformationD[hashVal]); *trav != NULL && (*trav)->data.employmentID != employmentID; trav = &(*trav)->next)
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
        D->count[3]--;
        return true;
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
        return NULL;
    }
}

void displayEmployeeJobInfo(int employeeID, Dictionary *D)
{
    Schema_JobInformation *ji = searchJobInformation(*D, employeeID);

    printf("|  Employee ID:      \t%d   |", ji->employeeID);
    printf("|  Employment ID:    \t%d   |", ji->employmentID);
    printf("|  Job Position:     \t%s   |", ji->jobPosition);
    printf("|  Job Location:     \t%s   |", ji->jobLocation);
    printf("|  Job Phone:        \t%s   |", ji->jobPhone);
    printf("|  Job Email:        \t%s   |", ji->jobEmail);
    printf("|  Start Date:       \t%s   |", ji->startDate);
    printf("|  Department:       \t%s   |", ji->department);
    printf("|  Basic Salary:     \t%lf  |", ji->basicSalary);
    printf("|  Pag-ibig Deposit: \t%lf  |", ji->jobPosition);
}

#endif