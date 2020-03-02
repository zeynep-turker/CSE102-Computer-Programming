#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef enum {
	M,P,S,B,T,N /*ozel tiplerin disindaki sayilar icin N tipini ekledim.*/
} blockTypes;
	
typedef struct {
char text[10];
int data;
blockTypes type;
int pos_x;
int pos_y;
int jump_x;
int jump_y;
} block;

void initialize(block board[][10]); /*oyun tahtasini tanimlayan fonksiyon*/
void printBoard(block board[][10]);	/*oyun tahtasini ekrana bastiran fonksiyon*/
void intToStr(char str[],int number,int digitNum); /*sayiyi stringe ceviren fonksiyon*/
int reverseNum(int number); /*bir sayinin tersini bulan fonksiyon*/
int findDigit(int number); /*bir sayinin basamak sayisini bulan fonksiyon*/ 
void fillStruct(block *piece,char text[],int p_x,int p_y,int j_x,int j_y,int data,blockTypes type);/*tahtadaki bloklarin ozelliklerinin tanimlandigi fonksiyon*/
int rollDice(); /*random zar atma fonksiyonu*/
void playOneGame(block board[][10],block *piece,int cord_x,int cord_y,int *moveNum,int player);/*tek kisilik oyun*/
void playTwoGame(block board[][10],block *piece,int cord_x,int cord_y);/*iki kisilik oyun*/
int main()
{
	block piece;/*oyuncunun o an bulundugu yerdir.*/
	block board[10][10]; /*block tipinde iki boyutlu bir array tanimladim.*/
	int moveNum;/*tek oyunculu oyunda lazım olmasada parametre olarak moveNum oldugu icin bu degiskeni tanimladim.*/
	
	initialize(board);
	printBoard(board);
	srand(time(NULL));/*zarin rastgele sayi getirmesi icin fonksiyon*/
	piece.pos_x=9; /*oyunucunun bulundugu satir 9 ve sutunda 9 dur.*/
	piece.pos_y=9;
	printf("One Player Game is Beginned\n\n\n");
	playOneGame(board,&piece,9,9,&moveNum,1);
	printf("\n\n\n\nOne Player Game is Finished\n\n\n");
	printf("Two Player Game is Beginned\n\n");	
	playTwoGame(board,&piece,9,9);
	

	return 0;	
}

void playTwoGame(block board[][10],block *piece,int cord_x,int cord_y)
{
	int firstPlayer=0; /*ilk oyuncunun hareket sayisini tutan degisken.*/
	int secondPlayer=0;/*ikinci oyuncunun hareket sayisini tutan degisken.*/
	
	playOneGame(board,piece,cord_x,cord_y,&firstPlayer,1);/*ilk oyuncu icin oyun oynanir.*/
	printf("\n\n\nFirst Player's Game is Finished.\n\n\n");	
	playOneGame(board,piece,cord_x,cord_y,&secondPlayer,2);/*ikinci oyuncu icin oyun oynanir.*/
	printf("\n\n\nSecond Player's Game is Finished.\n\n\n");	
	printf("First Player's numbers of move => %d\nSecond Player's numbers of move => %d\n",firstPlayer,secondPlayer);
	if(firstPlayer < secondPlayer) /*ilk oyuncunun hareket sayisi daha azsa kazanan ilk oyuncu olur.*/
		printf("First Player is Winner!\n");
	else if(firstPlayer > secondPlayer)/*ikinci oyuncunun hareket sayisi daha azsa kazanan ikinci oyuncu olur.*/
		printf("Second Player is Winner!\n");	
	else /*iki oyuncunun hareket sayilari esitse berabere olurlar.*/
		printf("Draw !\n");
}

