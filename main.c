#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DATA_LENGTH 50
#define MAX_STUDENTS 100
#define MAX_LESSONS 20

char students_names[MAX_STUDENTS][MAX_DATA_LENGTH];
int student_lessons[MAX_STUDENTS][MAX_LESSONS];

int number_of_students = 0;
int number_of_lessons = 0;

//functions
void MainMenu();
void InsertStudent();
void InsertCourses();
void ShowData();
void EditStudent();
void DeleteStudent();
void ClearInput();
void ExitProgram();
void SaveData();
void LoadData();

//manage file
FILE *fptr;

int main() {
    printf("\n==============================");
    printf("\n   School Database System");
    printf("\n==============================\n");
    
    // Load data from file at program start
    LoadData();
    
    MainMenu();
    
    return 0;
}

/* Clear input buffer */
void ClearInput() {
    while (getchar() != '\n');
}

/* Save data to file */
void SaveData() {
    fptr = fopen("Database.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    fprintf(fptr, "%d\n", number_of_students);
    fprintf(fptr, "%d\n", number_of_lessons);
    
    for (int i = 0; i < number_of_students; i++) {
        fprintf(fptr, "%s\n", students_names[i]);
        
        for (int j = 0; j < number_of_lessons; j++) {
            fprintf(fptr, "%d", student_lessons[i][j]);
            if (j < number_of_lessons - 1) {
                fprintf(fptr, " ");
            }
        }
        fprintf(fptr, "\n");
    }
    
    fclose(fptr);
    printf("Data saved successfully!\n");
}

/* Load data from file */
void LoadData() {
    fptr = fopen("Database.txt", "r");
    if (fptr == NULL) {
        printf("No file found for loading. A new file will be created.\n");
        return;
    }
    
    // Read number of students and lessons
    if (fscanf(fptr, "%d", &number_of_students) != 1) {
        printf("Error reading file!\n");
        fclose(fptr);
        return;
    }
    
    if (fscanf(fptr, "%d", &number_of_lessons) != 1) {
        printf("Error reading file!\n");
        fclose(fptr);
        return;
    }
    
    // Read information for each student
    for (int i = 0; i < number_of_students; i++) {
        // Read newline after numbers
        fgetc(fptr);
        
        // Read name
        if (fgets(students_names[i], MAX_DATA_LENGTH, fptr) == NULL) {
            printf("Error reading name for student %d\n", i + 1);
            break;
        }
        // Remove newline from end of name
        students_names[i][strcspn(students_names[i], "\n")] = '\0';
        
        // Read grades
        for (int j = 0; j < number_of_lessons; j++) {
            if (fscanf(fptr, "%d", &student_lessons[i][j]) != 1) {
                printf("Error reading grade %d for student %d\n", j + 1, i + 1);
                break;
            }
        }
    }
    
    fclose(fptr);
    printf("Data loaded successfully from file!\n");
    printf("Number of students: %d\n", number_of_students);
    printf("Number of lessons: %d\n", number_of_lessons);
    
    // Display loaded information
    if (number_of_students > 0) {
        printf("\nLoaded students:\n");
        for (int i = 0; i < number_of_students; i++) {
            printf("%d. %s\n", i + 1, students_names[i]);
        }
    }
}

/* Main menu */
void MainMenu() {
    int key;
    
    while (1) {
        printf("\n=========== MAIN MENU ===========\n");
        printf("1. Insert Student\n");
        printf("2. Insert Courses\n");
        printf("3. Show Data\n");
        printf("4. Edit Student\n");
        printf("5. Delete Student\n");
        printf("6. Save Data\n");
        printf("7. Exit\n");
        printf("Select: ");
        
        scanf("%d", &key);
        ClearInput();
        
        switch (key) {
            case 1:
                InsertStudent();
                break;
                
            case 2:
                InsertCourses();
                break;
                
            case 3:
                ShowData();
                break;
                
            case 4:
                EditStudent();
                break;
                
            case 5:
                DeleteStudent();
                break;
                
            case 6:
                SaveData();
                break;
                
            case 7:
                // Auto save before exit
                SaveData();
                ExitProgram();
                return;
                
            default:
                printf("Invalid option!\n");
        }
    }
}

/* Add student */
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
        number_of_students++;
    }
    
    printf("Students added successfully!\n");
}

/* Add courses/grades */
void InsertCourses() {
    if (number_of_students == 0) {
        printf("No students yet!\n");
        return;
    }
    
    if (number_of_lessons == 0) {
        printf("How many lessons? ");
        scanf("%d", &number_of_lessons);
        ClearInput();
        
        if (number_of_lessons > MAX_LESSONS) {
            number_of_lessons = 0;
            printf("Too many lessons!\n");
            return;
        }
    }
    
    for (int i = 0; i < number_of_students; i++) {
        printf("\nStudent: %s\n", students_names[i]);
        
        for (int j = 0; j < number_of_lessons; j++) {
            printf("Lesson %d: ", j + 1);
            scanf("%d", &student_lessons[i][j]);
        }
    }
    
    ClearInput();
    printf("Courses saved!\n");
}

/* Show data */
void ShowData() {
    if (number_of_students == 0) {
        printf("No data available!\n");
        return;
    }
    
    printf("\n=========== STUDENTS DATA ===========\n");
    printf("Total Students: %d\n", number_of_students);
    printf("Total Lessons: %d\n", number_of_lessons);
    
    for (int i = 0; i < number_of_students; i++) {
        printf("\n%d. %s\n", i + 1, students_names[i]);
        
        if (number_of_lessons > 0) {
            printf("   Grades: ");
            
            float sum = 0;
            for (int j = 0; j < number_of_lessons; j++) {
                printf("%d ", student_lessons[i][j]);
                sum += student_lessons[i][j];
            }
            
            if (number_of_lessons > 0) {
                printf("(Avg: %.2f)", sum / number_of_lessons);
            }
            printf("\n");
        }
    }
}

/* Edit student */
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
    
    /* Change name */
    printf("New name: ");
    fgets(students_names[index], MAX_DATA_LENGTH, stdin);
    students_names[index][strcspn(students_names[index], "\n")] = '\0';
    
    /* Change grades */
    if (number_of_lessons > 0) {
        printf("Enter new grades:\n");
        
        for (int j = 0; j < number_of_lessons; j++) {
            printf("Lesson %d: ", j + 1);
            scanf("%d", &student_lessons[index][j]);
        }
        
        ClearInput();
    }
    
    printf("Student updated!\n");
}

/* Delete student */
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
    
    /* Shift array */
    for (int i = index; i < number_of_students - 1; i++) {
        strcpy(students_names[i], students_names[i + 1]);
        
        for (int j = 0; j < number_of_lessons; j++) {
            student_lessons[i][j] = student_lessons[i + 1][j];
        }
    }
    
    number_of_students--;
    
    printf("Student deleted!\n");
}

/* Exit */
void ExitProgram() {
    printf("\n==============================");
    printf("\n   Program Closed");
    printf("\n==============================\n");
}