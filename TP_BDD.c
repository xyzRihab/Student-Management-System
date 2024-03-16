#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student
{
    char last_name[50];
    char first_name[50];
    int group;
    float overall_average;
};

// Function to create a new empty file
FILE *create_file()
{
    FILE *file;
    file = fopen("students.txt", "w");

    if (file == NULL)
    {
        printf("Error opening the file.");
        return NULL;
    }

    fprintf(file, "%-15s %-17s %-14s %s\n", "Last Name:","First Name:","Group:","Overall Average:");
    fclose(file);
    return file;
}

// Function to add student data to the file
void fill_file(FILE *file, struct Student students[], int *num_students)
{
    int choice = 1;
    struct Student student;

    while (choice)
    {
        file = fopen("students.txt", "a");

        printf("\nEnter information for student:\n");
        printf("Last Name: ");
        scanf("%s", student.last_name);
        printf("First Name: ");
        scanf("%s", student.first_name);
        printf("Group: ");
        scanf("%d", &student.group);
        printf("Overall Average: ");
        scanf("%f", &student.overall_average);

        students[*num_students] = student;
        (*num_students)++;

        fprintf(file, "%-15s %-17s %-14d %.2f\n",
                student.last_name, student.first_name, student.group, student.overall_average);

        fclose(file);
        printf("Do you want to add another student (1 for yes, 0 for no): ");
        scanf("%d", &choice);
    }
    printf("------------Students added successfully------------\n");
}