void playOneGame(block board[][10],block *piece,int cord_x,int cord_y,int *moveNum,int player)
{
	int dice;
	dice=rollDice(); /*her fonksiyona gelindiginde zar dondurulur.*/
	if(cord_x !=0 || cord_y !=9) { /*piece in bulundugu yer 100 degilse*/
		if(cord_x % 2==0) { /*satir cift bir sayiysa ve sutun sayisina zarin geldigi sayi eklendiginde 9dan saha buyuk bir sayi geliyorsa*/
			if(cord_y+dice > 9) { 	/*satir sayisi bir uste cikar yani bir azalir.*/
				cord_x=cord_x-1;
				cord_y=9-(dice-(9-cord_y))+1; /*yeni sutun sayisi yanda kendi bulmus oldugum islemlerle bulunur.*/
			}
			else/*satir cift bir sayiysa ve sutun sayisina zarin geldigi sayi eklendiginde 9dan saha buyuk bir sayi gelmiyorsa*/
				cord_y=cord_y+dice; /*satir sayisi degismez ve yeni sutun sayisida zar ve eski sutun sayisinin toplamiyla bulunur.*/
		}
		else if(cord_x %2 !=0){ /*satir sayisi tek bir sayiysa ve sutun sayisinin zarin geldigi sayiyla cikarmasi 0 dan kucukse*/ 
			if(cord_y-dice < 0) {
				cord_x=cord_x-1; /*satir sayisi bir uste cikar yani bir azalir.*/
				cord_y=dice-cord_y-1; /*yeni sutun sayisi yanda kendi bulmus oldugum islemlerle bulunur.*/
			}
			else/*satir tek bir sayiysa ve sutun sayisinin zar sayisiyla cikarimi 0 dan kücük degilse*/
				cord_y=cord_y-dice;	/*satir sayisi degismez ve yeni sutun sayisida eski sutun sayisinin zar sayisiyla cikarilmasiyla bulunur.*/
		}
		if(cord_x < 0) { /* oyuncunun bulundugu yer 100 u asiyorsa yani cord_x 0 dan kücükse*/
			cord_x=piece->pos_x;	/*oyuncu hareket etmez ve cord_x ve cord_y degiskenleri oyunucunun bulundugu yerdeki konumlarina esit olur.*/
			cord_y=piece->pos_y;
		}	
		else if(board[cord_x][cord_y].type==M) { /* zarin gittigi yer M tipinde bir yerse*/
			piece->pos_x=board[cord_x][cord_y].jump_x; /*oyuncunun yeni koordinatlari M tipinin ozelliginin tasidigi yeni*/
			piece->pos_y=board[cord_x][cord_y].jump_y;/*koordinatlara esit olur.*/
			cord_x=piece->pos_x; /*cord_x ve cord_y degerleri oyuncunun bulundugu yeri gosterdigi icin oyuncunun bulundugu yerin */
			cord_y=piece->pos_y; /*koordinatlarina esit olur.*/
		}	/*ayni sekilde S,P,T,B tipleri icinde M tipinde uygulanan yontem uygulanir.*/
		else if(board[cord_x][cord_y].type==S) {
			piece->pos_x=board[cord_x][cord_y].jump_x;
			piece->pos_y=board[cord_x][cord_y].jump_y;
			cord_x=piece->pos_x;
			cord_y=piece->pos_y;
		}			
		else if(board[cord_x][cord_y].type==P) {
			cord_x=piece->pos_x;
			cord_y=piece->pos_y;
		}	
		else if(board[cord_x][cord_y].type==T) {
			piece->pos_x=board[cord_x][cord_y].jump_x;
			piece->pos_y=board[cord_x][cord_y].jump_y;	
			cord_x=piece->pos_x;
			cord_y=piece->pos_y;
		}	
		else if(board[cord_x][cord_y].type==B) {
			piece->pos_x=board[cord_x][cord_y].jump_x;
			piece->pos_y=board[cord_x][cord_y].jump_y;	
			cord_x=piece->pos_x;
			cord_y=piece->pos_y;
		}
		else {/*oyuncunun bulundugu yer sayi tipindeyse cord_x ve cord_y bu yerin koordinatlarini alir.*/
			piece->pos_x=cord_x;
			piece->pos_y=cord_y;	
		}	
		if(cord_x !=0 || cord_y !=9){ /*oyununcunun bulundugu yer 100 e yani bitis noktasina gelmedigi surece recursive ile*/
			++(*moveNum);				/*tekrardan bu fonksiyona gidilir ve bu esnada her fonksiyona gidiste moveNum degiskeni artirilarak*/
			playOneGame(board,piece,cord_x,cord_y,moveNum,player);/*bir yerde tutulur.*/
		}	
	}
	
	printf("%d.player ===> dice=%d,data=%d\n",player,dice,board[cord_x][cord_y].data);	/*oyununcu bitis noktasina ulastiginda recursive bitirilir ve sondan basa */
																						/*dogru zarin geldigi sayi ve oyuncunun bulundugu yerin datasi print edilir.*/
}	
	
