#ifndef SCHEMA_H
#define SCHEMA_H

// change to true to enable debug mode
#define debug false

#define MD_MAX 30       // medium MAX
#define SM_MAX 30       // small MAX 50
#define DATE 30         // mm/dd/yy 11
#define MONTH 20        // mm/yy 6
#define MOBILE_PHONE 20 // ## ### ### #### 21
#define HOME_PHONE 20   // ### #### 21
// #pragma pack(1)

// MALE, FEMALE
typedef enum
{
    MALE,
    FEMALE
} Gender;

// EMPLOYEE, EMPLOYER
typedef enum
{
    EMPLOYEE,
    EMPLOYER
} UserType;

// NO, YES
typedef enum
{
    NO,
    YES
} Response;

typedef struct bonus
{
    int bonusID;
    int employeeID;
    char bonusName[SM_MAX];
    double amount;
    char period[MONTH];
} Schema_Bonus;

typedef struct issueSalary
{
    int issueID;
    int employeeID;
    double balance;
    char period[MONTH];
} Schema_IssueSalary;

typedef struct jobInformation
{
    int employmentID;
    int employeeID;
    char jobPosition[SM_MAX];
    char jobLocation[MD_MAX];
    char jobPhone[MOBILE_PHONE];
    char startDate[DATE];
    char department[SM_MAX];
    char jobEmail[SM_MAX];
    double basicSalary;
    double pagibigDeposit;
} Schema_JobInformation;

typedef struct user
{
    int userID;
    char firstName[SM_MAX];
    char lastName[SM_MAX];
    Gender gender;
    char dateOfBirth[DATE];
    Response filipinoCitizen;
    char homePhone[HOME_PHONE];
    char mobilePhone[MOBILE_PHONE];
    char emailAddress[MD_MAX];
    char address[MD_MAX];
    UserType userType;
} Schema_User;

typedef struct attendance
{
    int attendanceID;
    int employeeID;
    int present;
    int absent;
    int leave;
    int overtime;
    char period[MONTH];
} Schema_Attendance;

#endif
