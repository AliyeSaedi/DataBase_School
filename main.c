#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA_LENGTH 50
#define MAX_STUDENTS 100
#define MAX_LESSONS 20

char students_names[MAX_STUDENTS][MAX_DATA_LENGTH];
char student_ids[MAX_STUDENTS][20];
int academic_years[MAX_STUDENTS];
int student_lessons[MAX_STUDENTS][MAX_LESSONS];

int number_of_students = 0;
int number_of_lessons = 0;


void MainMenu();
void InsertStudent();
void InsertCourses();
void ShowData();
void EditStudent();
void DeleteStudent();
void ClearInput();
void ExitProgram();
void LoadData();
void SaveData();


void ClearInput() {
    while (getchar() != '\n');
}

int main() {
    printf("\n==============================");
    printf("\n   School Database System");
    printf("\n==============================\n");

    LoadData();   
    MainMenu();

    return 0;
}


void MainMenu() {
    int key;

    while (1) {
        printf("\n=========== MAIN MENU ===========\n");
        printf("1. Insert Student\n");
        printf("2. Insert Courses\n");
        printf("3. Show Data\n");
        printf("4. Edit Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit & SAVE\n");
        printf("Select: ");

        scanf("%d", &key);
        ClearInput();

        switch (key) {
            case 1: InsertStudent(); break;
            case 2: InsertCourses(); break;
            case 3: ShowData(); break;
            case 4: EditStudent(); break;
            case 5: DeleteStudent(); break;
            case 6: SaveData(); ExitProgram(); return;
            default: printf("Invalid option!\n");
        }
    }
}


void InsertStudent() {
    int count;

    printf("\nHow many students? ");
    scanf("%d", &count);
    ClearInput();

    if (number_of_students + count > MAX_STUDENTS) {
        printf("Max limit reached!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Enter name for student %d: ", number_of_students + 1);
        fgets(students_names[number_of_students], MAX_DATA_LENGTH, stdin);
        students_names[number_of_students][strcspn(students_names[number_of_students], "\n")] = '\0';

        printf("Enter student ID: ");
        fgets(student_ids[number_of_students], 20, stdin);
        student_ids[number_of_students][strcspn(student_ids[number_of_students], "\n")] = '\0';

        printf("Enter academic year: ");
        scanf("%d", &academic_years[number_of_students]);
        ClearInput();

        
        for (int j = 0; j < MAX_LESSONS; j++)
            student_lessons[number_of_students][j] = -1;

        number_of_students++;
    }

    SaveData();  
    printf("Students added successfully!\n");
}


void InsertCourses() {
    if (number_of_students == 0) {
        printf("No students yet!\n");
        return;
    }

    if (number_of_lessons == 0) {
        printf("How many lessons? ");
        scanf("%d", &number_of_lessons);

        if (number_of_lessons > MAX_LESSONS || number_of_lessons <= 0) {
            number_of_lessons = 0;
            printf("Invalid number of lessons!\n");
            return;
        }
    }

    for (int i = 0; i < number_of_students; i++) {
        printf("\nStudent: %s\n", students_names[i]);

        for (int j = 0; j < number_of_lessons; j++) {
            if (student_lessons[i][j] == -1) {
                printf("Enter grade for Lesson %d: ", j + 1);
                scanf("%d", &student_lessons[i][j]);
            }
        }
    }

    ClearInput();
    SaveData();
    printf("Courses saved!\n");
}


void ShowData() {
    if (number_of_students == 0) {
        printf("No data available!\n");
        return;
    }

    printf("\n=========== STUDENTS DATA ===========\n");

    for (int i = 0; i < number_of_students; i++) {
        printf("\n%d. %s\n", i + 1, students_names[i]);
        printf("ID: %s\n", student_ids[i]);
        printf("Year: %d\n", academic_years[i]);

        if (number_of_lessons > 0) {
            printf("Grades: ");
            for (int j = 0; j < number_of_lessons; j++) {
                if (student_lessons[i][j] != -1)
                    printf("%d ", student_lessons[i][j]);
                else
                    printf("_ "); // نمره خالی
            }
            printf("\n");
        }
    }
}


void EditStudent() {
    int index;

    if (number_of_students == 0) {
        printf("No students to edit!\n");
        return;
    }

    ShowData();

    printf("\nSelect student number: ");
    scanf("%d", &index);
    ClearInput();

    index--;

    if (index < 0 || index >= number_of_students) {
        printf("Invalid student!\n");
        return;
    }

    printf("New name: ");
    fgets(students_names[index], MAX_DATA_LENGTH, stdin);
    students_names[index][strcspn(students_names[index], "\n")] = '\0';

    printf("New student ID: ");
    fgets(student_ids[index], 20, stdin);
    student_ids[index][strcspn(student_ids[index], "\n")] = '\0';

    printf("New academic year: ");
    scanf("%d", &academic_years[index]);
    ClearInput();

    if (number_of_lessons > 0) {
        printf("Enter new grades (only if you want to change):\n");
        for (int j = 0; j < number_of_lessons; j++) {
            printf("Lesson %d (current: %s): ", j + 1, 
                   student_lessons[index][j] == -1 ? "none" : 
                   (char[10]){0});
            if (student_lessons[index][j] != -1)
                printf("%d", student_lessons[index][j]);
            int temp;
            if (scanf("%d", &temp) == 1)
                student_lessons[index][j] = temp;
            ClearInput();
        }
    }

    SaveData();
    printf("Student updated!\n");
}


void DeleteStudent() {
    int index;

    if (number_of_students == 0) {
        printf("No students to delete!\n");
        return;
    }

    ShowData();

    printf("\nSelect student number to delete: ");
    scanf("%d", &index);
    ClearInput();

    index--;

    if (index < 0 || index >= number_of_students) {
        printf("Invalid student!\n");
        return;
    }

    for (int i = index; i < number_of_students - 1; i++) {
        strcpy(students_names[i], students_names[i + 1]);
        strcpy(student_ids[i], student_ids[i + 1]);
        academic_years[i] = academic_years[i + 1];
        for (int j = 0; j < number_of_lessons; j++)
            student_lessons[i][j] = student_lessons[i + 1][j];
    }

    number_of_students--;
    SaveData();
    printf("Student deleted!\n");
}

void SaveData() {
    FILE *fptr = fopen("Database.txt", "w");

    if (fptr == NULL) {
        printf("Error saving file!\n");
        return;
    }

    fprintf(fptr, "%d\n", number_of_students);
    fprintf(fptr, "%d\n", number_of_lessons);

    for (int i = 0; i < number_of_students; i++) {
        fprintf(fptr, "%s %s %d ", students_names[i], student_ids[i], academic_years[i]);
        for (int j = 0; j < number_of_lessons; j++)
            fprintf(fptr, "%d ", student_lessons[i][j]);
        fprintf(fptr, "\n");
    }

    fclose(fptr);
}

void LoadData() {

    FILE *fptr;
    fptr = fopen("Database.txt", "r");

    if (fptr == NULL) {
        return;
    }

    fscanf(fptr, "%d", &number_of_students);
    fscanf(fptr, "%d", &number_of_lessons);

    for (int i = 0; i < number_of_students; i++) {

        fscanf(fptr, "%s", students_names[i]);
        fscanf(fptr, "%s", student_ids[i]);
        fscanf(fptr, "%d", &academic_years[i]);

        for (int j = 0; j < number_of_lessons; j++) {
            fscanf(fptr, "%d", &student_lessons[i][j]);
        }
    }

    fclose(fptr);
}

void ExitProgram() {
    printf("\n==============================");
    printf("\n   Program Closed");
    printf("\n==============================\n");
}