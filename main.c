#include <stdio.h>
#include <string.h>

#define MAX_DATA_LENGTH 50
#define MAX_STUDENTS 100
#define MAX_LESSONS 20

// متغیرهای سراسری برای ذخیره اطلاعات
char students_names[MAX_STUDENTS][MAX_DATA_LENGTH];
int student_lessons[MAX_STUDENTS][MAX_LESSONS];
int number_of_students = 0;
int number_of_lessons = 0;


void MainMenu();
void Insert_Student_Data_Menu();
void Insert_Student_Name();
void Insert_Student_Course();
void Show_Student_Data();
void Exit_Key();

int main() {
    printf("\n=====================================");
    printf("\n  Welcome to School DataBase");
    printf("\n=====================================\n");
    MainMenu();
    return 0;
}

void MainMenu() {
    int key;
    
    while(1) {
        printf("\n=============== MAIN MENU ===============\n");
        printf("\n\tINSERT[1] \t SHOW[2] \t EXIT[3]\n");
        printf("\nType your key: ");
        scanf("%d", &key);
        
        if(key == 1) {
            Insert_Student_Data_Menu();
        }
        else if(key == 2) {
            Show_Student_Data();
        }
        else if(key == 3) {
            Exit_Key();
            break;  // خروج از حلقه while
        }
        else {
            printf("\nInvalid key! Please try again.\n");
        }
    }
}

void Insert_Student_Data_Menu() {
    int key;
    
    while(1) {
        printf("\n========= INSERT STUDENT DATA MENU =========\n");
        printf("\n\tInsert Student Name[1]");
        printf("\n\tInsert Student Course[2]");
        printf("\n\tReturn to Main Menu[3]");
        printf("\n\nType your key: ");
        scanf("%d", &key);
        
        if(key == 1) {
            Insert_Student_Name();
        }
        else if(key == 2) {
            Insert_Student_Course();
        }
        else if(key == 3) {
            return;  // بازگشت به منوی اصلی
        }
        else {
            printf("\nInvalid key! Please try again.\n");
        }
    }
}

void Insert_Student_Name() {
    int i, temp_count;
    
    printf("\n=== Insert Student Names ===\n");
    printf("Tedad danesh amoozan ra vared konid: ");
    scanf("%d", &temp_count);
    
    // بررسی محدودیت حداکثر دانش‌آموزان
    if(temp_count + number_of_students > MAX_STUDENTS) {
        printf("\nError! Maximum students is %d\n", MAX_STUDENTS);
        return;
    }
    
    // دریافت نام دانش‌آموزان جدید
    for(i = 0; i < temp_count; i++) {
        printf("Name danesh amooz %d ra vared konid: ", number_of_students + i + 1);
        scanf("%s", students_names[number_of_students + i]);
    }
    
    number_of_students += temp_count;
    printf("\n%d student(s) added successfully!\n", temp_count);
}

void Insert_Student_Course() {
    int i, j, temp_lessons;
    
    if(number_of_students == 0) {
        printf("\nError! Please insert student names first.\n");
        return;
    }
    
    printf("\n=== Insert Student Courses ===\n");
    
    // اگر اولین بار است که درس وارد می‌شود، تعداد دروس را بگیر
    if(number_of_lessons == 0) {
        printf("Tedad doroos ra vared konid: ");
        scanf("%d", &temp_lessons);
        
        // بررسی محدودیت حداکثر دروس
        if(temp_lessons > MAX_LESSONS) {
            printf("\nError! Maximum lessons is %d\n", MAX_LESSONS);
            return;
        }
        number_of_lessons = temp_lessons;
    }
    
    printf("\nNomre %d dars ra baraye har danesh amooz vared konid:\n", number_of_lessons);
    
    // دریافت نمرات همه دانش‌آموزان
    for(i = 0; i < number_of_students; i++) {
        printf("\nDanesh amooz %d (%s):\n", i + 1, students_names[i]);
        for(j = 0; j < number_of_lessons; j++) {
            printf("  Nomre dars %d: ", j + 1);
            scanf("%d", &student_lessons[i][j]);
        }
    }
    
    printf("\nAll courses added successfully!\n");
}

void Show_Student_Data() {
    int i, j;
    
    printf("\n=========== STUDENTS DATA ===========\n");
    
    if(number_of_students == 0) {
        printf("\nNo students registered yet!\n");
        return;
    }
    
    for(i = 0; i < number_of_students; i++) {
        printf("\n-------------------------------------\n");
        printf("Danesh amooz %d: %s\n", i + 1, students_names[i]);
        
        if(number_of_lessons > 0) {
            printf("Nomreha: ");
            for(j = 0; j < number_of_lessons; j++) {
                printf("%d ", student_lessons[i][j]);
            }
            printf("\n");
		}
		
    printf("\n=====================================\n");
    printf("Total students: %d\n", number_of_students);
    printf("Total lessons: %d\n", number_of_lessons);
	}
}

void Exit_Key() {
    printf("\n=====================================");
    printf("\n  Thank you for using School DataBase");
    printf("\n  Goodbye!");
    printf("\n=====================================\n");
}