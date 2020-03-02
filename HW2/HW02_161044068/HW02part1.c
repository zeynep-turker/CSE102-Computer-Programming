#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void options(void);
char letterGrade(int grade);

int main()
{
	int stuNum;			/*Oğrenci sayisi icin stuNum degiskenini atadim.*/ 
	int flag=0;			/*While döngüsüne girilmesi icin flag degiskenini 0'a atadim.*/
	int i,choice;
	int grade;
	int numA=0,numB=0,numC=0,numD=0,numF=0;		/*Harf notunun ders puanina gore artirilirken kullanilmasi icin  bu degiskenleri 0'a atadim.*/
	double total=0;
	char letterMax,letterMin;	/*En buyuk ve en kucuk ders puanlarinin harf notu icin bu degiskenleri atadim.*/
	int indexMax,indexMin;		/*En buyuk ve en kucuk ders puanlarinin indexleri icin bu degiskenleri atadim.*/
	int min=100,max=0;			/*Ders puanlarinin icinden en buyuk ve en kucuk degerleri bulabilmek icin min degerini*/
								/*en buyuk puan olan 100 degerine,max degerini ise en kucuk puan olan 0 degerine atadim.*/
	
	
	do{									
		printf("Enter student count:");		/*Ogrenci sayisina 3 ile 50 arasindan degerler girilene kadar donen bir do while dongusu yaptim.*/
		scanf("%d",&stuNum);				/*Bu dongu sadece flag degerinin 0'a esit oldugu durumlarda calisacak.Eger kullanici bu aralikta*/
		printf("\n\n");						/*bir deger girerse flag degeri 1'e esit olacak ve donguden cikilacak.*/
											
		if(stuNum > 2 && stuNum < 51)
			flag=1;	
		else
			printf("Not in Range!\n");
	
	}
	while(flag==0);	
	
	srand(40);	
	
	for(i=1;i<=stuNum;i++)	/*Butun islemler ogrenci sayisi kadar yapilacagi icin for dongusununu ogrenci sayisi kadar dondurdum.*/
	{
		grade=rand()%100;	/*Rand fonksiyonun 0 ile 100 arasinda degerler vermesi icin fonksiyonu 100 ile kalanını buluruz.*/
		printf("%d ",grade);
		
		if(max<grade)	/*Bu if'in icerisinde rastgele alinmis olan puanlar birbirleri ile karsilastirir ve en buyuk deger bulunur.*/
		{				/*Ayrica bu en buyuk puanin indexi ve harf notunu da bulunur.*/
			max=grade;
			indexMax=i;
			letterMax=letterGrade(grade);
		}
		if(min>grade)	/*Bu if'in icerisinde rastgele alinmis olan puanlar birbirleri ile karsilastirir ve en kucuk deger bulunur.*/
		{				/*Ayrica bu en kucuk puanin indexi ve harf notunu da bulunur.*/
			min=grade;
			indexMin=i;
			letterMin=letterGrade(grade);
		}
				
		if(grade>=90 && grade<=100)	/*Her bir ogrenci puani icin harf notu degeri bir artirilir.*/
			numA++;
		else if(grade>=80 && grade<=89)
			numB++;
		else if(grade>=70 && grade<=79)
			numC++;
		else if(grade>=60 && grade<=69)
			numD++;
		else if(grade>=0 && grade<=59){
			numF++;		
		}
		total=total+grade;	/*Ogrenci puanlarinin toplam degeri bulunur.*/
	}
	
	printf("\n\n");
	printf("Student Score Calculator Menu for %d Student\n\n",stuNum);
	
		
	while(flag==1){		/*Yukardaki do while dongusunden cikarken flag degeri 1'e esit oldugu icin bu while döngüsüne girilir.*/
	
		options();	/*While dongusu donerken her defasinda menunun gosterildigi fonksiyona gidilir.*/
	
		printf("Make Selection:");	
		scanf("%d",&choice);	/*Kullanicidan istedigi secenegin girilmesi beklenir.*/
		printf("\n\n");
		switch(choice){
			case -1 : flag = !flag;break;	/*Kullanici eger programdan cikmak istiyorsa -1 degerini girer.*/
			case 1: printf("Show most successful student:\n");	/*Kullanici 1 degerini girdiginde en basarili ogrencinin puani,indexi ve harf notu ekranda gosterilir.*/
							printf("Index : %d\n",indexMax);
							printf("Score : %d\n",max);
							printf("Letter Grade : %c\n\n",letterMax);
							break;
			case 2: printf("Show most unsuccessful student:\n");	/*Kullanici 2 degerini girdiginde en basarisiz ogrencinin puani,indexi ve harf notu ekranda gosterilir.*/
							printf("Index : %d\n",indexMin);
							printf("Score : %d\n",min);
							printf("Letter Grade : %c\n\n",letterMin);
							break;
			case 3: printf("List the number of students for each letter grade:\n");	/*Kullanici 3 degerini girdiginde her harf notu icin kac ogrencinin oldugu gösterilir.*/
							printf("%d student got letter grade 'A'\n",numA);
							printf("%d student got letter grade 'B'\n",numB);
							printf("%d student got letter grade 'C'\n",numC);
							printf("%d student got letter grade 'D'\n",numD);
							printf("%d student got letter grade 'F'\n\n",numF);
							break;
			case 4: printf("Show calculated average grade: %.2f\n\n",total/stuNum);	/*Kullanici 4 degerini girdiginde puan ortalamasi gösterilir.*/
							break;													/*Ortalama degerin virgulden sonra 2 rakaminin gösterilmesi icin .2f ifadesini kullandim.*/
			case 5: printf("Show all four options data:\n\n");	/*Kullanici 5 degerini girdiginde dıger seceneklerdeki butun veriler ekranda gosterilir.*/
							printf("Index : %d\n",indexMax);
							printf("Score : %d\n",max);
							printf("Letter Grade : %c\n",letterMax);
							printf("\n\n");
							printf("Index : %d\n",indexMin);
							printf("Score : %d\n",min);
							printf("Letter Grade : %c\n",letterMin);
							printf("\n\n");
							printf("%d student got letter grade 'A'\n",numA);
							printf("%d student got letter grade 'B'\n",numB);
							printf("%d student got letter grade 'C'\n",numC);
							printf("%d student got letter grade 'D'\n",numD);
							printf("%d student got letter grade 'F'\n",numF);
							printf("\n\n");
							printf("The average score of %d student is %.2f\n\n",stuNum,total/stuNum);
							break;
			default: printf("False Selection!!!\n\n");	/*Eger kullanici -1,1,2,3,4,5 degerlerinden farkli bir deger girerse program uyari verir.*/
		}
	}
		
		
	return 0;
}

char letterGrade(int grade)	/*Harf notu degerinin bulundugu fonksiyon.*/
{
	char letter;

		if(grade>=90 && grade<=100)
			letter='A';
		else if(grade>=80 && grade<=89)
			letter='B';	
		else if(grade>=70 && grade<=79)
			letter='C';
		else if(grade>=60 && grade<=69)
			letter='D';	
		else if(grade>=0 && grade<=59)
			letter='F';					

	return letter;
}

void options(void)	/*Kullaniciya gosterilen seceneklerin bulundugu fonksiyon.*/
{
	printf("1)Show most successful student\n");
	printf("2)Show most unsuccessful student\n");
	printf("3)List the number of students for each letter grade\n");
	printf("4)Show calculated average grade\n");
	printf("5)Show all four options data\n\n\n");
}			
		
		
		
		
		
		
		
		
		
		
		
		
