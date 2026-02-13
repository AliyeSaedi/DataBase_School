#include <stdio.h>

#define MAX_DATA_LENGTH 50
#define MAX_COURS_LENGTH 50

void MenuKeys();
void Insert_Key();
void Exit_Key();
void Show_Key();
void Student();
void Insert_Data_Student();

int main(){
	MenuKeys();
	return 0;
}

void MenuKeys(){
	int key;
	printf("\n\tWELCOME TO SCHOOL DATABASE");
	
	while(1){
		//دکمه های برنامه
		printf("\n\tINSERT[1] \t SHOW[2]\n");
		printf("\ntype your key: ");
		scanf(" %d",&key);
		
		//دکمه ورود اطلاعات دانش آموزان و نمرات
		if(key == 1){
			Insert_Key();
		}
		
		// دکمه نمایش اطلاعات وارد شده
		else if(key == 2){
			Show_Key();
		}
	}
}

void Insert_Key(){
	printf("\n\tINSERT STUDENT DATA\n");		
	printf("\n\t Insert Student Name[1] \t Insert Student Course[2] \t EXIT[3] \n");
	printf("\ntype your key: ");
	
	int key;
	scanf("%d",&key);
	
	if(key == 1){
		Student();
	}
	else if(key == 2){
		Insert_Data_Student();
	}
	else if(key == 3){
		Exit_Key();
	}
}

void Exit_Key(){
	printf("\n\tEXITED\n");
	MenuKeys();
}

void Show_Key(){
	printf("\n\tSHOW STUDENT DATA\n");
}


void Student(){
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

void Insert_Data_Student(){
	int dars_counter, nomre, j;
	int daneshamoz_dars[dars_counter][MAX_COURS_LENGTH];
	
	printf("tedad dars har danesh amoz ra vared konid: ");
	scanf("%d",&dars_counter);
	
	for(j = 0; j < dars_counter; j++){
		printf("nomre daneshamoz X baraye darse %d ra vared konid: ", j + 1);
		scanf("%d",&daneshamoz_dars[j]);
	}
}