#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
char **Map;
int Width;
int Height;
int Flower_X;
int Flower_Y;
}Forest;

typedef struct {
int Coord_X; /* koordinat duzleminde x sutun ile y ise satir ile gosterilir.*/
int Coord_Y;
int Water_Bottle_Size;
}Botanist;

void init_game(Forest *forest,Botanist *botanist);
void print_map(Forest forest);
void search(Forest *forest,Botanist *botanist,int water);

int main()
{
	int i;
	Forest forest;
	Botanist botanist;
	
	srand(time(NULL));
	
	init_game(&forest,&botanist);
	print_map(forest);
	printf("Searching..\n\n");
	search(&forest,&botanist,botanist.Water_Bottle_Size);
	
  	for(i=0; i<(forest.Height); i++) /*malloc ile yer ayirdigim iki boyutlu arrayi bellege geri iade etmek icin free fonksiyonunu kullandim.*/
 	  	free(forest.Map[i]);
  	free(forest.Map);  			
	
	
	return 0;
}

void init_game(Forest *forest,Botanist *botanist)
{
	FILE *file = fopen("init.csv", "r"); /*init.csv dosyasını okumak icin actim ve asagidaki if de  dosyanin olup olmadigini kontrol ettim.*/
	char space;	/*init.csv deki virgul gibi gereksiz karakterleri atlamak icin bu degiskeni kullaniyorum.*/
	int i,j,m=0;
	char *str;	/*bu string arrayi dosyadaki oyunun her satirini okuyup iki boyutlu forest->Map arrayine atamak icin*/
	int temp;
	if(file == NULL)
	{
		printf("File Open Error\n");
		exit(1);
	}
	else {
		fscanf(file,"%d",&(botanist->Water_Bottle_Size)); /*dosyaki ilk sayiyi Water_Bottle_Size degiskenine atadim.*/
		fscanf(file,"%d%c",&(forest->Height),&space);	 /*dosyaki ikinci sayiyi Height degiskenine atadim.virgulleride space degiskenini atadim*/
		fscanf(file,"%d",&(forest->Width));  /*dosyaki ucuncu sayiyi Width degiskenine atadim.*/
		
	    forest->Map = (char **)malloc((forest->Height) * sizeof(char *)); /*dosyadan okunan height width degerleine gore malloc ile bellekte yer ayirtiriz.*/
	    for(i=0; i<(forest->Height); i++)
	    	forest->Map[i] = (char *)malloc((forest->Width) * sizeof(char));
		
		temp=(forest->Width)*2+10;
		str=(char *)malloc(temp * sizeof(char)); /*oyun tahtasinin her satirinde hem # karakteri hemde virgüller olucagi icin*/
		    								/*forest->Width in 2 katinın 10 fazlasi kadar yer ayirdim.(10 \n ve null icin)*/
		fgets(str,temp,file);	 /*dosyadan tek bir satir alarak bunu bir stringe atariz ve boylelikle forest->Map in ici doldurulur.*/
		
		i=0;
		while(fgets(str,temp,file) != NULL) { /*oyun tahtasindaki her satir icin string alinir ta ki dosya bitene kadar*/
			for(j=0; j<(forest->Width); j++,m++) {
				if(str[m] != ','){
					forest->Map[i][j]=str[m]; /*string in virgul disindaki elemanlari Map i doldurur.*/
					if(forest->Map[i][j]=='F') { /*F in oldugu koordinatlar belirlenir.*/
						forest->Flower_X=j;
						forest->Flower_Y=i;
					}	
					else if(forest->Map[i][j]=='B') { /*B nin oldugu koordinatlar belirlenir.*/
						botanist->Coord_X=j;
						botanist->Coord_Y=i;
					}	
				}
				else 
					--j;/*str[m] virgul oldugunda j azalir*/
			}
			i++;
			m=0;	/*string arayi icin m 0 a tekrar esitlenir.*/
			
		}
	}
	fclose(file);/*islemler bitince dosya kapanir.*/
	free(str); /*bellekten alinan str nin yeri geri verilir.*/
}

void print_map(Forest forest)
{
	int i,j;
	
	for(i=0; i<(forest.Height); i++){	/*satirlarin sonunda bosluk olmadigindan 9. sutun da karakterin yaninda bosluk olmaz.*/
		for(j=0; j<(forest.Width); j++){	
			if(j != (forest.Width)-1)
				printf("%c ",forest.Map[i][j]);
			else
				printf("%c",forest.Map[i][j]);
		}		
		printf("\n");
	}	
	printf("\n");
}

