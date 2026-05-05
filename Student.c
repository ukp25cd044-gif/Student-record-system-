#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float m1, m2, m3;
    float total;
};

// Function to add student
void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter marks of 3 subjects: ");
    scanf("%f %f %f", &s.m1, &s.m2, &s.m3);

    s.total = s.m1 + s.m2 + s.m3;

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student record added successfully!\n");
}

// Function to display students
void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d\n", s.roll);
        printf("Name: %s\n", s.name);
        printf("Marks: %.2f %.2f %.2f\n", s.m1, s.m2, s.m3);
        printf("Total: %.2f\n", s.total);
        printf("----------------------\n");
    }

    fclose(fp);
}

// Function to generate rank list
void rankList() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s[100];
    int i = 0, j;
    struct Student temp;

    // Read all records into array
    while (fread(&s[i], sizeof(struct Student), 1, fp)) {
        i++;
    }
    fclose(fp);

    // Sort (descending by total marks)
    for (int x = 0; x < i - 1; x++) {
        for (int y = 0; y < i - x - 1; y++) {
            if (s[y].total < s[y + 1].total) {
                temp = s[y];
                s[y] = s[y + 1];
                s[y + 1] = temp;
            }
        }
    }

    // Display rank list
    printf("\n--- Rank List ---\n");
    for (j = 0; j < i; j++) {
        printf("Rank %d\n", j + 1);
        printf("Roll: %d\n", s[j].roll);
        printf("Name: %s\n", s[j].name);
        printf("Total: %.2f\n", s[j].total);
        printf("----------------------\n");
    }
}

// Main function
int main() {
    int choice;

    do {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Rank List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                rankList();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}
