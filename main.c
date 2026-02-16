#include <stdio.h>
#include <string.h>

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

//manage file
FILE *fptr_fwrite;



int main() {

    printf("\n==============================");
    printf("\n   School Database System");
    printf("\n==============================\n");

    MainMenu();

    return 0;
}


/* پاک کردن بافر ورودی */
void ClearInput() {
    while (getchar() != '\n');
}


/* منوی اصلی */
void MainMenu() {

    int key;
	
	// نمایش تیتر برنامه در فایل
	fptr_fwrite = fopen("Database.txt","w");
	fprintf(fptr_fwrite,"\t\tW E L C O M E\n");
	fprintf(fptr_fwrite,"-------------------------------------\n");
	fprintf(fptr_fwrite,"\tDataBase School\n\n");
	fclose(fptr_fwrite);

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
	
	// ثبت تعداد دانش آموزان در فایل
	fptr_fwrite = fopen("Database.txt","a");
	fprintf(fptr_fwrite,"Number of students: %d\n",count);
	fclose(fptr_fwrite);
	
    ClearInput();

    if (number_of_students + count > MAX_STUDENTS) {
        printf("Max limit reached!\n");
        return;
    }

    for (int i = 0; i < count; i++) {

        printf("Enter name for student %d: ",
               number_of_students + 1);
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

        if (number_of_lessons > MAX_LESSONS) {
            number_of_lessons = 0;
            printf("Too many lessons!\n");
            return;
        }
    }

    for (int i = 0; i < number_of_students; i++) {

        printf("\nStudent: %s\n",students_names[i]);
		
		// نمایش نام هر دانش آموز در فایل
		fptr_fwrite = fopen("Database.txt","a");
		fprintf(fptr_fwrite,"\nStudent %d : %s \t\t ",i,students_names[i]);
		fclose(fptr_fwrite);

        for (int j = 0; j < number_of_lessons; j++) {

            printf("Lesson %d: ", j + 1);
            scanf("%d", &student_lessons[i][j]);
			
			// نمایش نمرات هر دانش آموز در فایل
			fptr_fwrite = fopen("Database.txt","a");
			fprintf(fptr_fwrite,"%d, " ,student_lessons[i][j]);
			fclose(fptr_fwrite);
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

        printf("\n%d. %s\n", i + 1,
               students_names[i]);

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


    /* تغییر نام */
    printf("New name: ");
    fgets(students_names[index],
          MAX_DATA_LENGTH,
          stdin);

    students_names[index]
    [strcspn(students_names[index], "\n")] = '\0';


    /* تغییر نمرات */
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


    /* شیفت دادن آرایه */
    for (int i = index; i < number_of_students - 1; i++) {

        strcpy(students_names[i],
               students_names[i + 1]);

        for (int j = 0; j < number_of_lessons; j++) {

            student_lessons[i][j] =
            student_lessons[i + 1][j];
        }
    }

    number_of_students--;

    printf("Student deleted!\n");
}


/* خروج */
void ExitProgram() {

    printf("\n==============================");
    printf("\n   Program Closed");
    printf("\n==============================\n");
}