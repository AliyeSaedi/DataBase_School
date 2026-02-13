#include <stdio.h>

#define MAX_DATA_LENGTH 50

void MainMenu();
void Insert_Student_Data_Menu();
void Insert_Student_Name();
void Show_Student_Data();
void Exit_Key();

int main(){
	printf("\n welcome to School DataBase \n");
	MainMenu();
	return 0;
}

void MainMenu(){
	int key;
	printf("\n Main Menu \n");
	while(1){
		//دکمه های برنامه
		printf("\n\tINSERT[1] \t SHOW[2]\n");
		printf("\ntype your key: ");
		scanf(" %d",&key);
		
		//دکمه ورود اطلاعات دانش آموزان و نمرات
		if(key == 1){
			Insert_Student_Data_Menu();
		}
		
		// دکمه نمایش اطلاعات وارد شده
		else if(key == 2){
			Show_Student_Data();
		}
	}
}

void Insert_Student_Data_Menu(){
	printf("\n\tINSERT STUDENT DATA MENU\n");		
	printf("\n\t Insert Student Name[1] \t Insert Student Course[2] \t EXIT[3] \n");
	printf("\ntype your key: ");
	
	int key;
	scanf("%d",&key);
	
	if(key == 1){
		Insert_Student_Name();
	}
	else if(key == 2){
		
	}
	else if(key == 3){
		Exit_Key();
	}
}

void Insert_Student_Name(){
	int number_of_students=0, i;
	int number_of_student_lessons=0;
	int students_names [number_of_students][MAX_DATA_LENGTH];
	int student_lessons [number_of_student_lessons][MAX_DATA_LENGTH];
	
	//دریافت تعداد دانش آموزان و تعداد دروس
	printf("tedad danesh amozan ra vared konid: ");
	scanf("%d",&number_of_students);
	printf("tedad doroos danesh amozan ro vared konid: ");
	scanf("%d",&number_of_student_lessons);
	
	for(i = 0; i < number_of_students; i++){
		printf("name danesh amoz %d ra vared konid: ", i + 1);
		scanf("%s",&students_names[i]);
	}
	
}

void Show_Student_Data(){
	printf("\n\tSHOW STUDENT DATA\n");
}

void Exit_Key(){
	printf("\n\tEXITED\n");
	printf("=====================================");
	MainMenu();
}