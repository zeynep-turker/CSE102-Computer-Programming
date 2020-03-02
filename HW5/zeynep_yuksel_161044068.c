#include <stdio.h>
#define BOARDSIZE 8

typedef enum {white_man, black_man, white_king, black_king, empty} piece;
typedef enum {white = 10, black = 20} player;

void init_board(piece board[][8]);
int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p);
int check_end_of_game(piece board[][8]);
void display_board(piece board[][8]);
/*Ayrı olarak yazdığım fonksiyon*/
void play_game(piece board[][8]); /*Oyunun oynanıldığı fonksiyon*/
void repeat_move(piece board[][8],int from_x,int from_y,player p); /*Ard arda yeme fonksiyonu*/
int isKingMovable(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p); 	/*King taslarının oynama fonksiyonu*/ 
int isManMovable(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p);	/*Man taslarının oynama fonksiyonu*/
void isKing(piece board[][8],int to_x,int to_y,player p); /*Man taslarının king olup olmadıklarını kontrol eden fonksiyon*/

int main(void)
{
	piece dama[BOARDSIZE][BOARDSIZE];

	init_board(dama);	/*Oyun tahtası tanımlanır.*/
	play_game(dama);	/*Oyuma baslanır.*/
	
	return 0;
}

void init_board(piece board[][8])
{
	int i;
	
	for(i=0;i<BOARDSIZE;i++)	/*Oyun tahtasındaki parcaları tanımladım.*/
	{
		board[0][i]=empty;
		board[1][i]=black_man;
		board[2][i]=black_man;
		board[3][i]=empty;
		board[4][i]=empty;
		board[5][i]=white_man;
		board[6][i]=white_man;
		board[7][i]=empty;		
	}
}

void display_board(piece board[][8])	/*Oyun tahtasındaki parcaların isaretlerinin gosterildigi fonksiyon.*/
{
	int i,j;
	
	for(i=0;i<BOARDSIZE;i++)
	{
		for(j=0;j<BOARDSIZE;j++)
		{
			if(board[i][j] == empty)
				printf("-");
			else if(board[i][j] == white_man)
				printf("w");
			else if(board[i][j] == black_man)
				printf("b");
			else if(board[i][j] == white_king)
				printf("W");
			else if(board[i][j] == black_king)
				printf("B");
		}
		printf("\n");
	}
}

int check_end_of_game(piece board[][8])
{
	int i,j;
	int numWhite=0,numBlack=0;
	player winner;
	
	for(i=0; i<BOARDSIZE; i++)
	{
		for(j=0; j<BOARDSIZE; j++)
		{
			if(board[i][j] == white_man || board[i][j] == white_king)
				numWhite++;
			else if(board[i][j] == black_man || board[i][j] == black_king)
				numBlack++;
		}		
	}
	if(numWhite > 0 && numBlack == 0)	/*Tahtada beyaz tas var ve de siyah tas yoksa beyaz olan takım yenmistir.*/
		winner=white;
	else if(numBlack > 0 && numWhite == 0)	/*Tahtada siyah tas var ve de beyaz tas yoksa siyah olan takım yenmistir.*/
		winner=black;
	else
		return -1;
		
	return winner;		
	
}

void play_game(piece board[][8])
{
	
	int from_x,from_y;
	int to_x,to_y;
	int temp;
	
	player p=white;
	
	
	display_board(board);
	
	do{
		scanf("%d%d",&from_x,&from_y);
		scanf("%d%d",&to_x,&to_y);
		
		temp=move(board,from_x,from_y,to_x,to_y,p);
		
		while(temp == -2 || temp == -1){ /*eğer move fonksiyonu -2 veya -1 return ederse kullanıcı uyarılır ve tekrar oynaması istenilir.*/
			printf("Wrong Move Try Again\n");
			display_board(board);		
			scanf("%d%d",&from_x,&from_y);
			scanf("%d%d",&to_x,&to_y);
			temp=move(board,from_x,from_y,to_x,to_y,p);
		}	
			
		display_board(board);		
		
		if(p == white)
			p=black;
		else 
			p=white;	
	}	
	while(check_end_of_game(board) == -1);
	
	if(check_end_of_game(board) == white) 	/*eger oyun tahtasında sadece beyaz taslar kalırsa beyaz takım,*/
		printf("WINNER IS WHITE!");			/*tahtada sadece siyah taslar varsa siyah takım kazanır.*/
	else
		printf("WINNER IS BLACK!");

}

