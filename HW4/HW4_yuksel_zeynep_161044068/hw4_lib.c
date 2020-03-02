/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018
**
** Revision: 2018.03.27.08.19
** 
*/
#include <stdio.h>
#include "hw4_lib.h"
#include <math.h>

double integral(double f(double x), double xs, double xe, double delta)
{
	double area=0.0;	/*Alanlari toplaya toplaya islem yapilacagi icin alani 0.0'a esitledim.*/
	double i;
	
	for(i=xs; i<xe; i=i+delta)		/*Fonksiyonun baslangic noktasindan bitis noktasina kadar olan alanini buluruz.*/
		area = area + f(i) * delta;	/*Bu alanlari fonksiyonu deltayla carparsak elde ederiz.*/
		
	
    return area;
}

double integral2(double f(double x, double y), double xs, double xe, double ys, double ye, double delta)
{
	double volume=0.0;	/*Cift katli bir integral aslinda bir hacimdir*/
	double i,j;			/*Hacimi toplaya toplaya islem yapilacagi icin 0.0'a esitledim.*/
	
	for(i=xs; i<xe; i=i+delta)	/*Ic ice for dongunde her x degiskenini sabit tutarak degisen y degerleriyle fonksiyona gondererek */
	{							/*bu degeri hem x icin hem de y icin deltayla carptim yani delta*delta oldu.*/
		for(j=ys; j<ye; j=j+delta)
			volume=volume+f(i,j)*delta*delta;	/*Burdaki mantik sabit tutulmuş bir alani x ve y nin artis miktarinin karesiyle*/
	}											/*carparak hacmi bulmak*/
	
	return volume;			/*Hocam bu fonksiyonu WolframAlpha sayfasinda 2D integral testleri ile test ettim*/
}							/*ve deltaya baglı olarak cok yaklasik degerler buldum.*/

int derivatives(double f(double a), double x, double eps, double * d1, double * d2)
{

	if(eps != 0.0)	/*Fonksiyon eps degiskeni 0.0 oldugunda -1 dondurur.*/
	{	
		*d1 = (f(x+eps)-f(x-eps))/(2.0*eps);
		*d2 = (f(x+eps)-(2.0*f(x))+f(x-eps))/(eps*eps);
	}
	else 
		return -1;
		
}

int compare_derivatives(double f(double a), double d1(double b), double d2(double b), double x, double eps, double *e1, double *e2)
{
	double myd1,myd2;	/*Bu degiskenlere benim yazdigim derivatives fonksiyonumda degerler atanir.*/
	
	derivatives(f,x,eps,&myd1,&myd2);	
	
	if(d1(x) > myd1)		/*Bu bolum hata payinin negatif bir deger cikmamasi icin*/
		*e1=d1(x)-myd1; 
	else
		*e1=myd1-d1(x);
	
	if(d2(x) > myd2)	 
		*e2=d2(x)-myd2;
	else
		*e2=myd2-d2(x);
	
	return 0;
}
	
int find_roots(double f(double x), double * x1, double * x2, double * x3, double * x4)
{
	double arr[4];		/*Kok degerlerini tutacak 4 elemanli bir array tanimladim.*/
	double i;
	int k=0,m;
	
	for(m=0;m<4;m++)	/*Ilk basta arrayin elemanlarini 0.0 a atadim.*/
		arr[m]=0.0;		/*Cunku kok olmayan degerlerin sifir olarak kalmasi icin boyle yaptim.*/
		
	for(i=-200.0; i<=200.0; i=i+0.01)			/*Buyuk bir aralikta kokleri bulmaya calıstim.*/
	{											/*Virgullu koklerin bulunması icin i degerini daha kucuk sekilde artirdim.*/
		if(f(i) > -0.1 && f(i) < 0.1 && k<4)	/*Koklerin bulunmasinin daha verimli olmasi icin 0 ya yakin olan bir aralik belirledim.*/
		{										/*Arraye sadece 4 tane atama yapilabilmesi icin k degerini 4 e kadar yaptım.*/
			arr[k]=i; 	/*Fonksiyonu 0 yapan degerler arrayin k indexli elemani olur.*/
			k++;		/*Fonksiyon her kok buldugunde arrayin indexi bir artar.*/
		}
	}	

	*x1=arr[0];		/*1. koku arrayin 1. elemanina ,*/
	*x2=arr[1];		/*2. koku arrayin 2. elemanina ,*/
	*x3=arr[2];		/*3. koku arrayin 3. elemanina ,*/
	*x4=arr[3];		/*4. koku arrayin 4. elemanina atanir.*/ 
		
	return 0;	
	
}
