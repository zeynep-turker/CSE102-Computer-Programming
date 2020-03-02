#include <stdio.h>
#include <stdlib.h> /*malloc kullandigim icin bu kutuphaneyi tanimladim*/
#include <string.h> /*strcpy kullandigim icin bu kutuphaneyi tanimladim*/

typedef struct customer {
char name[30];
char surname[30];
int age;
char gender[10];
int roomNumber;
struct customer *next;
}customers;

typedef struct room{
int number;
int capacity;
int floor;
customers *customer;
struct room *next;
}rooms;

int add_room_to_end(FILE *roomFile,rooms **startRoom);/*bu fonksiyonu, belirtmediginiz icin dosyadan okuyup room linked list yapan sekilde yaptim*/
void add_room_after_room_number (rooms **startRoom,int roomNumber);
int add_customer_to_end(FILE *customerFile,customers **startCustomer);/*bu fonksiyonu,belirtmediginiz icin dosyadan okuyup customer linked list yapan sekilde yaptim*/
void link_customers_to_room(rooms *startRoom,customers *startCustomer);
void remove_room (rooms **startRoom,int deleteNumber);
void show_vacancy(rooms *startRoom);
void get_by_floor(rooms *startRoom,int floor);
void print_list (rooms *startRoom);
void extractString(char str[],char surname[],char gender[],int *age);/*stringi customerin surname i,gender i,age i sekilinde ayiran kendi ekledigim fonksiyon*/
void Test();

int main()
{
	Test();
	
	return 0;
}

void Test() /*kendime gore yaptigim butun fonksiyonlarin calistigi test fonksiyonu*/
{
	FILE *customerFile,*roomFile;
	rooms *startRoom=NULL;
	customers *startCustomer=NULL;
	int num=5,num2=4;
	roomFile=fopen("rooms.txt","r");
	if(roomFile == NULL)
	{
		printf("Room File Open Error\n");
		exit(1);	
	}
	while( num == 5 ) /*bu dongu add_room_to_end fonksiyonunun return ettigi deger 5 oldugu surece calisir,boylece room linked listi olusur*/
	{
		num=add_room_to_end(roomFile,&startRoom);
	}
	fclose(roomFile);
	printf("***Get By Floor Function***\n");	
	get_by_floor(startRoom,1);
	printf("***Add Room After Room Number***\n");	
	add_room_after_room_number(&startRoom,105);
	printf("***Remove Room Function***\n");		
	remove_room(&startRoom,107);
	printf("***Get By Floor Function***\n");
	get_by_floor(startRoom,1);

	customerFile=fopen("customers.txt","r");
	if(customerFile == NULL)
	{
		printf("Customer File Open Error\n");
		exit(1);	
	}
	while( num2 == 4 )  /*bu dongu add_room_to_end fonksiyonunun return ettigi deger 4 oldugu surece calisir,boylece room linked listi olusur*/
	{
		num2=add_customer_to_end(customerFile,&startCustomer);
	}
	fclose(customerFile);
	/* Link Customer To Room */
	link_customers_to_room(startRoom,startCustomer);
	printf("***Show Vacancy Function***\n");
	show_vacancy(startRoom);
	printf("***Print List Function***\n");
	print_list(startRoom);
	
}

void link_customers_to_room(rooms *startRoom,customers *startCustomer)/*bu fonksiyona room ve customer linked listlerinin baslari gelir*/
{
	rooms *tempRoom,*startLink;/*startLink her room node icin customerlerinin baglanmaya basladigi yerdir ve ilk olarak NULL u gosterir*/
	customers *tempCustomer,*tempLink,*addedLink;
	tempRoom=startRoom;/*roomlari gezen pointer olan tempRoom ilk olarak room listin basi olan startRoom u gosterir*/
	tempCustomer=startCustomer;/*customerleri gezen pointer olan tempCustomer ilk olarak customer listin basi olan startCustomer i gosterir*/
	
	while(tempRoom != NULL)/*while butun roomlari gezer*/
	{
		startLink=tempRoom;
		startLink->customer=NULL;
		while(tempCustomer != NULL)
		{
			if(tempCustomer->roomNumber == tempRoom->number) /*customerlerin oda nosu tempRoomun numberina esitse bu customer addedLink adli pointera kopyalanir*/
			{
				addedLink=(customers*)malloc(sizeof(customers));
				addedLink->age=tempCustomer->age;
				addedLink->roomNumber=tempCustomer->roomNumber;
				strcpy(addedLink->name,tempCustomer->name);
				strcpy(addedLink->surname,tempCustomer->surname);
				strcpy(addedLink->gender,tempCustomer->gender);
				addedLink->next=NULL;
				if(startLink->customer==NULL){
					startLink->customer=addedLink;
				}
				else
				{	
					tempLink=startLink->customer;
					while(tempLink->next != NULL)
					{	
						tempLink=tempLink->next;
					}
					tempLink->next=addedLink;
					tempLink=addedLink;
				}
			}

			tempCustomer=tempCustomer->next;
		}
		tempCustomer=startCustomer;/*tempCustomer tekrar customer listin basini gosterir*/
		tempRoom=tempRoom->next;
	}
}