int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p)
{
	int temp;
	
	if(board[from_x][from_y]==white_man || board[from_x][from_y]==black_man)	
		temp=isManMovable(board,from_x,from_y,to_x,to_y,p); 	/*siyah ya da  beyaz tasların man i oynarsa isManMovable fonksiyonu is gorur.*/
	else if(board[from_x][from_y]==white_king || board[from_x][from_y]==black_king)
		temp=isKingMovable(board,from_x,from_y,to_x,to_y,p);	/*siyah ya da  beyaz tasların king i oynarsa isKingMovable fonksiyonu is gorur.*/
	else 
		return -2;	/*Hic biri değilse -2 return edilir.*/

	return temp;

}

void repeat_move(piece board[][8], int from_x,int from_y,player p)
{
	int flag=1;
	
	do{
		if(p == white)
		{
			if(board[from_x][from_y+1]==black_man || board[from_x][from_y+1]==black_king) /*Eğer beyaz man tasının sagında siyah tas varsa*/
			{
				from_y=from_y+2;		/*Beyaz man siyah tası yer ve onun bir sagına gecer.*/
				board[from_x][from_y]=empty;	/*Beyaz tasın eski yeri bos olur.*/
				board[from_x][from_y+2]=white_man; /*Yeni yerinde kendisi olur.*/
				board[from_x][from_y+1]=empty;	/*Yenilen siyah tasın yeri bos olur.*/
			}
			else if(board[from_x][from_y-1]==black_man ||board[from_x][from_y-1]==black_king) /*Eğer beyaz man tasının solunda siyah tas varsa*/
			{
				from_y=from_y-2;		/*Beyaz man siyah tası yer ve onun bir soluna gecer.*/
				board[from_x][from_y]=empty;	/*Beyaz tasın eski yeri bos olur.*/
				board[from_x][from_y-2]=white_man; /*Yeni yerinde kendisi olur.*/
				board[from_x][from_y-1]=empty;	/*Yenilen siyah tasın yeri bos olur.*/
			}
			else if(board[from_x-1][from_y]==black_man || board[from_x-1][from_y]==black_king) /*Eğer beyaz tasın bir onunde siyah tas varsa*/
			{
				from_x=from_x-2;	/*Beyaz man siyah tası yer ve onun bir onune gecer.*/
				board[from_x][from_y]=empty;	/*Beyaz tasın eski yeri bos olur.*/
				board[from_x-2][from_y]=white_man;	 /*Yeni yerinde kendisi olur.*/
				board[from_x-1][from_y]=empty;		/*Yenilen siyah tasın yeri bos olur.*/
			}
			else 
				flag=0;	/*Eğer yukarıdaki if lerin hicbiri yoksa flag 0 olur ve donguden cıkar.*/
		}
				
		else
		{
			if(board[from_x][from_y+1]==white_man || board[from_x +1][from_y]==white_king) /*Eger siyah tasın bir sagında beyaz tas varsa*/
			{
				from_y=from_y+2;	/*Siyah tas beyaz tasın bir sagına gecer.*/
				board[from_x][from_y]=empty;	/*Siyah tasın eski yeri bos olur.*/
				board[from_x][from_y+2]=black_man;	/*Yeni yerinde kendisi olur.*/
				board[from_x][from_y+1]=empty; /*Yenilen beyaz tasın yeri bos olur.*/
			}
			else if(board[from_x][from_y-1]==white_man || board[from_x][from_y-1]==white_king)
			{
				from_y=from_y-2;		/*Siyah tas beyaz tasın bir soluna gecer.*/
				board[from_x][from_y]=empty;	/*Siyah tasın eski yeri bos olur.*/
				board[from_x][from_y-2]=black_man;	/*Yeni yerinde kendisi olur.*/
				board[from_x][from_y-1]=empty;	 /*Yenilen beyaz tasın yeri bos olur.*/
			}
			else if(board[from_x+1][from_y]==white_man || board[from_x+1][from_y]==white_king)
			{
				from_x=from_x+2;		/*Siyah tas beyaz tasın bir soluna gecer.*/
				board[from_x][from_y]=empty;	/*Siyah tasın eski yeri bos olur.*/
				board[from_x+2][from_y]=black_man;	/*Yeni yerinde kendisi olur.*/
				board[from_x+1][from_y]=empty;	/*Yenilen beyaz tasın yeri bos olur.*/
			}
			else
				flag=0;	/*Eğer yukarıdaki if lerin hicbiri yoksa flag 0 olur ve donguden cıkar.*/
		}		
	}
	while(flag==1);

}