int rollDice()
{
	int dice;
	
	dice=rand()%6+1; /* 1 ve 6 arasinda rastgele sayi uretilir.*/
	
	return dice;
}

void initialize(block board[][10])
{
	int i,j,k=1;/*k degeri baslangictan baslanir 100 e kadar artar ve bloklara sayinin string hali atanir.*/
	int temp;
	int digitNum;
	/*tahtadaki sayilar string e cevrilir ve bu sekilde tanimlanir*/
	for(i=9; i>=0; i--){ /*tahtayi tanimlamaya 9. satir ve 9. sutun dan baslanir.*/
		if(i % 2==0){ /*satirin cift sayi oldugu durumlarda oyuncu sutun artar bir sekilde ilerler*/
			for(j=0; j<=9; j++, k++){
				if(k>9) { /*k degeri 9 dan buyukse sayi ters cevrilir ve sonra stringe cevrilir.*/
					 temp=reverseNum(k);
					 digitNum=findDigit(k);
					 intToStr(board[i][j].text,temp,digitNum);
					 fillStruct(&board[i][j],board[i][j].text,i,j,i,j,k,N);	/*tahtadaki bloklara bloklarin texti,datasi,blogun tipi,bulundugu konumlar ve */
				}															/*blogun ozelligine gore gidecegi konumlar fillStruct fonksiyonuna gonderilerek tanimlanir.*/
				else {
					board[i][j].text[0]=(char)(48+k); /*eger k rakamsa sayi chara cast yapilir ve bu sekilde blok stringine atanir.*/
					board[i][j].text[1]='\0';/*blok stringini bitirmek icin sonuna null konur.*/
					fillStruct(&board[i][j],board[i][j].text,i,j,i,j,k,N);/*tahtadaki bloklara bloklarin texti,datasi,blogun tipi,bulundugu konumlar ve */
				}															/*blogun ozelligine gore gidecegi konumlar fillStruct fonksiyonuna gonderilerek tanimlanir.*/	
			}
		}
		else { /* i tek bir sayiysa oyuncu sutun azalir bir sekilde ilerler.*/ 
			for(j=9; j>=0; j--, k++){ 
				if(k>9) {	/*k degeri 9 dan buyukse sayi ters cevrilir ve sonra stringe cevrilir.*/
					 temp=reverseNum(k);
					 digitNum=findDigit(k);
					 intToStr(board[i][j].text,temp,digitNum);
					 fillStruct(&board[i][j],board[i][j].text,i,j,i,j,k,N); /*tahtadaki bloklara bloklarin texti,datasi,blogun tipi,bulundugu konumlar ve */
				}															/*blogun ozelligine gore gidecegi konumlar fillStruct fonksiyonuna gonderilerek tanimlanir.*/	
				else{
					board[i][j].text[0]=(char)(48+k);/*eger k rakamsa sayi chara cast yapilir ve bu sekilde blok stringine atanir.*/
					board[i][j].text[1]='\0'; /*blok stringini bitirmek icin sonuna null konur.*/
					fillStruct(&board[i][j],board[i][j].text,i,j,i,j,k,N); /*tahtadaki bloklara bloklarin texti,datasi,blogun tipi,bulundugu konumlar ve */
				}														/*blogun ozelligine gore gidecegi konumlar fillStruct fonksiyonuna gonderilerek tanimlanir.*/				
			}							
		}
	}
	/*ozel bloklar icin ayri ayri bloklarin textleri,datalari,tipleri,bulunduklari konumlar */
	fillStruct(&board[1][1],"M{94}",1,1,0,3,89,M);	/*ve blogun ozelligine gore gidecegi yerin konumlari fillStruct fonksiyonuna gonderilir ve bloklar tanimlanir*/
	fillStruct(&board[0][2],"T",0,2,1,2,93,T);
	fillStruct(&board[2][5],"M{83}",2,5,1,7,76,M);
	fillStruct(&board[3][1],"M{77}",3,1,2,6,69,M);
	fillStruct(&board[4][6],"M{77}",4,6,2,6,57,M);
	fillStruct(&board[6][1],"M{52}",6,1,4,1,32,M);
	fillStruct(&board[8][6],"M{28}",8,6,7,2,17,M);
	fillStruct(&board[9][3],"M{11}",9,3,8,0,7,M);
	fillStruct(&board[0][7],"S{72}",0,7,2,1,98,S);
	fillStruct(&board[0][8],"S{56}",0,8,4,5,99,S);
	fillStruct(&board[2][2],"S{68}",2,2,3,2,73,S);
	fillStruct(&board[3][7],"S{52}",3,7,4,1,63,S);
	fillStruct(&board[4][9],"S{44}",4,9,5,6,60,S);
	fillStruct(&board[5][5],"S{22}",5,5,7,8,45,S);
	fillStruct(&board[7][5],"S{12}",7,5,8,1,25,S);
	fillStruct(&board[9][4],"S{1}",9,4,9,9,6,S);
	fillStruct(&board[2][8],"T",2,8,2,3,79,T);
	fillStruct(&board[4][3],"T",4,3,5,1,54,T);
	fillStruct(&board[6][9],"T",6,9,6,4,40,T);
	fillStruct(&board[1][8],"B",1,8,1,3,82,B);
	fillStruct(&board[3][4],"B",3,4,2,0,66,B);
	fillStruct(&board[5][0],"B",5,0,4,4,50,B);
	fillStruct(&board[6][5],"B",6,5,5,9,36,B);
	fillStruct(&board[7][1],"B",7,1,6,3,29,B);
	fillStruct(&board[1][5],"P",1,5,1,5,85,P);				
	fillStruct(&board[5][2],"P",5,2,5,2,48,P);		
	fillStruct(&board[8][2],"P",8,2,8,2,13,P);

}