int add_room_to_end(FILE *roomFile,rooms **startRoom) /*bu fonksiyon pdf de oda kullanicidan alinmali diye belirtilmedigi icin ben dosyadan okunup*/
{													/*room listi olusturalacak diye anladim ve bu sekilde yaptim*/
	rooms *addedRoom,*tempRoom;
	int number,capacity,floor,num;
	char buf;
	
	num=fscanf(roomFile,"%d%c%d%c%d",&number,&buf,&capacity,&buf,&floor);/*room dosyasindan bir satirdaki odaya ait bilgiler alinir ve node a ait bilgilere atilir.*/
	
	if(num==5){ /*dosyanin sonuna gelip feof u alip hata vermesin diye fscanfle alinan degisken sayisinin 5 oldugu surece asagidaki islemler yapilir*/
		addedRoom=(rooms*)malloc(sizeof(rooms));
		addedRoom->number=number;
		addedRoom->capacity=capacity;
		addedRoom->floor=floor;
		addedRoom->next=NULL;
	
		if(*startRoom == NULL)
			*startRoom=addedRoom;
		else
		{
			tempRoom=*startRoom;
			while(tempRoom->next != NULL)
				tempRoom=tempRoom->next;
			tempRoom->next=addedRoom;
		}
	}	
	return num;	
}

void add_room_after_room_number (rooms **startRoom,int roomNumber)
{
	rooms *tempRoom,*addedRoom,*lastRoom;
	int number,capacity,floor;
	
	tempRoom=*startRoom;
	printf("Enter a room number: \n"); /*kullanicidan eklenecek odanin bilgileri istenir*/
	scanf("%d",&number);
	printf("Enter a room capacity: \n");
	scanf("%d",&capacity);	
	printf("Enter a room floor: \n");
	scanf("%d",&floor);	
			
	addedRoom=(rooms*)malloc(sizeof(rooms));
	addedRoom->number=number;
	addedRoom->capacity=capacity;
	addedRoom->floor=floor;
	addedRoom->next=NULL;
	
	while(tempRoom != NULL) 
	{
		lastRoom=tempRoom->next; /*tempRoomdan bir sonraki node tutulur*/
		if(tempRoom->number == roomNumber){
			addedRoom->next=lastRoom;
			tempRoom->next=addedRoom;
			return;
		}

		tempRoom=tempRoom->next;
	}
	tempRoom=*startRoom; /*eger eklenecek oda bulunan odalarin icinde yoksa room listinin sonuna eklenir*/
	while(tempRoom->next != NULL)
		tempRoom=tempRoom->next;
	tempRoom->next=addedRoom;
}

int add_customer_to_end(FILE *customerFile,customers **startCustomer)/*bu fonksiyon pdf de customer kullanicidan alinmali diye belirtilmedigi icin ben dosyadan okunup*/
{																	/*customer listi olusturalacak diye anladim ve bu sekilde yaptim*/
	customers *addedCustomer,*tempCustomer;
	int number,age=0,num;
	char buf,name[50],surname[50],gender[10],restStr[100];
	
	num=fscanf(customerFile,"%d%c%s%s",&number,&buf,name,restStr);/*customer larin oda numarisi, name i ve satirin geri kalani string bir sekilde alinir*/
	extractString(restStr,surname,gender,&age);/*alinan stringden customerlerin surname i, gender i ve age i ayristirilir.*/
	
	if(num == 4) { /*fscanfle alinan elemanlar 4 oldugu yani dosyanin sonuna gelmedigi surece asagidaki islemler calisir*/
		addedCustomer=(customers*)malloc(sizeof(customers));
		addedCustomer->age=age;
		addedCustomer->roomNumber=number;
		strcpy(addedCustomer->name,name);
		strcpy(addedCustomer->surname,surname);
		strcpy(addedCustomer->gender,gender);
		addedCustomer->next=NULL;
		if(*startCustomer == NULL)
			*startCustomer=addedCustomer;
		else
		{
			tempCustomer=*startCustomer;
			while(tempCustomer->next != NULL)
				tempCustomer=tempCustomer->next;
			tempCustomer->next=addedCustomer;
		}	
	}
	return num;		
	
}

