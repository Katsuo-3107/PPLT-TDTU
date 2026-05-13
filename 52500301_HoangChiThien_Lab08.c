#include <stdio.h>
#include <string.h>
#define SIZE 100

struct Employee
{
    char id[SIZE];
    char name[SIZE];
    char sex[SIZE];
    int birthYear;
    int phoneNumber;
    int salary;
};

struct Employee employees[10];

void printAllEmployees(struct Employee employees[], int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Employee %d:\n", i + 1);
        printf("  ID: %s\n", employees[i].id);
        printf("  Name: %s\n", employees[i].name);
        printf("  Sex: %s\n", employees[i].sex);
        printf("  Birth year: %d\n", employees[i].birthYear);
        printf("  Phone number: %d\n", employees[i].phoneNumber);
        printf("  Salary: %d\n", employees[i].salary);
        printf("\n");
    }
}

void readLine(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) != NULL)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        else
        {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }
    else
    {
        buffer[0] = '\0';
    }
}

int readInt(const char *prompt)
{
    char line[SIZE];
    int value;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            return 0;
        }
        if (sscanf(line, "%d", &value) == 1)
        {
            return value;
        }
        printf("Invalid number. Please try again.\n");
    }
}

int isValidSex(const char *sex)
{
    return strcmp(sex, "Male") == 0 || strcmp(sex, "Female") == 0;
}

void countEmployeesBySex(const struct Employee employees[], int count, int *maleCount, int *femaleCount)
{
    *maleCount = 0;
    *femaleCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(employees[i].sex, "Male") == 0)
        {
            (*maleCount)++;
        }
        else if (strcmp(employees[i].sex, "Female") == 0)
        {
            (*femaleCount)++;
        }
    }
}

void sortEmployeesByBirthYear(struct Employee employees[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (employees[i].birthYear > employees[j].birthYear ||
               (employees[i].birthYear == employees[j].birthYear && employees[i].salary > employees[j].salary))
            {
                struct Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
}

void sortEmployeesBySalary(struct Employee employees[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (employees[i].salary > employees[j].salary ||
               (employees[i].salary == employees[j].salary && employees[i].birthYear > employees[j].birthYear))
            {
                struct Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
}

int findYoungestEmployee(const struct Employee employees[], int count)
{
    if (count <= 0)
    {
        return -1;
    }

    int youngestIndex = 0;
    for (int i = 1; i < count; i++)
    {
        if (employees[i].birthYear > employees[youngestIndex].birthYear)
        {
            youngestIndex = i;
        }
    }
    return youngestIndex;
}

int findEmployeeById(struct Employee employees[], int count, const char *id)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(employees[i].id, id) == 0)
        {
            return i;
        }
    }
    return -1;
}

int deleteEmployeeById(struct Employee employees[], int *count, const char *id)
{
    int index = findEmployeeById(employees, *count, id);
    if (index < 0)
    {
        return 0;
    }

    for (int i = index; i < *count - 1; i++)
    {
        employees[i] = employees[i + 1];
    }
    (*count)--;
    return 1;
}

int findMaxSalary(const struct Employee employees[], int count)
{
    if (count <= 0)
    {
        return 0;
    }

    int maxSalary = employees[0].salary;
    for (int i = 1; i < count; i++)
    {
        if (employees[i].salary > maxSalary)
        {
            maxSalary = employees[i].salary;
        }
    }
    return maxSalary;
}

void printEmployeesWithMaxSalary(const struct Employee employees[], int count)
{
    int maxSalary = findMaxSalary(employees, count);
    printf("Maximum salary: %d\n", maxSalary);
    printf("Employees with maximum salary:\n");
    for (int i = 0; i < count; i++)
    {
        if (employees[i].salary == maxSalary)
        {
            printf("Employee %d: ID=%s, Name=%s\n", i + 1, employees[i].id, employees[i].name);
        }
    }
}

int main()
{
    int count = 0;
    while (count < 10)
    {
        printf("Enter details for employee %d:\n", count + 1);
        printf("ID: ");
        readLine(employees[count].id, SIZE);
        printf("Name: ");
        readLine(employees[count].name, SIZE);
        do
        {
            printf("Sex (Male/Female): ");
            readLine(employees[count].sex, SIZE);
            if (!isValidSex(employees[count].sex))
            {
                printf("Invalid sex. Please enter Male or Female.\n");
            }
        } while (!isValidSex(employees[count].sex));
        employees[count].birthYear = readInt("Birth year: ");
        employees[count].phoneNumber = readInt("Phone number: ");
        employees[count].salary = readInt("Salary: ");
        count++;
    }

    struct Employee birthSorted[10];
    struct Employee salarySorted[10];
    memcpy(birthSorted, employees, count * sizeof(struct Employee));
    memcpy(salarySorted, employees, count * sizeof(struct Employee));

    sortEmployeesByBirthYear(birthSorted, count);
    printf("Employees sorted by birth year:\n");
    printAllEmployees(birthSorted, count);

    sortEmployeesBySalary(salarySorted, count);
    printf("Employees sorted by salary:\n");
    printAllEmployees(salarySorted, count);

    printEmployeesWithMaxSalary(employees, count);

    int youngestIndex = findYoungestEmployee(employees, count);
    if (youngestIndex != -1)
    {
        printf("Youngest employee: ID=%s, Name=%s\n", employees[youngestIndex].id, employees[youngestIndex].name);
    }

    char deleteId[SIZE];
    printf("Enter employee ID to delete: ");
    readLine(deleteId, SIZE);
    if (deleteEmployeeById(employees, &count, deleteId))
    {
        printf("Deleted employee with ID %s.\n", deleteId);
    }
    else
    {
        printf("Employee with ID %s not found.\n", deleteId);
    }

    int maleCount, femaleCount;
    countEmployeesBySex(employees, count, &maleCount, &femaleCount);
    printf("Male employees: %d\n", maleCount);
    printf("Female employees: %d\n", femaleCount);

    char searchId[SIZE];

    printf("Enter employee ID to search: ");
    readLine(searchId, SIZE);

    int index = findEmployeeById(employees, count, searchId);
    if (index != -1)
    {
        printf("Employee found:\n");
        printf("  ID: %s\n", employees[index].id);
        printf("  Name: %s\n", employees[index].name);
        printf("  Sex: %s\n", employees[index].sex);
        printf("  Birth year: %d\n", employees[index].birthYear);
        printf("  Phone number: %d\n", employees[index].phoneNumber);
        printf("  Salary: %d\n", employees[index].salary);
    }

    else
    {
        printf("Employee with ID %s not found.\n", searchId);
    }

    return 0;
}