int isKingMovable(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p)
{
	if(p==white)
	{
		
		if(board[to_x-1][to_y]==black_man || board[to_x-1][to_y]==black_king)	/*Eğer white king in solunda siyah man veya siyah king varsa*/
		{
			board[from_x][from_y]=empty;	/*white king in eski yeri bos olur.*/
			board[to_x][to_y]=white_king;	
			board[to_x-1][to_y]=empty;	/*white king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);	/*tekrar beyaz tasın siyah tas yiyip yiyemeyecegi kontrol edilir.*/
		}	
		else if(board[to_x+1][to_y]==black_man || board[to_x+1][to_y]==black_king)	/*Eğer white king in sagında siyah man veya siyah king varsa*/
		{
			board[from_x][from_y]=empty;	/*white king in eski yeri bos olur.*/
			board[to_x][to_y]=white_king;
			board[to_x+1][to_y]=empty;	/*white king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);	/*tekrar beyaz tasın siyah tas yiyip yiyemeyecegi kontrol edilir.*/
		}
		else if(board[to_x][to_y-1]==black_man || board[to_x][to_y-1]==black_king)		/*Eğer white king in arkasında siyah man veya siyah king varsa*/
		{
			board[from_x][from_y]=empty;	/*white king in eski yeri bos olur.*/
			board[to_x][to_y]=white_king;
			board[to_x][to_y-1]=empty;	/*white king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);		/*tekrar beyaz tasın siyah tas yiyip yiyemeyecegi kontrol edilir.*/
		}
		else if(board[to_x][to_y+1]==black_man || board[to_x][to_y+1]==black_king)	 /*Eğer white king in onunde siyah man veya siyah king varsa*/
		{
			board[from_x][from_y]=empty;	/*white king in eski yeri bos olur.*/
			board[to_x][to_y]=white_king;	
			board[to_x][to_y+1]=empty;	/*white king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);	/*tekrar beyaz tasın siyah tas yiyip yiyemeyecegi kontrol edilir.*/
		}
		else if(board[from_x][from_y]==black_man || board[from_x][from_y]==black_king)
				return -1;	/*Eger kullanıcı siyah tası oynadıysa -1 return edilir.*/
		else
			return -2;	/*Yukarıdakilerden hicbiri degilse -2 return edilir.*/
						
	}
	else if(p==black)
	{
		if(board[to_x-1][to_y]==white_man || board[to_x-1][to_y]==white_king)	/*Eger black king in arkasında white taslarınsa biri varsa*/
		{
			board[from_x][from_y]=empty;	/*black king in eski yeri bos olur.*/
			board[to_x][to_y]=black_king;
			board[to_x-1][to_y]=empty;		/*black king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);	/*tekrar siyah tasın beyaz tas yiyip yiyemeyecegi kontrol edilir.*/
		}	
		else if(board[to_x+1][to_y]==white_man || board[to_x+1][to_y]==white_king)	/*Eger black king in onunde white taslarınsa biri varsa*/
		{
			board[from_x][from_y]=empty;	/*black king in eski yeri bos olur.*/
			board[to_x][to_y]=black_king;
			board[to_x+1][to_y]=empty;	/*black king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);	/*tekrar siyah tasın beyaz tas yiyip yiyemeyecegi kontrol edilir.*/
		}
		else if(board[to_x][to_y-1]==white_man || board[to_x][to_y-1]==white_king)	/*Eger black king in solunda white taslarınsa biri varsa*/	
		{
			board[from_x][from_y]=empty;	/*black king in eski yeri bos olur.*/
			board[to_x][to_y]=black_king;
			board[to_x][to_y-1]=empty;	/*black king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);	/*tekrar siyah tasın beyaz tas yiyip yiyemeyecegi kontrol edilir.*/
		}
		else if(board[to_x][to_y+1]==white_man || board[to_x][to_y+1]==white_king)	/*Eger black king in sagında white taslarınsa biri varsa*/	
		{
			board[from_x][from_y]=empty;	/*black king in eski yeri bos olur.*/
			board[to_x][to_y]=black_king;
			board[to_x][to_y+1]=empty;		/*black king in yedigi tasın yeri bos olur.*/
			repeat_move(board,to_x,to_y,p);	/*tekrar siyah tasın beyaz tas yiyip yiyemeyecegi kontrol edilir.*/
		}
		else if(board[from_x][from_y]==white_man || board[from_x][from_y]==white_king) /*Eger kullanıcı beyaz tası oynadıysa -1 return edilir.*/
				return -1;
		else
			return -2;			/*Yukarıdakilerden hicbiri degilse -2 return edilir.*/		
	}
	return 0;	
				
}

