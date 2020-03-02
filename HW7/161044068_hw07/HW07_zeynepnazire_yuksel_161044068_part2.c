#include<stdio.h>
#include<stdlib.h>
#define MYFIRSTDAY 27 /*bu define lar kullanıcının tanımlayacagı pazartesi günüdür.*/
#define MYFIRSTMONTH 4
#define MYFIRSTYEAR 2015
	
void readDate(); 	/*iki tarih arasındaki günleri yazma fonksiyonu.*/
void writeDate();	/*tarihleri (dd/MM/yyyy) formatından (dddd, MMMM dd, yyyy) formatına çeviren fonksiyon*/

int main()
{
	readDate();
	writeDate();

	return 0;
}	

void readDate()
{
	FILE *file;
	int sDay,sMonth,sYear; /*bu değişkenler kullanıcının girdiği ilk tarih değişkenleridir.*/
	int eDay,eMonth,eYear;	/*bu değişkenler kullanıcının girdiği son tarih değişkenleridir.*/
	int i,j,k;
	int cDay,cMonth=12; /*bu değişkenler for döngülerindeki j ve k değerlerinin gittiği son noktalardır.*/
	int flag=1;
	
	file=fopen("input_date.txt","w");	/*input_date.txt dosyasını yazmak için açarız(eğer dosya yoksa oluşacaktır)*/
	if(file == NULL)					/* ve file adlı pointer dosyanın adresi yollanir.*/
   	{									/*eğer dosya açılamadıysa kullanıcıya hata mesajı verip program çıkış yapacaktır.*/
      printf("Open File Error!\n");   
      exit(1);             
   	}
	
	do{
		
		printf("Enter Starting Date..\n");
		scanf("%d%d%d",&sDay,&sMonth,&sYear);
	
		printf("Enter End Date..\n");
		scanf("%d%d%d",&eDay,&eMonth,&eYear);
		/*kullanicinin girdiği tarihlerin sırası pdf de belirtilmediği için kullanıcının girdiği ilk tarih son tarihten daha öncedir.*/
		if(sYear>eYear || (sYear==eYear && sMonth>eMonth) || (sYear==eYear && sMonth==eMonth && sDay>eDay))/*kullanıcı ilk girdiği tarihi ikinci girdiği*/
			printf("Wrong Date Entered!!\nTry Again...\n");/*tarihten daha büyük olarak girerse kullancıya hata mesajı verilir ve kullaniciden tekrar tarih istenir.*/
		else if(sMonth>12 || sMonth<0 || eMonth>12 || eMonth<0)
			printf("Wrong Month Entered!!\nTry Again..\n");	
		else if((sMonth==1 || sMonth==3 || sMonth==5 || sMonth==7 || sMonth==8 || sMonth==10 || sMonth==12) && (sDay>31 || sDay<0))
			printf("Wrong Day Entered!!\nTry Again..\n");
		else if((eMonth==1 || eMonth==3 || eMonth==5 || eMonth==7 || eMonth==8 || eMonth==10 || eMonth==12 ) && (eDay>31 || eDay<0))
			printf("Wrong Day Entered!!\nTry Again..\n");
		else if((sMonth==4 || sMonth==6 || sMonth==9 || sMonth==11) && (sDay>30 || sDay<0))
			printf("Wrong Day Entered!!\nTry Again..\n");	
		else if((eMonth==4 || eMonth==6 || eMonth==9 || eMonth==11) && (eDay>30 || eDay<0))
			printf("Wrong Day Entered!!\nTry Again..\n");	
		else if((sYear%4==0 && sMonth==2 && (sDay<0 || sDay>29)) || (sYear%4 !=0 && sMonth==2 && (sDay<0 || sDay>28)))
			printf("Wrong Day Entered!!\nTry Again..\n");
		else if((eYear%4==0 && eMonth==2 && (eDay<0 || eDay>29)) || (eYear%4==0 && eMonth==2 && (eDay<0 || sDay>28)))
			printf("Wrong Day Entered!!\nTry Again..\n");
		else{
			printf("Your Starting Date : %d/%d/%d\n",sDay,sMonth,sYear);
			printf("Your Ending Date : %d/%d/%d\n",eDay,eMonth,eYear);	
			flag=0;
		}	
	}while(flag==1);

	for(i=sYear;i<=eYear;i++){	/*for döngüsü kullanıcının ilk ve son girdiği yıl kadar döner.*/
		if(i==eYear)	/*eğer yıl kullanıcın girdiği son tarihteki yılsa cMonth kullanıcının girdiği son aya eşitlenir.*/
			cMonth=eMonth;
		for(j=sMonth;j<=cMonth;j++){
			if(j==12)	/*j son aya geldiğinde tekrardan. aya döner.*/ 
				sMonth=1;	
			if(j==1 || j==3 || j==5 || j==7 || j==8 || j==10 || j==12)
				cDay=31;/*1,3,5,7,8,10 ve 12. aydalarda ay 31 gündür.*/
			else if(j==4 || j==6 || j==9 || j==11)
				cDay=30;/*4,6,9 ve 11. aylarda ay 30 gündür.*/
			else if(i %4 == 0 && j==2)
				cDay=29;/*eğer yılın yani i değerinin 4 ile kalanı 0 ise ve ay şubat ayıysa ay 28 gündür.*/
			else if(i %4 != 0 && j==2)
				cDay=28;/*eğer yılın yani i değerinin 4 ile kalanı 0 değilse ve ay şubat ayıysa ay 29 gündür.*/ 
			if(i==eYear && j==eMonth) /*i değişkeni  kullanıcının girdiği son tarihin yılıysa ve ayda o tarihin ayıysa*/
				cDay=eDay;				/*cDay son ayın günü kadar olur.*/
			for(k=sDay;k<=cDay;k++)
			{	
				if(k>0 && k<10 && j>0 && j<10)
					fprintf(file,"0%d/0%d/%d\n",k,j,i); /*ay veya gün tek rakamlıysa başına 0 koyarak 2 haneli yaptım ve*/
				else if(k>0 && k<10 && j>9)				/*tarihi file dosyasına gönderdim.*/
					fprintf(file,"0%d/%d/%d\n",k,j,i);
				else if(k>9 && j>0 && j<10)
					fprintf(file,"%d/0%d/%d\n",k,j,i);	
				else
					fprintf(file,"%d/%d/%d\n",k,j,i);			
			}
			sDay=1;/*her ay sonunda for döngüsündeki k değişkenini tekrar 1 e eşitledim.*/
		}	
	}	
	 
	 
	fclose(file);/*işlem yapılan dosya kapanır.*/

}

