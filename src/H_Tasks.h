#ifndef TASKS_H
#define TASKS_H

#include "H_Schema.h"
#include "H_Model.h"
#include "C_AttendanceController.h"
#include "C_BonusController.h"
#include "C_DictionaryController.h"
#include "C_JobInformationController.h"
#include "C_SalaryController.h"
#include "C_UserController.h"

void getEmployee()
{
    Schema_User emp;
    Schema_JobInformation jobInfo;

    // Create employee basic information
    printf("Create Employee");
    printf("\nCreate Employee Information");

    char file1[50] = "EmployeeInformation.bin";
    // emp.userID = getNewID(file1, 'U');
    emp.userType = EMPLOYER;

    printf("\n\tFirst Name: ");
    scanf("%s", &emp.firstName);
    fflush(stdin);

    printf("\n\tLast Name: ");
    scanf("%s", &emp.lastName);
    fflush(stdin);

    printf("\n\tGender (MALE/FEMALE): ");
    scanf("%d", &emp.gender);
    fflush(stdin);

    printf("\n\tDate of Birth (mm/dd/yy): ");
    scanf("%s", &emp.dateOfBirth);
    fflush(stdin);

    printf("\n\tFilipino Citizen: ");
    scanf("%s", &emp.filipinoCitizen);
    fflush(stdin);

    printf("\n\tHome Phone: ");
    scanf("%s", &emp.homePhone);
    fflush(stdin);

    printf("\n\tMobile Phone: ");
    scanf("%s", &emp.mobilePhone);
    fflush(stdin);

    printf("\nEmail Address: ");
    scanf("%s", &emp.emailAddress);
    fflush(stdin);

    printf("\n\tAddress: ");
    scanf("%s", &emp.address);
    fflush(stdin);

    char file2[50] = "JobInformation.bin";
    // jobInfo.employmentID = getNewID(file2, D);

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

    // bool isSuccess = insertToDictionary(emp, jobInfo);
}

void displayEmployeeInformation(int employeeID, Dictionary *D)
{
    Schema_User *emp = searchUser(*D, employeeID);

    printf("|  Employee ID:      \t%d  |", emp->userID);
    printf("|  First Name:       \t%d  |", emp->firstName);
    printf("|  Last Name:        \t%s  |", emp->lastName);
    printf("|  Gender:           \t%s  |", emp->gender);
    printf("|  Date of Birth     \t%s  |", emp->dateOfBirth);
    printf("|  Filipino:         \t%s  |", emp->filipinoCitizen);
    printf("|  Home Phone:       \t%s  |", emp->homePhone);
    printf("|  Mobile Phone:     \t%d  |", emp->mobilePhone);
    printf("|  Email:            \t%d  |", emp->emailAddress);
    printf("|  Address           \t%s  |", emp->address);
}

void updateEmployeeInformation(int employeeID, Dictionary *D)
{
    Schema_User *emp = searchUser(*D, employeeID);
}

void deleteEmployeeInformation(int employeeID, Dictionary *D)
{
    deleteUser(D, employeeID);
    printf("Employee information successfully deleted!");
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

void displayAllEmployeeAttendence()
{
}

#endif