int isManMovable(piece board[][8],int from_x,int from_y,int to_x,int to_y,player p)
{
	
	if(p == white)
	{
		if(to_x-from_x == -2 && to_y == from_y && (board[(from_x+to_x)/2][from_y] == black_king 
			|| board[(from_x+to_x)/2][from_y] == black_man))	/*White man 2 öne gitmek istiyorsa ve de */
		{														/*gitmek istediği yer ile durdugu yer arasında siyah tas varsa*/
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			isKing(board,to_x,to_y,p);  /*white man in yeni yerinde king olup olmadıgı kontrol edilir.*/
			board[(from_x+to_x)/2][from_y] = empty; /*yedigi tasın yeri bos olur.*/
			
			if((board[from_x][from_y+1]==black_man || board[from_x][from_y+1]==black_king)
				&& (board[from_x][from_y-1]==black_man ||board[from_x][from_y-1]==black_king)
				&& (board[from_x-1][from_y]==black_man || board[from_x-1][from_y]==black_king))

				repeat_move(board,to_x,to_y,p);	/*Eger if in icindekiler saglanırsa tekrar tas yenilip yenilmeyecegi kontrol edilir.*/
		}
		else if(to_x == from_x && (to_y - from_y == 2 || to_y - from_y == -2) 
				&& (board[from_x][(to_y+from_y)/2] == black_king || board[from_x][(to_y+from_y)/2] == black_man))
		{		/*White man 2 saga gitmek istiyorsa ve de gitmek istediği yer ile durdugu yer arasında siyah tas varsa*/
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			isKing(board,to_x,to_y,p);	/*white man in yeni yerinde king olup olmadıgı kontrol edilir.*/
			board[from_x][(to_y+from_y)/2] = empty; /*yedigi tasın yeri bos olur.*/
			
			
			if((board[from_x][from_y+1]==black_man || board[from_x][from_y+1]==black_king)
				&& (board[from_x][from_y-1]==black_man ||board[from_x][from_y-1]==black_king)
				&& (board[from_x-1][from_y]==black_man || board[from_x-1][from_y]==black_king))

			repeat_move(board,to_x,to_y,p);	/*Eger if in icindekiler saglanırsa tekrar tas yenilip yenilmeyecegi kontrol edilir.*/
		}
		else if(to_x-from_x == -1 && to_y == from_y && board[to_x][to_y] == empty) /*Eger beyaz tas önüne giderse ve orası bossa*/
		{		
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			isKing(board,to_x,to_y,p);	/*white man in yeni yerinde king olup olmadıgı kontrol edilir.*/
		}	
		else if(to_x == from_x && (to_y - from_y == 1 || to_y - from_y == -1) && board[from_x][from_y]==empty) /*Eğer beyaz tas sagına ve ya soluna gitmek isterse*/
		{																										/*ve orası bossa*/
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			isKing(board,to_x,to_y,p);	/*white man in yeni yerinde king olup olmadıgı kontrol edilir.*/
		}	
		else if(board[from_x][from_y]==black_man || board[from_x][from_y]==black_king)
				return -1;  /*Eger kullanıcı siyah tası oynadıysa -1 return edilir.*/
		else
			return -2;	/*Yukarıdakilerden hicbiri degilse -2 return edilir.*/	
						
	}
	else if(p == black)
	{
		if(to_x-from_x == 2 && to_y == from_y && (board[(from_x+to_x)/2][from_y] == white_king 
			|| board[(from_x+to_x)/2][from_y] == white_man))
		{
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			board[(from_x+to_x)/2][from_y] = empty;
			isKing(board,to_x,to_y,p); /*black man in yeni yerinde king olup olmadıgı kontrol edilir.*/
		
			if((board[from_x][from_y+1]==white_man || board[from_x +1][from_y]==white_king)
				&& (board[from_x][from_y-1]==white_man || board[from_x][from_y-1]==white_king)
				&& (board[from_x+1][from_y]==white_man || board[from_x+1][from_y]==white_king))
				
				repeat_move(board,to_x,to_y,p);	/*Eger if in icindekiler saglanırsa tekrar tas yenilip yenilmeyecegi kontrol edilir.*/
		}
		else if(to_x == from_x && (to_y-from_y == 2 || to_y-from_y == -2) && 
				(board[from_x][(to_y+from_y)/2] == white_king || board[from_x][(to_y+from_y)/2] == white_man))
		{
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			board[from_x][(to_y+from_y)/2] = empty; /*yedigi tasın yeri bos olur.*/
			isKing(board,to_x,to_y,p);	/*black man in yeni yerinde king olup olmadıgı kontrol edilir.*/
			
			if((board[from_x][from_y+1]==white_man || board[from_x +1][from_y]==white_king)
				&& (board[from_x][from_y-1]==white_man || board[from_x][from_y-1]==white_king)
				&& (board[from_x+1][from_y]==white_man || board[from_x+1][from_y]==white_king))
				
				repeat_move(board,to_x,to_y,p);	/*Eger if in icindekiler saglanırsa tekrar tas yenilip yenilmeyecegi kontrol edilir.*/
		}
		else if(to_x-from_x == 1 && to_y == from_y) /*siyah tas 1 onune gitmek isterse*/
		{
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			isKing(board,to_x,to_y,p);	/*black man in yeni yerinde king olup olmadıgı kontrol edilir.*/
		}	
		else if(to_x == from_x && (to_y - from_y == 1 || to_y - from_y == -1)) /*siyah tas sagına ve ya soluna 1 adım gitmek isterse*/
		{
			board[from_x][from_y]=empty; /*Tasın ayrıldığı yer bos olur.*/
			isKing(board,to_x,to_y,p); /*black man in yeni yerinde king olup olmadıgı kontrol edilir.*/
		}
		else if(board[from_x][from_y]==white_man || board[from_x][from_y]==white_king)
				return -1;	 /*Eger kullanıcı beyaz tası oynadıysa -1 return edilir.*/
		else 
			return -2;	/*Yukarıdakilerden hicbiri degilse -2 return edilir.*/	
	}
	return 0;
}