// Function to display the content of the file
void display_file_content(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
    }

    char ch;
    printf("\n");
    while ((ch = fgetc(file)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(file);
}

// Function to search for a student by first name
void search_student_by_first_name(struct Student students[], int num_students)
{
    char search_name[50];
    printf("Enter first name to search: ");
    scanf("%s", &search_name);

    int found = 0;
    for (int i = 0; i < num_students; i++)
    {
        if (strcmp(students[i].first_name, search_name) == 0)
        {
            if (!found)
            {
                printf("\n------------Student found------------\n");
                printf("Last Name\tFirst Name\tGroup\tOverall Average\n");
                found = 1;
            }
            printf("%-10s\t%-10s\t%d\t%.2f\n", students[i].last_name, students[i].first_name,
                   students[i].group, students[i].overall_average);
            return;
        }
    }

    if (!found)
        printf("\n------------Student not found------------\n");
}

// Function to search for a student by last name
void search_student_by_last_name(struct Student students[], int num_students)
{
    char search_name[50];
    printf("Enter last name to search: ");
    scanf("%s", &search_name);

    int found = 0;
    for (int i = 0; i < num_students; i++)
    {
        if (strcmp(students[i].last_name, search_name) == 0)
        {
            if (!found)
            {
                printf("\n------------Student found------------\n");
                printf("Last Name\tFirst Name\tGroup\tOverall Average\n");
                found = 1;
            }
            printf("%-10s\t%-10s\t%d\t%.2f\n", students[i].last_name, students[i].first_name,
                   students[i].group, students[i].overall_average);
            return;
        }
    }

    if (!found)
        printf("\n------------Student not found------------\n");
}

// Function to search for a student by group
void search_student_by_group(struct Student students[], int num_students)
{
    int search_group;
    printf("Enter Group to search: ");
    scanf("%d", &search_group);

    int found = 0;
    for (int i = 0; i < num_students; i++)
    {
        if (students[i].group == search_group)
        {
            if (!found)
            {
                printf("\n------------Student found------------\n");
                printf("Last Name\tFirst Name\tGroup\tOverall Average\n");
                found = 1;
            }
            printf("%-10s\t%-10s\t%d\t%.2f\n", students[i].last_name, students[i].first_name,
                   students[i].group, students[i].overall_average);
        }
    }
    if (!found)
        printf("\n------------Student not found------------\n");
}

// Function to search for a student by average
void search_student_by_average(struct Student students[], int num_students)
{
    float search_average;
    printf("Enter Average to search: ");
    scanf("%f", &search_average);

    int found = 0;
    for (int i = 0; i < num_students; i++)
    {
        if (students[i].overall_average == search_average)
        {
            if (!found)
            {
                printf("\n------------Student found------------\n");
                printf("Last Name\tFirst Name\tGroup\tOverall Average\n");
                found = 1;
            }
            printf("%-10s\t%-10s\t%d\t%.2f\n", students[i].last_name, students[i].first_name,
                   students[i].group, students[i].overall_average);
        }
    }
    if (!found)
        printf("\n------------Student not found------------\n");
}

// Search for a student based on user choice
void search_student(struct Student students[], int num_students)
{
    int choice;
    printf("\nSearch a student by:\n");
    printf("1. First Name\n");
    printf("2. Last Name\n");
    printf("3. Group\n");
    printf("4. Overall Average\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        search_student_by_first_name(students, num_students);
        break;
    case 2:
        search_student_by_last_name(students, num_students);
        break;
    case 3:
        search_student_by_group(students, num_students);
        break;
    case 4:
        search_student_by_average(students, num_students);
        break;
    default:
        break;
    }
}

// Function to sort students by overall average
void sort_students(FILE *file, struct Student students[], int num_students)
{
    for (int i = 0; i < num_students - 1; i++)
    {
        for (int j = 0; j < num_students - i - 1; j++)
        {
            if (students[j].overall_average > students[j + 1].overall_average)
            {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    file = fopen("students.txt", "w");
    fprintf(file, "%-15s %-17s %-14s %s\n", "Last Name:","First Name:","Group:","Overall Average:");
    for (int i = 0; i < num_students; i++)
    {
        fprintf(file, "%-15s %-17s %-14d %.2f\n",
                students[i].last_name, students[i].first_name, students[i].group, students[i].overall_average);
    }
    fclose(file);
    printf("\n------------Students sorted by overall average------------\n");
}

// Function to delete a student from the list
void delete_student(FILE *file, struct Student students[], int *num_students)
{
    char first_name[50];
    printf("Enter first name to delete: ");
    scanf("%s", &first_name);
    char last_name[50];
    printf("Enter last name to delete: ");
    scanf("%s", &last_name);

    int found = 0;
    for (int i = 0; i < *num_students; i++)
    {
        if (strcmp(students[i].first_name, first_name) == 0 && strcmp(students[i].last_name, last_name) == 0)
        {
            found = 1;
            for (int j = i; j < *num_students - 1; j++)
            {
                students[j] = students[j + 1];
            }
            (*num_students)--;
            break;
        }
    }

    if (!found)
    {
        printf("------------Student not found------------\n");
        return;
    }

    file = fopen("students.txt", "w");
    if (file == NULL)
    {
        printf("Error opening the file.");
        return;
    }

    fprintf(file, "%-15s %-17s %-14s %s\n", "Last Name:","First Name:","Group:","Overall Average:");
    for (int i = 0; i < *num_students; i++)
    {
        fprintf(file, "%-15s %-17s %-14d %.2f\n",
                students[i].last_name, students[i].first_name, students[i].group, students[i].overall_average);
    }
    fclose(file);
    printf("------------Student deleted------------\n");
}

int main()
{
    FILE *file = create_file();
    if (file == NULL)
    {
        return 1;
    }

    struct Student students[MAX_STUDENTS];
    int num_students = 0;
    int choice;

    do
    {
        printf("\nMenu:\n");
        printf("1. Add student\n");
        printf("2. Display all students\n");
        printf("3. Search student\n");
        printf("4. Sort students by overall average\n");
        printf("5. Delete student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fill_file(file, students, &num_students);
            break;
        case 2:
            display_file_content("students.txt");
            break;
        case 3:
            search_student(students, num_students);
            break;
        case 4:
            sort_students(file, students, num_students);
            break;
        case 5:
            delete_student(file, students, &num_students);
            break;
        case 0:
            printf("------------Exiting program------------\n");
            break;
        default:
            printf("------------Invalid choice. Please try again------------\n");
            break;
        }
    } while (choice != 0);

    fclose(file);

    return 0;
}