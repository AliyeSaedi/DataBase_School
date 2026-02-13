#include <stdio.h>

#define MAX_DATA_LENGTH 50
#define MAX_COURS_LENGTH 50

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
	int daneshamoz_counter, i;
	int daneshamoz_name [daneshamoz_counter][MAX_DATA_LENGTH];
	
	//تعداد دانش آموزان و تعدا دروس
	printf("tedad danesh amozan ra vared konid: ");
	scanf("%d",&daneshamoz_counter);
	
	for(i = 0; i < daneshamoz_counter; i++){
		printf("name danesh amoz %d ra vared konid: ", i + 1);
		scanf("%s",&daneshamoz_name[i]);
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