void isKing(piece board[][8],int to_x,int to_y,player p)
{
	if(p == white)
	{
		if(board[to_x][to_y]==board[0][0] || board[to_x][to_y]==board[0][1] || board[to_x][to_y]==board[0][2]
				|| board[to_x][to_y]==board[0][3] || board[to_x][to_y]==board[0][4] || board[to_x][to_y]==board[0][5]
				|| board[to_x][to_y]==board[0][6] || board[to_x][to_y]==board[0][7])
				board[to_x][to_y]=white_king;	/*Siyah takımın en ustunde bulunan yerlere beyaz tas geldiginde beyaz tas king olur.*/
		else	
			board[to_x][to_y]=white_man;
	}
	else if(p == black)
	{
		if(board[to_x][to_y]==board[7][0] || board[to_x][to_y]==board[7][1] || board[to_x][to_y]==board[7][2]
				|| board[to_x][to_y]==board[7][3] || board[to_x][to_y]==board[7][4] || board[to_x][to_y]==board[7][5]
				|| board[to_x][to_y]==board[7][6] || board[to_x][to_y]==board[7][7])
				board[to_x][to_y]=black_king;	/*Beyaz takımın en ustunde bulunan yerlere siyah tas geldiginde siyah tas king olur.*/
		else	
			board[to_x][to_y]=black_man;
	}	

}
