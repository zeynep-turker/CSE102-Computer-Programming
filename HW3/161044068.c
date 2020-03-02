#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
void triangleOfSequences();
void countOccurrence();
void horseRacingGame();
int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min, int max);
int numOfDigit(int number);	/*Benim ekstradan yazdigim basamak sayisinin bulundugu fonksiyon.*/

int main()
{

	menu();	/*Menunun print edildigi fonksiyona gider.*/
	
	return 0;
}	

void menu()
{
	int choice;
	int flag=1;	/*Kullaniciya menunun gosteriminin tekrari icin flag degerini 1'e atadim.*/
	
	do{
		printf("1.Horse Racing Game\n");
		printf("2.Occurrence Counter\n");
		printf("3.Triangle of Sequences\n");
		printf("0.Exit\n");
		printf("\n\n");
		printf("Enter your choice:");
		scanf("%d",&choice);
		printf("\n");
		
		switch(choice){	
			case 1 : horseRacingGame();break;
			case 2 : countOccurrence();break;
			case 3 : triangleOfSequences();break;
			case 0 : flag=0;break;	/*Secenegin 0 olmasi durumunda do while dongusunden cikilmasi icin flag degerini 0'a atadim.*/
			default : printf("Your choice is false!!!\n\n");
		}
	}
	while(flag==1);

}

void countOccurrence()
{
	int bigNum;
	int searchNum;
	int count=0;
	int sRemain,bRemain,c;
	int tempNum;
	int numCount=0;
	int numDigit;
	int term;
	int bigDigit;
	
	printf("Enter big Number: ");
	scanf("%d",&bigNum);
	printf("Enter Search Number: ");
	scanf("%d",&searchNum);
	
	numDigit=numOfDigit(searchNum);	/*Search yapilacak sayinin basamak sayisi bulunur.*/
	bigDigit=numOfDigit(bigNum);	/*Buyuk sayinin basamak sayisi bulunur.*/
	term=searchNum;					/*searchNum'in degeri term adli degiskene atanir.*/
	
	if(numDigit<2)	/*Search yapilacak sayi tek basamakliysa bu ifin icindekiler calisir.*/
	{
		
		while(bigNum != 0)
		{
			bRemain=bigNum%10;	/*Buyuk sayisini while dongusunun her basinda 10 ile kalani bulunur.*/
			/*Tek basamakli sayinin zaten 10 ile kalani kendisine esit olacagi icin onun 10 ile kalanini bulmadim.*/
			
			if(searchNum==bRemain)	/*Eger search sayi buyuk sayinin 10 ile kalanina esitse count degeri 1 artirilir.*/
				count++;
				
			bigNum=bigNum/10;	/*Dongunun sonunda buyuk sayinin diger bir basamak degerini bulmak icin sayi 10'a bolunur.*/
		}
		printf("Occurrence: %d\n\n",count);	/*Search edilen sayinin buyuk sayinin icinde kac kere oldugu print edilir.*/
	}
	else	/*Searh yapilacak sayinin basamak sayisi 12den buyukse else nin icindekiler calisir.*/
	{	
		while(bigDigit>=numDigit)	/*Buyuk sayinin icinde search edilecek sayinin kac kere oldugunu bulmamiz icin buyuk sayinin*/
		{							/*basamak sayisinin search edilecek sayinin basamak sayisindan buyuk ya da esit olmalidir.*/
			tempNum=bigNum/10;	
			bigDigit=numOfDigit(bigNum);
			
			for(c=0;c<numDigit;c++)		/*for dongusu search edilen sayinin basamak sayisi kadar doner.*/
			{
				sRemain=searchNum%10;	
				bRemain=bigNum%10;		
		
				if(sRemain==bRemain)   /*Eger sayilarin 10 ile kalanlari esitse count degiskeni 1 artirilir.*/
					count++;
		
				searchNum=searchNum/10;		
				bigNum=bigNum/10;		
			}
	
			bigNum=tempNum;	/*Buyuk sayinin bastaki bir sayinin silindigi sonraki sayilarinin oldugu tempNum degiskenine esitlenir.*/	
			searchNum=term;	/*Search edilen sayi tekrar kendi degerinin oldugu term degiskenine esitlenir.*/
			
			if(count==numDigit)	/*Eger count sayisi search edilen sayinin basamak sayisina esitse numCount degiskeni 1 artirilir.*/
			{					
				numCount++;
			}
			count=0; /*count degiskeni yukaridaki for dongusunde tekrar bastan kullanilabilmesi icin 0'a esitlenir.*/
				
		
		}
		printf("Occurrence: %d\n\n",numCount);		/*Search edilen sayinin buyuk sayinin icinde kac kere oldugu print edilir.*/
	
	}
}