void remove_room (rooms **startRoom,int deleteNumber)
{
	rooms *tempRoom,*deleteRoom;
	
	tempRoom=*startRoom;
	if(deleteNumber == (*startRoom)->number){ /*eger silinecek o da link listin ilk elemani ise startRoom bir sonraki node olur ve eski node u free edilir.*/
		*startRoom=(*startRoom)->next; 
		free(tempRoom);
		return;
	}
	while(tempRoom != NULL){
		if(tempRoom->next->number == deleteNumber) {/*tempRoom un nexti silinecek odanin numarisiysa deleteRoom bu odayi gosterir ve tempNode un nexti de */
			deleteRoom=tempRoom->next;				/*silinecek olan odadan sonraki node u gosterir sonrada deleteRoom free edilir.*/
			tempRoom->next=tempRoom->next->next;
			free(deleteRoom);						
			return;
		}
		tempRoom=tempRoom->next;
	}	
}

void show_vacancy(rooms *startRoom)
{	
	rooms *tempRoom;	
	tempRoom=startRoom;

	printf("**Empty Rooms** \n");
	while(tempRoom != NULL) /*icinde customer kalmayan odalar her room node un customerlerine bakilarak ekrana bastirilir*/
	{
		if(tempRoom->customer == NULL) /*room node un customer i NULL sa bastirilir*/
			printf("=> %d\n",tempRoom->number);
		tempRoom=tempRoom->next;					
	}
	printf("\n");
}

void get_by_floor(rooms *startRoom,int floor) /*odalarin bulundugu link listin basi ve odalarinin gosterilmesi istenen koridor parametre olarak fonksiyona gelir.*/
{
	rooms *tempRoom;/*startRoomdan baslayarak listeyi gezecek bir pointer tanimladim*/
	
	tempRoom=startRoom;

	while(tempRoom != NULL) /*odalarin bulundugu listeninin sonuna gelinceye kadar odalarin bulundugu kat kontrol edilir*/
	{						/*ve koridor numarasi parametre olarak gelen sayiyla ayniysa ekrana basilir*/
		if(tempRoom->floor == floor)
			printf("Room -> %d\n",tempRoom->number);
		tempRoom=tempRoom->next;
	}
	printf("\n");	
}

void print_list (rooms *startRoom)
{
	
	rooms *tempRoom;
	tempRoom=startRoom;

	while(tempRoom != NULL) /*room listi bitene kadar calisir*/
	{					
		printf("Room %d (Floor %d - capacity %dx):\n",tempRoom->number,tempRoom->floor,tempRoom->capacity); /*her odanin bilgileri*/
		if(tempRoom->customer == NULL) /*eger odanin customeri NULL sa oda bostur ve empty olarak ekrana basilir*/
			printf("-> Empty\n");
		else 
		{
			while(tempRoom->customer != NULL)
			{		/*odalarda kalan her customerin bilgileri ekrana bastirilir*/
				printf("-> %s %s (%d - %s)\n",tempRoom->customer->name,tempRoom->customer->surname,tempRoom->customer->age,tempRoom->customer->gender);
				tempRoom->customer=tempRoom->customer->next;
			}
		}	
		tempRoom=tempRoom->next;
	}
	printf("\n");
}

void extractString(char str[],char surname[],char gender[],int *age) /*customer link listi yaparken oda sayisini ve
 customer name i alip geri kalan değerler tek string olarak alinir,bu fonkiyonda stringi parçalar ve customer surname,age ve gender degerlerini doldurur*/
{
	int i,m,k,n;
	char strAge[10]; /*age i bulurken int e çevirelecek string*/
	
	for(i=0;str[i] != ',';i++) /*stringde ilk virgule kadar olan kelime surname a atanir*/
		surname[i]=str[i];
	surname[i]='\0';
	++i;	
	for(k=0;str[i] != ',';k++,i++)	/*ikinci virgule kadar olan sayi stringi alinir*/
		strAge[k]=str[i];
	strAge[k]='\0';
	++i;
	for (n=0; strAge[n] != '\0'; ++n) /*age stringi int e donusur*/
        *age = (*age)*10 + strAge[n] - '0';
  
	for(m=0;str[i] !='\0';m++,i++)/*ikinci virgülden stringin sonuna kadar olan stringde gender olarak atanir*/
		gender[m]=str[i];
	gender[m]='\0';	
	
		

}
