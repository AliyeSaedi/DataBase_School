#include <stdio.h>
#include <string.h>

#define MAX_DATA_LENGTH 50
#define MAX_STUDENTS 100
#define MAX_LESSONS 20

char students_names[MAX_STUDENTS][MAX_DATA_LENGTH];
int student_lessons[MAX_STUDENTS][MAX_LESSONS];

int number_of_students = 0;
int number_of_lessons = 0;

// functions
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

/* پاک کردن بافر ورودی */
void ClearInput() {
    while (getchar() != '\n');
}

int main() {

    printf("\n==============================");
    printf("\n   School Database System");
    printf("\n==============================\n");

    LoadData();   // لود اطلاعات در شروع برنامه
    MainMenu();

    return 0;
}

/* منوی اصلی */
void MainMenu() {

    int key;

    while (1) {

        printf("\n=========== MAIN MENU ===========\n");
        printf("1. Insert Student\n");
        printf("2. Insert Courses\n");
        printf("3. Show Data\n");
        printf("4. Edit Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
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
                ExitProgram();
                return;

            default:
                printf("Invalid option!\n");
        }
    }
}

/* افزودن دانش آموز */
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

        fgets(students_names[number_of_students],
              MAX_DATA_LENGTH,
              stdin);

        students_names[number_of_students]
        [strcspn(students_names[number_of_students], "\n")] = '\0';

        number_of_students++;
    }

    printf("Students added successfully!\n");
}

/* افزودن نمرات */
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

            printf("Lesson %d: ", j + 1);
            scanf("%d", &student_lessons[i][j]);
        }
    }

    ClearInput();
    printf("Courses saved!\n");
}

/* نمایش اطلاعات */
void ShowData() {

    if (number_of_students == 0) {
        printf("No data available!\n");
        return;
    }

    printf("\n=========== STUDENTS DATA ===========\n");

    for (int i = 0; i < number_of_students; i++) {

        printf("\n%d. %s\n", i + 1, students_names[i]);

        if (number_of_lessons > 0) {

            printf("Grades: ");

            for (int j = 0; j < number_of_lessons; j++) {
                printf("%d ", student_lessons[i][j]);
            }

            printf("\n");
        }
    }
}

/* ویرایش دانش آموز */
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

    students_names[index]
    [strcspn(students_names[index], "\n")] = '\0';

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

/* حذف دانش آموز */
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

        for (int j = 0; j < number_of_lessons; j++) {
            student_lessons[i][j] = student_lessons[i + 1][j];
        }
    }

    number_of_students--;

    printf("Student deleted!\n");
}

/* ذخیره اطلاعات در فایل */
void SaveData() {

    FILE *fptr = fopen("Database.txt", "w");

    if (fptr == NULL) {
        printf("Error saving file!\n");
        return;
    }

    fprintf(fptr, "%d\n", number_of_students);
    fprintf(fptr, "%d\n", number_of_lessons);

    for (int i = 0; i < number_of_students; i++) {

        fprintf(fptr, "%s ", students_names[i]);

        for (int j = 0; j < number_of_lessons; j++) {
            fprintf(fptr, "%d ", student_lessons[i][j]);
        }

        fprintf(fptr, "\n");
    }

    fclose(fptr);
}

/* خواندن اطلاعات از فایل */
void LoadData() {

    FILE *fptr = fopen("Database.txt", "r");

    if (fptr == NULL) {
        return;  // اگر فایل نبود، بی‌صدا ادامه بده
    }

    fscanf(fptr, "%d", &number_of_students);
    fscanf(fptr, "%d", &number_of_lessons);

    for (int i = 0; i < number_of_students; i++) {

        fscanf(fptr, "%s", students_names[i]);

        for (int j = 0; j < number_of_lessons; j++) {
            fscanf(fptr, "%d", &student_lessons[i][j]);
        }
    }

    fclose(fptr);
}

/* خروج */
void ExitProgram() {

    printf("\n==============================");
    printf("\n   Program Closed");
    printf("\n==============================\n");
}