void search(Forest *forest,Botanist *botanist,int water)
{
	int step;
	
	if(water == 0){ /*botanistin suyu bitince oyun tahtasi tekrar gosterilir ve botonistin koordinatlari gosterilir sonrada return ile cikilir*/
		print_map(*forest); 
		printf("Help! I am on (%d,%d)\n",botanist->Coord_X,botanist->Coord_Y);
		return ;
	}	
	step=rand()%4+1; /*botonistin rastgele gitmesi icin 1 ve 4 arasinda sayi bulunur.*/ 
	/*1 botonistin asagiya , 2 yukari, 3 saga ve 4 ise sola gitmesi demektir.*/
	if(step == 1 && botanist->Coord_Y<9 && forest->Map[botanist->Coord_Y+1][botanist->Coord_X] ==' ') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' '; /*botinistin asagisi bos ise botanist bir asagiya gecer ve eski yeri bos olur.*/
		forest->Map[++(botanist->Coord_Y)][botanist->Coord_X]='B';
		water--;/*bir birim hareket ettigi icin botanistin suyu bir azalir.*/
	}
	else if(step ==1 && botanist->Coord_Y<9 && forest->Map[botanist->Coord_Y+1][botanist->Coord_X] =='F') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' '; /*botanistin asagisinda F varsa B oraya gecer ve haritada kaybolur.*/
		print_map(*forest);	/*oyun tahtasi yeni haliyle gosterilir ve cicegin koordinatlari ekrana basilir sonrada return ile cikilir.*/
		printf("I have found it on (%d,%d)!\n",forest->Flower_X,forest->Flower_Y);
		return ;
	}		
	else if(step == 2 && botanist->Coord_Y>0 && forest->Map[botanist->Coord_Y-1][botanist->Coord_X] ==' ') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' '; /*botanistin yukarisi bos ise botanist bir yukariya gecer ve eski yeri bos olur.*/
		forest->Map[--(botanist->Coord_Y)][botanist->Coord_X]='B';
		water--;
	}
	else if(step == 2 && botanist->Coord_Y>0 && forest->Map[botanist->Coord_Y-1][botanist->Coord_X] =='F') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' ';	/*botanistin yukarisinda F varsa B oraya gecer ve haritada kaybolur.*/
		print_map(*forest);	
		printf("I have found it on (%d,%d)!\n",forest->Flower_X,forest->Flower_Y);
		return ;
	}	
	else if(step == 3 && botanist->Coord_X <9 && forest->Map[botanist->Coord_Y][botanist->Coord_X+1]==' ') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' '; /*botanistin sagi bos ise botanist bir saga gecer ve eski yeri bos olur.*/
		forest->Map[botanist->Coord_Y][++(botanist->Coord_X)]='B';
		water--;
	}
	else if(step == 3 && botanist->Coord_X <9 && forest->Map[botanist->Coord_Y][botanist->Coord_X+1]=='F') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' ';	/*botanistin saginda F varsa B oraya gecer ve haritada kaybolur.*/
		print_map(*forest);
		printf("I have found it on (%d,%d)!\n",forest->Flower_X,forest->Flower_Y);
		return ;
	}	
	else if	(step == 4  && botanist->Coord_X>0 && forest->Map[botanist->Coord_Y][botanist->Coord_X-1]==' ') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' '; /*botansitin solu bos ise botanist bir sola gecer ve eski yeri kaybolur.*/
		forest->Map[botanist->Coord_Y][--(botanist->Coord_X)]='B';
		water--;
	}
	else if(step == 4  && botanist->Coord_X>0 && forest->Map[botanist->Coord_Y][botanist->Coord_X-1]=='F') {
		forest->Map[botanist->Coord_Y][botanist->Coord_X]=' '; /*botanistin solunda F varsa B oraya gecer ve haritada kaybolur.*/
		print_map(*forest);	
		printf("I have found it on (%d,%d)!\n",forest->Flower_X,forest->Flower_Y);
		return ;
	}	
	search(forest,botanist,water);	/*ayni islemler botanist F yi buluncaya veya suyu bitene kadar devam eder.*/
}	
