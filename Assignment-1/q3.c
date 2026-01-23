/*
Write a program to create a structure to store the information of n number of Employees.
Employee’s information includes data members: Emp-id, Name, Designation, basic_salary, hra%, da%.
Display the information of employees with gross salary. Use array of structure.
*/

#include <stdio.h>

struct employee
{
    int emp_id;
    char name[50];
    char designation[50];
    float basic_salary;
    float hra;
};

int main()
{
    int n;
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    struct employee emp[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter employee %d information:\n", i + 1);
        scanf("%d %s %s %f %f", &emp[i].emp_id, emp[i].name, emp[i].designation, &emp[i].basic_salary, &emp[i].hra);
    }

    printf("\nEmployee Information:\n");
    for (int i = 0; i < n; i++)
    {
        float hra_amount = (emp[i].basic_salary * emp[i].hra) / 100;
        float gross_salary = emp[i].basic_salary + hra_amount;
        printf("\nName: %s\n", emp[i].name);
        printf("Designation: %s\n", emp[i].designation);
        printf("Basic Salary: %.2f\n", emp[i].basic_salary);
        printf("HRA %%: %.2f\n", emp[i].hra);
        printf("Gross Salary: %.2f\n", gross_salary);
        printf("\n");

        return 0;
    }
}
