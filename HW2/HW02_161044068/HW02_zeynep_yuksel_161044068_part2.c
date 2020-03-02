#include <stdio.h>
void results(int number);	/*Her bir basamak icin basamak degerlerinin ekrana yazdirildigi fonksiyon.*/
int numofdigit(int number);	/*Sayinin basamak sayinin bulundugu fonksiyon.*/
int valueofDigit(int ndigit,int number); /*Sayinin her bir basamagi icin basamak degerinin bulundugu fonksiyon.*/

int main()
{
	int num;
	int flag=0;	/*Do while dongusunun donmesi icin flag degiskenini 0'a atadım.*/
	
	do{
		printf("Enter the number: ");
		scanf("%d",&num);
		printf("\n\n");
		
		if(num>=23 && num<=98760)	/*Kullanici 23 ve 98760 sayilari arasindan bir sayi girene kadar bu dongu devam eder.*/
		{
			results(num);			/*Kullanici bu aralik arasindan bir sayi girdiginde results adli fonksiyona gidilir ve islemler yapilir.*/
			flag=1;					/*Ayni zamanda flag degiskeni 1 degerine esit olur ve do while dongusunden cikilir.*/
		}	
		else
		{
			printf("You entered a wrong number.Please enter again.\n\n");	/*Kullanici 23 ile 98760 sayilari arasinda bir deger girmediginde*/
			flag=0;														/*program uyari verir ve dongu devam eder.*/	
		}	
	}
	while(flag==0);
		
	return 0;
}

void results(int number)
{
	int ndigit;	/*Girilen sayinin basamak sayisi icin ndigit adli degiskeni atadim.*/
	int i;
	
	ndigit=numofdigit(number);	/*Sayinin basamak degerinin bulunmasi icin numofdigit adli fonksiyona sayi yollanir.*/

	for(i=ndigit;i>0;i--)											/*Sayinin basamak degerlerini ekrana basarken son basamagindan baslamasi icin for dongusunu*/
		printf("The %d. digit is %d\n",i,valueofDigit(i,number));	/*sayinin basamak sayisinden baslatıp 1 oldugunda	sonlandırdım.*/
																	/*Her basamak degerini bulmasi icin valueofDigit adli fonksiyona sayinin istenilen*/
																	/*basamak sayisini ve sayi gonderilir.*/
}

int valueofDigit(int numDigit,int number)	/*Sayinin kacinci basamaginin degeri isteniliyorsa onu bulan bir fonksiyon*/
{
	int temp,i;

	for(i=1;i<numDigit;i++)		
	{							/*Bir sayinin n. basamak degeri bulunmak isteniyorsa sayi n-1 kere 10'a bolunur ve cikan degerin 10 ile kalani bulunur.*/
		number=number/10;
	}
	temp=number%10;
	
	return temp;	
}

int numofdigit(int number)	/*Gonderilen sayinin kac basamakli oldugunu bulan bir fonksiyondur.*/
{
	int numdigit=0;	/*Sayinin basamak sayisi icin bu degiskeni atadim.*/
	
	while(number != 0)	/*Bu while dongusu sayi degerinin 0 olmadigi surece devam eder.*/
	{
		number=number/10;	/*Sayi her 10'a bolundugunde bir basamak sayisi bir azalir  ve ayni zamanda ndigit degiskeni bir artirilir.*/
		numdigit++;			/*Boylelikle sayinin degeri sifir olmayana kadar basamak degeri bulunmus olur.*/
	}
	
	return numdigit;
}		
