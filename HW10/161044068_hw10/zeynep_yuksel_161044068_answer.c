#include <stdio.h>
#include <stdlib.h>/*mallloc kullanımı için*/
#include <time.h> /*clock fonkiyonu için time.h kütüphanesini kullandım*/
#include <math.h>/*sqrt kullanımı için*/

typedef struct linkedList{ /*linked list in her node nun structı,data node un sahip olduğu asal sayıyı,next de node un gösterdiği bir sonra node ya da null*/
	long int data;
	struct linkedList *next;
}node;
	
void primeDynamicArray(FILE *outputFile,long int finalNum,int digit);
void primeLinkedList(FILE *outputFile,long int finalNum,int digit);
int findPrime(long int number);
int readLine(FILE *file,long int *number);

int main()
{
	FILE *outputFile;
	FILE *linkedOutput;
	clock_t sTime,fTime;
	
	remove("output_prime_dynamic_array.txt");/*dosyayı a mmodunda açtığım için programı her çalıştırdığımda çıktılar üst üste gelmesin diye remove ile olan başlangıçta dosya varsa silinip tekrar oluşturulur.*/
	remove("output_prime_LiknedList.txt");
	/*clock fonksiyonu ile zaman hesaplanır : fonksiyona gitmeden ve gittikten sonraki zamanlar birbirinden çıkarılır ve time.h kütüphanesinin sabiti olan CLOCKS_PER_SEC a bölünür.clock fonksiyonu zamanı saniye cinsinden return ettiği için çıkan zaman sonucu 1000 ile çarpılarak milisaniye cinsine dönüştürülür.*/
	/* TIME CALCULATOR FOR DYNAMIC ARRAY*/
	outputFile=fopen("output_prime_dynamic_array.txt","a");
	
	sTime=clock();	
	primeDynamicArray(outputFile,1000000,1);
	fTime=clock();
	fprintf(outputFile,"\n********TIME CALCULATOR RESULTS FOR DYNAMIC ARRAY********\n\n");
	fprintf(stdout,"\n********TIME CALCULATOR RESULTS FOR DYNAMIC ARRAY********\n\n");	
	fprintf(outputFile,"Time for 1.000.000(with writing prime number into file) ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 1.000.000(with writing prime number into file) ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	
	sTime=clock();	
	primeDynamicArray(outputFile,1000000,0);
	fTime=clock();
	fprintf(outputFile,"Time for 1.000.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 1.000.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));

	sTime=clock();
	primeDynamicArray(outputFile,750000,0);
	fTime=clock();
	fprintf(outputFile,"Time for 750.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 750.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
			
	sTime=clock();	
	primeDynamicArray(outputFile,500000,0);
	fTime=clock();
	fprintf(outputFile,"Time for 500.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 500.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));	
	fclose(outputFile);/*yazdırılma işlemi bittikten sonra dosya kapanır.*/
	
	/*TIME CALCULATOR FOR LINKED LIST*/
	linkedOutput=fopen("output_prime_LiknedList.txt","a");
	
	sTime=clock();	
	primeLinkedList(linkedOutput,1000000,1);
	fTime=clock();
	fprintf(linkedOutput,"\n********TIME CALCULATOR RESULTS LINKED LIST********\n\n");	
	fprintf(stdout,"\n********TIME CALCULATOR RESULTS FOR LINKED LIST********\n\n");			
	fprintf(linkedOutput,"Time for 1.000.000(with writing prime number into file) ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 1.000.000(with writing prime number into file) ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
		
	sTime=clock();	
	primeLinkedList(linkedOutput,1000000,0);
	fTime=clock();
	fprintf(linkedOutput,"Time for 1.000.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 1.000.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	
	sTime=clock();	
	primeLinkedList(linkedOutput,750000,0);
	fTime=clock();
	fprintf(linkedOutput,"Time for 750.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 750.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	
	sTime=clock();
	primeLinkedList(linkedOutput,500000,0);
	fTime=clock();
	fprintf(linkedOutput,"Time for 500.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fprintf(stdout,"Time for 500.000 ==> %f miliseconds\n",1000*((double)(fTime-sTime)/CLOCKS_PER_SEC));
	fclose(linkedOutput);/*yazdırılma işlemi bittikten sonra dosya kapanır.*/
	
	return 0;
}
void primeLinkedList(FILE *outputFile,long int finalNum,int digit)
{
	FILE *linkFile=fopen("data.txt","r"); /*data txt dosyası okuma modunda açılır.*/
	node *startNode = NULL; /*linked listin en başını ifade eder.*/
	node *tmpNode;  /*asal sayıların bastırılması ve nodeların free edilmesinde yardımcı olan pointer*/
	node *addedNode; /*linked liste sonradan eklenecek node u ifade eder.*/
	node *lastNode; /*son node u gösteren pointer*/
	long int number;

	if(linkFile == NULL)
	{
		printf("Open Error LinkFile!\n");
		exit(1);
	}
	readLine(linkFile,&number); /*while döngüsüne girilebilmesi için dosyadan bir tane long int sayısı alınır.*/
	while(number <= finalNum) /*parametre olarak girilen sayıya kadar dosyadan sayı alınır.*/
	{
		if(findPrime(number) == 1) /*alınan sayı asal oldugunda*/
		{
			addedNode=(node*)malloc(sizeof(node));/*sayının eklenebilmesi için bir tane node için bellekten yer ayırtılır.*/
			addedNode->data=number;/*node un datası asal olan sayıdır.*/
			addedNode->next=NULL; /*node linked listin en sonunda olacağı için next i NULL olur.*/
			if(startNode == NULL){/*eğer linked listte hiç node yoksa dosyadan alınan sayı ile ilk node oluşturulur.*/
				startNode=addedNode;
				lastNode=startNode;
			}	
			else {/*eğer eklenecek sayının önünde başka node lar var ise son node u ifade eden lastNode değişkeni artık yeni eklenecek olan sayının node unu gösterir.*/
				lastNode->next=addedNode;
				lastNode=addedNode;				
			}
		}
		if(readLine(linkFile,&number) !=3)/*Dosyanın sonundaki EOF un alınmaması için eğer dosyadan alınan bir satırda 3 tane eleman yoksa (yani %ld %c %d) number sayısı 10 artırılarak finalNum dan daha büyük olur ve döngüden çıkar.*/
			number=number+10;
	}
	if(digit == 1) {
		tmpNode=startNode;/*tmpNode linked listin en başını gösterir.*/
		while(tmpNode != NULL) {/*tmpNode Null u göstermedikçe asal sayılar bastırılır.*/
			fprintf(outputFile,"%ld,00\n",tmpNode->data);
			tmpNode=tmpNode->next;
		}	
	}
	while(startNode !=NULL) {/*burada nodelar free edilir.*/
		tmpNode=startNode;
		startNode=startNode->next;
		free(tmpNode);
	}
}

void primeDynamicArray(FILE *outputFile,long int finalNum,int digit)
{
	long int number;
	long int *arr; /*ana arrayim*/
	long int *dynArr; /*ek olarak tuttuğum array*/
	long int memorySize=10;
	long int used=0;
	int i;
	FILE *file=fopen("data.txt","r");/*data txt dosyasını okuma modunda açtım.*/
	arr=(long int*)malloc(memorySize * sizeof(long int));/*arraye kendi belirlediğim yer kadar bellekte yer ayırttım.*/
	
	if(file == NULL)
	{
		printf("File Open Error\n");
		exit(1);
	}
	readLine(file,&number);	/*while döngüsüne girebilmek için dosyadan bir tane long int number alınır.*/				
	while(number <= finalNum)/*finalNum dosyadan alınan son sayıdır.*/
	{
		if(used+1 == memorySize)/*Eğer kullanılan arrayin (yani usedin) bir fazlası array için bellekten ayırtılmış yere denk geliyorsa  bellek boyutu iki katına çıkarılır ve  ek olarak tanımladığım array için  bu bellek boyutu kadar yer  alınır.Daha sonra ana arrayimin elemanlarını tutması için elemanları ikinci arraye atanır.Bellekte yer kaplamaması için ana arrayim için aldığım ilk yeri free ile belleğe geri veririm.Son olarak da ana arrayimin yerini ikinci olarak eklediğim arrayin yeri olarak gösteririm.*/
		{
			memorySize=memorySize*2;
			dynArr=(long int*)malloc(memorySize * sizeof(long int));
			for(i=0; i<used; i++)
				dynArr[i]=arr[i];
			free(arr);
			arr=dynArr;
		}
		if(findPrime(number) == 1)/*Dosyadan alınan sayı asalsa arrayin used indexine atılır ve used bir artırılır.*/
		{
			arr[used]=number;
			used++;
		}
		if(readLine(file,&number) != 3)/*Dosyanın sonundaki EOF un alınmaması için eğer dosyadan alınan bir satırda 3 tane eleman yoksa (yani %ld %c %d) number sayısı 10 artırılarak finalNum dan daha büyük olur ve döngüden çıkar.*/
			number=number+10;
	}
	fclose(file);/*işlemler bittiğinde data.txt dosyası kapatılır.*/
	if(digit==1) {
		for(i=0; i<used; i++)
			fprintf(outputFile,"%ld,00\n",arr[i]);
	}		
	free(arr);
}

int readLine(FILE *file,long int *number)
{	
	char space;	/*space virgüllerin alınması için olan bir değişkendir.*/
	int buf;	/*buf ise 0 virgülden sonraki 0 ları alan bir değişkendir.*/
	int num; /*num,fonksiyonun return degeridir.Dosyadan alınan bir satırdaki alınan elemanların sayısını ifade eder.*/

	num=fscanf(file,"%ld%c%d",number,&space,&buf);		
	
	return num;
}
 
int findPrime(long int number)
{
	int i;	
	int sqrtNum;
	sqrtNum=(int)sqrt(number);
	
	if(number == 1) /*Bir sayı asalsa 2 ve onun kare köküne kadar olan aralıkta böleni yoktur fakat sayı asal değilse bu aralıkta en az bir böleni vardır.*/
		return 0;	
	for(i=2; i<=sqrtNum; i++)
	{
		if(number % i == 0)
			return 0; /*sayı asalsa 1 , asal değilse 0 return edilir.*/
	}
	return 1;
}
