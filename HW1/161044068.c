#include <stdio.h>
#include <math.h>
#define PI 3.14

double circle_area(double radius);
double calc_hypotenuse(int side1,int side2);
double calc_radius_of_smallest_circle(int side1, int side2);
double calc_radius_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_circle(int side1, int side2);
double calc_area_of_largest_circle(int side1, int side2);
double calc_area_of_smallest_square(int side1, int side2);
double calc_area_of_largest_square(int side1, int side2);
double calc_area_of_square (int side);
void display_results(double largest_circle, double largest_square,
					 double smallest_circle,double smallest_square);

int main(void)
{
	int side1,side2,temp;   /*temp değişkenini uzun kenarın değerinin kısa kenarın değerinden küçük*/
	double largest_circle;	/*olduğu durumlarda değerlerini swap yapmak için kullanıyoruz.*/
	double largest_square;
	double smallest_circle;
	double smallest_square;
	
	
	printf("Enter first side for rectangle:"); /*Dikdörtgenin uzun kenarını kullanıcıdan istiyoruz.*/
	scanf("%d",&side1);
	printf("Enter second side for rectangle:"); /*Dikdörtgenin kısa kenarını kullanıcıdan istiyoruz.*/
	scanf("%d",&side2);
	
	if(side1<side2){   /*Uzun kenarın değeri kısa kenarın değerinden küçükse swap işlemi yapıyoruz.*/ 
		temp=side1;
		side1=side2;
		side2=temp;
	}	

	largest_circle=calc_area_of_largest_circle(side1,side2); 
	largest_square=calc_area_of_largest_square(side1,side2);
	smallest_circle=calc_area_of_smallest_circle(side1,side2);
	smallest_square=calc_area_of_smallest_square(side1,side2);
	
	display_results(largest_circle,largest_square,smallest_circle,smallest_square);
	
	return 0;
}

double circle_area(double radius) /*Dairenin alanını bulduğumuz fonksiyon.*/
{
	double area;
	
	area=PI*pow(radius,2.0);	/*Dairenin alanını bulmak için PIxYarıçapxYarıçap formülünü kullanıyoruz.*/
								/*Yarıçapın karesini bulmak için pow fonksiyonunu kullanıyoruz.*/
	return area;
}
											
double calc_hypotenuse(int side1,int side2) /*Dikdörtgeni çevreleyen en küçük alana sahip olan bir daireninin yarıçapını*/ 
{											/*bulmak için dikdörtgenin hipotenüsünü bulduğumuz fonksiyon.*/
	double hipo;
	
	hipo=sqrt(pow(side1,2.0)+pow(side2,2.0));		  /*Dikdörtgenin hipotenüsünü bulmak için dikdörtgenin uzun ve kısa kenarını pow*/
													  /*fonksiyonu yardımıyla karesini alırız.Karesini aldığımız sonuçları toplar ve*/
													  /*sqrt fonksiyonu ile karekökünü alırız.Elde edilen sonuç bize dikdörtgenin */
	return hipo;									  /*hipotenüsünü verir.*/
	
}

double calc_radius_of_smallest_circle(int side1, int side2) /*Dikdörtgenin çevreleyen en küçük dairenin*/
{															/*yarıçapını hesaplayan fonksiyon.*/
	double radius;
	
	radius=(calc_hypotenuse(side1,side2));                 /*Dairenin yarıçapını bulmak için dikdörtgenin kenarlarını*/
	radius=radius/2;									   /*calc_hypotenuse fonksiyonuna yollarız ve çıkan sonucun yarısını alırız.*/
	
	return radius;
}

double calc_radius_of_largest_circle(int side1, int side2)  /*Dikdörtgenin içine konulan en büyük dairenin*/
{															/*yarıçapını hesaplayan fonksiyon.*/
	double radius;
	
	radius=side2/2.0;  		/*Dikdörtgenin kısakenarı dairenin çapını,*/
							/*kısakenarın yarısı ise dairenin yarıçapını verir.*/

	return radius; 
}

double calc_area_of_smallest_circle(int side1, int side2) /*Dikdörtgeni çevreleyen en küçük dairenin*/
{														  /*alanını hesaplayan fonksiyon.*/
	double radius;
	double area;
	
	radius=calc_radius_of_smallest_circle(side1,side2);  /*Dairenin yarıçapını bulmak için dikdörtgenin kenarlarını*/
	area=circle_area(radius);							 /*calc_radius_of_smallest_circle fonksiyonuna yollarız.*/
	
	return area;
}

double calc_area_of_largest_circle(int side1, int side2) /*Dikdörgenin içine konulan en büyük dairenin*/
{														 /*alanının hesaplayan fonksiyon.*/
	double radius;
	double area;
	
	radius=calc_radius_of_largest_circle(side1,side2);  /*Dairenin yarıçapını bulmak için dikdörtgenin kenarlarını*/
	area=circle_area(radius);							/*calc_radius_of_largest_circle fonksiyonuna yollarız.*/

	return area; 

}

double calc_area_of_smallest_square(int side1, int side2) /*Dikdörtgeni çevreleyen en küçük karenin*/
{														  /*alanını hesaplayan fonnksiyon.*/
	double area;
	
	area=calc_area_of_square(side1);		/*Dikdörtgeni çevreleyen en küçük karenin bir kenarı dikdörtgenin uzun olan kenarıdır*/
											/*bu yüzden bu kenarı calc_area_of_square fonksiyonuna göndeririz ve karenin alanını buluruz.*/
	return area;
}

double calc_area_of_largest_square(int side1, int side2) /*Dikdörtgenin içine konulan en büyük karenin*/
{														/*alanını hesaplayan fonsiyon*/
	double area;
	
	area=calc_area_of_square(side2);		/*Dikdörtgenin içine konulan en büyük karenin bir kenarı dikdörtgenin kısa olan kenarıdır*/
											/*bu yüzden bu kenarı calc_area_of_square fonksiyonuna göndeririz ve karenin alanını buluruz.*/
	return area;
}

double calc_area_of_square(int side) /*Karenin alanını hesaplayan fonksiyon.*/
{
	double area;
	
	area=pow(side,2.0);   /*Bir karenin alanını bulabilmek için bir kenarının karesini alırız*/
						  /*ve bu işlemi pow fonksiyonu yardımıyla yaparız.*/	
	return area;
}

void display_results(double largest_circle,   /*Bütün sonuçlar bu fonksiyonda gösterilir.*/
					 double largest_square,
					 double smallest_circle,
					 double smallest_square) 
{
	/*sayısal değerlerin noktadan sonra 2 basamağını göstermesi için .2f ifadesini kullandım.*/
	printf("The area of the largest circle that fits inside a rectangle:\t\t %.2f\n",largest_circle);
	printf("The area of the largest square that fits inside a rectangle:\t\t %.2f\n",largest_square); 
	printf("The area of the smallest circle that surrounds the same rectangle:\t %.2f\n",smallest_circle);
	printf("The area of the smallest square that surrounds the same rectangle:\t %.2f\n",smallest_square);

}