void printBoard(block board[][10])
{
	int i,j;
	
	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			printf("%9s",board[i][j].text); /* oyun tahtasindaki her bir blok ekrana bastirilir.*/
		}									/*bloklarin her biri ayni buyuklukteki yeri kaplamasi icin 9s yaptim*/
		printf("\n");
	}
	printf("\n\n\n");
}

void fillStruct(block *piece,char text[],int p_x,int p_y,int j_x,int j_y,int data,blockTypes type)
{
	strcpy(piece->text,text); /*fonksiyona gonderilen degerlere gore blogun texti,bulundugu yerler ,*/
	piece->pos_x=p_x;		/*datası , tipi ve tipin ozelligine gore gidecegi yerin konumlari tanimlanir.*/
	piece->pos_y=p_y;
	piece->jump_x=j_x;
	piece->jump_y=j_y;
	piece->data=data;
	piece->type=type;
	
}

void intToStr(char str[],int number,int digitNum)
{
	int i;
	int newDigit;
	
	newDigit=findDigit(number); /*sayinin tersinin basamak sayisi bulunur*/
	/*50 gibi son basamaklari 0 olan sayilarin tersi tek basamak olacagi icin, eger sayinin tersinin son basamagi 0 degilse */
	if(digitNum==newDigit) 
	{
		for(i=0; number != 0; ++i) /*sayinin tersi 0 olmayana kadar 10 ile kalani bulunur ve bu rakama 45 ekler ve char a cast edersek*/
		{							/*sayinin char halini buluruz*/
			str[i]=(char)(48+(number % 10));	/*sayinin char hali str nin i. elemani olur.*/
			number=number / 10;	
		}
		str[i]='\0'; /*string i bitirmek icin sonuna null konur.*/
	}
	else { /* eger sayi 50 60 100 gibi sayilarsa bu sayilarin tersler 5 6 1 gibi rakamlar olur.*/
		str[0]=(char)(48+number); /*ilk olarak rakami chara cast eder ve string in sifirinci indexine atariz*/
		for(i=0; i<digitNum-newDigit; i++) /*daha sonra sayinin kendisinde bulunan sifir kadar sifirin chara casti */
			str[i+1]=(char)(48+0); /*string in sonraki indexlerine atanir.*/
		str[i+1]='\0';	/*string i bitirmek icin sonuna null konulur.*/
	}				
}

int reverseNum(int number)
{
	int newNum=0;
	int temp;
	
	while(number !=0)
	{	
		temp=number%10; /*sayinin 10 ile kalani bulunur*/
		number=number/10;	/*sayi tekrar 10 bolunur*/
		newNum=temp+10*newNum;	/*ters cevirmis sayi temp ile newNum ın 10 ile carpimina esit olur*/
	}	

	return newNum;
}

int findDigit(int number)
{
	int digitNum=1;

	while(number !=0)
	{
		number=number/10; 	/*sayi her ona bolundugunde digitNum degeri artar, bu islem sayi 0 olmayana kadar devam eder*/
		digitNum++;		
	}

	return digitNum;
}

