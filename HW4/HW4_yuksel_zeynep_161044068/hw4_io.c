/*
** hw4_io.c:
**
** The source file implementing input and output functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/

#include <stdio.h>
#include "hw4_io.h"



int read_polynomial3(double * a0, double * a1, double * a2, double * a3)
{									/*3.derecedeki sayıyı a3,2.yi a2 1.yi a1 ve sabit sayıyı a0 ifade eder.*/	
	int flag=0;
	
	do{								/*Kullanici a3 sayisini 0 girmezse flag değişkeni 1 e atanir,*/
									/*diger degiskenlerde kullanicidan istenir ve do while dongusunden cikilir.*/
		printf("Enter four numbers: ");
		scanf("%lf",a3);
		
		if(*a3 != 0.0)
			flag=1;
		else
			printf("Please try again.\n");
			
		if(flag == 1)	
			scanf("%lf %lf %lf",a2,a1,a0);
		
	}		
	while(flag==0);
	
	return 0;
}

int read_polynomial4(double * a0, double * a1, double * a2, double * a3, double * a4)
{										/*4.derecedeki sayıyı a4,3.yü a3,2.yi a2 1.yi a1 ve sabit sayıyı a0 ifade eder.*/							
	int flag=0;
	
	do{									/*Kullanici a4 sayisini 0 girmezse flag değişkeni 1 e atanir,*/
										/*diger degiskenlerde kullanicidan istenir ve do while dongusunden cikilir.*/
		printf("Enter five numbers:");	
		scanf("%lf",a4);
		
		if(*a4 != 0.0)
			flag=1;
		else	
			printf("Please try again.\n");
		
		if(flag == 1)
			scanf("%lf %lf %lf %lf",a3,a2,a1,a0);
		
		
	}		
	while(flag==0);
	
	return 0;
	
}

void write_polynomial3(double a0, double a1, double a2, double a3)
{
	if(a3 != 0.0)					/*Sayilar 0 olmazsa print edilir.Sayilardan sonra gelen sayi pozitif bir sayiysa */
	{								/*(+) isareti konulur.Sayi negatifse bisiy konmaz sayinin  kendi isareti yazilir.*/
		if(a3 == 1.0)				/*Double sayilarin noktadan sonra bir rakam yazilmasi icin .1f koydum.*/
			printf("x^3");			/*Her polinomun katsayi degiskeninin 1 veya -1 olma durumunda print edilirken*/
		else if(a3 == -1.0)			/*ekrana sadece katsayinin isareti ve x degeri gosterilir 1 degeri gosterilmez.*/
			printf("-x^3");	
		else						
			printf("%.1fx^3",a3);	
			
		if(a2 > 0)
			printf("+");			/*Eger bir sonraki desigken pozitifse araya + isareti konulur.*/
	}
			
	if(a2 != 0.0)
	{
		if(a2 == 1.0)
			printf("x^2");
		else if(a2 == -1.0)
			printf("-x^2");	
		else		
			printf("%.1fx^2",a2);
		
		if(a1 > 0)
			printf("+");
	}
			
	if(a1 != 0.0)
	{
		if(a1 == 1.0)
			printf("x");
		else if(a1 == -1.0)
			printf("-x");	
		else		
			printf("%.1fx",a1);
		
		if(a0 > 0)
			printf("+");
	}
			
	if(a0 != 0.0)
		printf("%.1f",a0);	

	printf("\n");
}			

void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
	if(a4 != 0.0)				/*Sayilar 0 olmazsa print edilir.Sayilardan sonra gelen sayi pozitif bir sayiysa */
	{							/*(+) isareti konulur.Sayi negatifse bisiy konmaz sayinin  kendi isareti yazilir.*/
		if(a4 == 1.0)			/*Double sayilarin noktadan sonra bir rakam yazilmasi icin .1f koydum.*/
			printf("x^4");
		else if(a4 == -1.0)
			printf("-x^4");	
		else						
			printf("%.1fx^4",a4);	
		
		if(a3 > 0)
			printf("+");
	}		
	
	if(a3 != 0.0)
	{
		if(a3 == 1.0)
			printf("x^3");
		else if(a3 == -1.0)
			printf("-x^3");	
		else		
			printf("%.1fx^3",a3);
	
		if(a2 > 0)
			printf("+");
	}
			
	if(a2 != 0.0)
	{
		if(a2 == 1.0)
			printf("x^2");
		else if(a2 == -1.0)
			printf("-x^2");	
		else		
			printf("%.1fx^2",a2);
		
		if(a1 > 0)
			printf("+");
	}
			
	if(a1 != 0.0)
	{
		if(a1 == 1.0)
			printf("x");
		else if(a1 == -1.0)
			printf("-x");	
		else		
			printf("%.1fx",a1);
		
		if(a0 > 0)
			printf("+");
	}
			
	if(a0 != 0.0)
		printf("%.1f",a0);	

	printf("\n");
}