void writeDate()
{
	FILE *rfile,*wfile;
	int day,month,year;
	char empty;
	int day7;
	int i,j,k;
	int sYear=MYFIRSTYEAR,sMonth=MYFIRSTMONTH,sDay=MYFIRSTDAY;
	int count=0,cDay,cMonth=12;
	int flag=1;
		
	rfile=fopen("input_date.txt","r");/*input_date.txt dosyası okumak için açılır ve rfile adlı pointera dosyanın adresi yollanır.*/
	if(rfile == NULL)/*dosya açılamadıysa kullanıcıya hata mesajı verilir ve programdan çıkılır.*/
   	{
      printf("Input File Error!\n");   
      exit(1);             
   	}
   	
	wfile=fopen("new_date.txt","w");/*new_date.txt adlı dosyayı dosyasını yazmak için açılır(eğer dosya yoksa oluşacaktır)*/
	if(wfile == NULL)				/*ve wfile adlı pointer a adresini gönderilir.*/
   	{								/*eğer dosya yoksa kullanıcıya hata mesajı verilir ve programdan çıkılır.*/
      printf("New File Error!\n");   
      exit(1);             
   	}
   	
   	while(!feof(rfile)) /*dosyanın sonuna gelinene kadar while nın içerisindeki işlemler yapılır.*/
   	{
   		
   		if(fscanf(rfile,"%d%c%d%c%d%c",&day,&empty,&month,&empty,&year,&empty) != 6)
			return;/*tarihlerdeki 3 integer sayıyı almak için fscanf i kullandım ve tarihler arasındaki / */
					/*operatoru da aldımki sayıları alırken sıra operatora geldiğinde hata vermesin.*/
		if(flag==1) /*bu if e bir kere girilir çünkü haftanın günlerini bulurken kullanıcının ilk girdiği tarihle define ile belirlenmiş*/
		{	/*olunan pazartesi günü arasındaki gün toplamı bulunur ve bu toplam üzerinden işlem yapılır.*/
			if(year==sYear)/*define ile belilrlenmiş olan yılla kullanıcının girmiş olduğu yıl aynı olduğunda haftanın günleri bir fazladan*/
   			count--;   		/*ilerlediği için count değişkenini bir azalttım.*/
	   		for(i=sYear; i<=year; i++){
	   			if(i==year)	/*i değişkeninin kullanıcının girmiş olduğu yıla eşit olduğı zaman ayların sayıldığı*/
	   				cMonth=month;/*for unda cMonth u kullanıcının girmiş olduğu aya eşit olur.*/
	   			if(i != sYear && j==12)
					sMonth=1;	/*i değişkeni define ile belirlenmiş olan yıla eşit değilse ve ay for u 12 ye gelmişse sMonth 1 olur.*/ 
	   			for(j=sMonth; j<=cMonth; j++){/*ayların olduğu for döngüsü*/
	   				if(j==1 || j==3 || j==5 || j==7 || j==8 || j==10 || j==12)
	   					cDay=31;/*1,3,5,7,8,10 ve 12. aylarda cDay 31 e atanır.*/
	   				else if(j==4 || j==6 || j==9 || j==11)
	   					cDay=30;/*4,6,9 ve 11. aylarda cDay 30 a atanır.*/
	   				else if(j==2 && i%4==0)
						cDay=29;/*şubat ayıysa ve i nin yanı yılın 4 ile bölümünden kalan 0 ise cDay 29 a atanır.*/
					else if(j==2 && i%4 !=0)
						cDay=28;/*şubat ayıysa ve i nin yanı yılın 4 ile bölümünden kalan 0 değil ise cDay 28 e atanır.*/
					if(j==month && i==year)
						cDay=day;/*j deki ay kullanıcının girmiş olduğu tarihse ve yılda kullanıcının girdiği yıl ise cDay de*/
	   				for(k=sDay; k<=cDay; k++)/*kullanıcının girmiş olduğu gün olur ve gün for u o güne kadar ilerler.*/
	   					count++; /*istenilen aylar ve o aylardaki günler kadar count değişkeni artar.*/
					sDay=1;/*her ayın bitiminde sDay 1 olur.*/
				}
			}
			flag=0;/*if in bir kez çalıştırılması için flag 0 a eşitlenir.*/	   		
		}
   		day7=count%7;/*count değerinin 7 ile kalanı day7 adlı değişkene eşit olur ve day7 de switch case de kullanılır.*/
   		
   		switch(day7){
   			case 0:	fprintf(wfile,"Monday,");break;/*kalan 0 ise*/
   			case 1:	fprintf(wfile,"Tuesday,");break;/*kalan 1 ise*/
   			case 2:	fprintf(wfile,"Wednesday,");break;/*kalan 2 ise*/
   			case 3:	fprintf(wfile,"Thursday,");break;/*kalan 3 ise*/
   			case 4:	fprintf(wfile,"Friday,");break;/*kalan 4 ise*/
   			case 5:	fprintf(wfile,"Saturday,");break;/*kalan 5 ise*/
   			case 6:	fprintf(wfile,"Sunday,");break;/*kalan 6 ise*/
   			default:printf("Entered Wrong Day\n");
   		}
   			
   		switch(month){/*ayların yazı olarak yazdırılmasını için switch case ile yaptım.*/
   			case 1:	fprintf(wfile,"January");break;
   			case 2:	fprintf(wfile,"February");break;
   			case 3:	fprintf(wfile,"March");break;
   			case 4:	fprintf(wfile,"April");break;
   			case 5:	fprintf(wfile,"May");break;
   			case 6:	fprintf(wfile,"June");break;
   			case 7:	fprintf(wfile,"July");break;
   			case 8:	fprintf(wfile,"August");break;
   			case 9:	fprintf(wfile,"September");break;
   			case 10:fprintf(wfile,"October");break;
   			case 11:fprintf(wfile,"November");break;
   			case 12:fprintf(wfile,"December");break;
   			default:printf("Entered Wrong Month\n");
   		}
   		if(day>0 && day<10)	/*ekrana bastırılırken günü 2 haneli yazmak için 0 ile 10 arasındaki rakamların başına 0 konularak dosyaya gönderdim.*/
   			fprintf(wfile," 0%d,%d\n",day,year);
		else   
			fprintf(wfile," %d,%d\n",day,year);
		count++;/*dosyadaki bir alttaki tarihe geçerken count 1 artırılırki günler ard arda ilerlesin.*/	
		
   	}
	fclose(rfile);/*işlemlerden sonra dosyalar kapanır.*/
	fclose(wfile);



}