int getInt(int mini, int maxi)	/*Belirli araliklar icinde kullanicidan sayi istenilen fonksiyon.*/
{
	int num;
	int flag=1;
	
	do{
	
		scanf("%d",&num);

		if(num>=mini && num<=maxi) /*Kullanici belirli araliklar icinde sayi uretirse flag 0 olur ve donguden cikilir.*/
			flag=0;
		else
			printf("Please enter a valid number between %d and %d\n",mini,maxi);
	}
	while(flag==1);		

	return num;
}

int numberGeneratorBetweenRange(int min, int max)	/*Belirli araliklar icinde random sayi uretme fonksiyonu*/
{
	int num;
	
	num=min+rand()%(max-min+1);
	
	return num;	
}

void horseRacingGame()
{
	int numOfHorse;	/*Rastgele atanilacak olan at sayisi icin numOfHorse degiskenini atadim*/
	int horseNum;	/*Kullanicinin 1 ve numOfHorse'un degeri arasindan secicek oldugu sayi icin bu degiskeni atadim.*/
	int timeLine;	/*Atlarin yarisi bitirme zamaninin cizgisel olarak belirlenmesi icin bu degiskeni atadim.*/
	int min=20,indexMin;	/*Atlarin yarisi bitirme zamanlarini karsilastirmek icin min degerini atadim ve */
	int i,j;			/*bu en kucuk degerin indexini bulmak icin indexMin degerini atadim.*/
	int temp;		/*Kullanicinin secmis oldugu atin yarisi bitirme zamaninin atandigi degisken.*/
	int count=0;	/*Bu degiskeni berabere olma durumlari icin tuttum.*/
	
	srand(time(NULL));
	
	numOfHorse=numberGeneratorBetweenRange(3,5);
	printf("Number of Horse: %d\n",numOfHorse);
	printf("Horse Number: ");	
	horseNum=getInt(1,numOfHorse);
	
	
	printf("Racing starts...\n");
	
	
	
	for(i=1;i<=numOfHorse;i++)
	{
		printf("Horse %i :",i);
		timeLine=numberGeneratorBetweenRange(10,20);	/*Her at icin yarisi bitirme zamanlari random olarak belirlenir.*/
		
		if(i==horseNum)
			temp=timeLine;	/*Kullanicinin secmis oldugu atin yarisi bitirme zamanini temp degsikenine atadim.*/
			
		for(j=1;j<=timeLine;j++)	/*Her at icin yarisi bitirme zamani kadar cizgi ekrana print edilir.*/
			printf("-");
		
		printf("\n");
		
		if(min>timeLine)	/*Min degerinden daha kucuk bir at hizi buyuklugu varsa min o buyukluge esitlenir*/
		{
			min=timeLine;
			indexMin=i;		/*Min degerinin bulundugu index indexMin adli degiskende tutulur.*/
			count=0;		/*Yeni bir min degeri oldugu icin count degiskeni 0'a atanir.*/
		}
		else if(min==timeLine) /*Eger ayni olan zamanlar varsa count degeri her seferinde 1 artilir.*/
			count++;
		
	}	
	
	if(min==temp)	
		printf("You win!! Winner is Horse %d \n\n",horseNum);
	else if(min != temp)	
		printf("You lose. Winner is Horse %d\n\n",indexMin);
	else if(min==temp && count !=0)
		printf("You win. Winner is Horse %d\n\n",horseNum);
	else if(min != temp && count != 0)
		printf("You lose. Winner is %d",indexMin);			
}

void triangleOfSequences() 
{
	int num;
	int i,j;
	
	num=numberGeneratorBetweenRange(2,10);	/*2 ve 10 arasindan rondom sekilde sayi uretilmesi icin */
											/*numberGeneratorBetweenRange adli fonksiyona gonderilir.*/
	printf("for %d\n\n",num);
	
	for(i=1;i<=num;i++)	/*num sayisi kadar satir print edilir.*/
	{
		for(j=i;j<=i*i;j=j+i)	/*j i'den baslayip her seferinde i kadar toplanip ixi ye kadar ekrana bastirilir.*/
		{
			printf("%d ",j);
		}
		printf("\n");
	}		
	printf("\n\n\n");
}	
	
int numOfDigit(int number)	/*countOccurrence adli fonksiyonda kullanilan basamak sayisinin bulundugu fonksiyon.*/
{
	int digit=0;
	
	while(number != 0)
	{
		number=number/10;
		digit++;
	}	

	return digit;
}		
