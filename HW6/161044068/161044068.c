#include <stdio.h>
#include <stdlib.h>
void menu();
void reverse_line(char line[], int line_lenght);
int find_size_of_line(char line[]);
void encrypt_open_msg();
void decrypt_secret_msg();

int main(void)
{
	menu();	
	
	return 0;
}

void menu()
{
	int choice;
	
	do{
		printf("1. Encrypt \n2. Decrypt \n0. Exit\n");
		printf("Choice:");
		scanf("%d",&choice);
		
		switch(choice){
		
			case 0 : printf("Good Bye\n"); 	break;
			case 1 : encrypt_open_msg(); 	break;
			case 2 : decrypt_secret_msg();	break;	
			default : printf("Wrong Choice! Please Try Again..\n");
		}
	
	
	}while(choice != 0);	/*Kullanici 0 girmedikce menu gösterilmeye devam eder.*/


}

int find_size_of_line(char line[])
{
	int size=0;
	
	while(line[size] != '\0') /*Stringin indexi null u göstermedikçe i artmaya devam eder ve stringin */
		size++;				/*uzunluğu bulunur.*/
		

	return size;
}

void reverse_line(char line[], int line_lenght)
{
	char temp[100];	/*Stringin tersini tutacak bir string.*/
	int i=0;
	
	
	while(line_lenght > 0)
	{
		temp[i]=line[line_lenght-1];/*temp stringinin 0 dan başlayıp artan her indexi */
		line_lenght--;		/*line stringinin null dan önceki elemanından başlayıp azalan indexlerinin*/
		i++;				/*değerlerine esittir.*/
	}						/*demek istedigim temp[0]i 9 uzunlukta line stringin line[8]ine,*/
	temp[i]='\0';			/*temp[1]=line[7] gibi..*/
	
	for(i=0; temp[i] !='\0'; i++)	/*line stringi kendisinin ters cevrilmis hali olan temp stringine*/
		line[i]=temp[i];			/*esitlenir.*/
	
	line[i]='\0';	/*stringin bitmesi icin sonuna null koydum*/
			
}	

void encrypt_open_msg()
{
	FILE *file,*fileSecret;
	char str[150];
	char encryptedStr[150];
	char wordStr[150];
	int key,i=0,k=0,m,j;
	int tempKey;
	int wordLenght;
	int a=1;
	
	printf("Enter key:");
	scanf("%d",&key);
	tempKey=key;/*Aşağıdaki işlemler sonunda key değişeceği için tempKey tuttum.*/
	
	file=fopen("open_msg.txt","r");/*dosyayı okumak için açtım*/
	if(file == NULL)	/*eğer dosya yoksa kullanıcıya hata mesajı verilir*/
	{
		printf("File Open Error\n");
		exit(1);/*cıkıs için exit(1) fonksiyonunu kullandım.*/
	}
	fileSecret=fopen("secret_msg.txt","w");/*şifrelenmiş stringlerin yazılacağı dosyayı yazma eylemi için açtım.*/
	if(fileSecret == NULL)	/*eğer dosya yoksa kullanıcıya hata mesajı verilir.*/
	{
		printf("FileSecret Open Error\n");
		exit(1);	/*cıkıs için exit(1) fonksiyonunu kullandım.*/
	}
	
	while( ! feof(file) )	/*Dosyanın sonuna gelindiğinde döngüden çıkması için*/
	{
		if (fgets(str,150, file) == NULL){/*bu kısmı son str yi fazladan yaptığı için hatayı*/
			fclose(file);				/*düzeltmek için yaptım.*/
			fclose(fileSecret);
			return;
		}
		for(i=0;str[i] != '\0';++i){/*dosyadaki strlerin sonunda \n varsa null a eşitlenir.*/
			if(str[i] == '\n')
				str[i] = '\0';
		}		
		fprintf(stdout,"%s\n",str);	/* open_msg.txt dosyasındaki şifrelenecek her bir string */
		i=0;k=0;					/*ekrana bastırılır.*/
		while(str[i] != '\0')
		{
			for(j=0; str[i] !=' ' && str[i] !='\0'; j++,i++)/*stringi kelime kelime ters cevirip şifreleyeceğimiz*/
				wordStr[j]=str[i];						/*için stringte bosluk ya da null görene kadar kelime alınır.*/ 
			
			wordStr[j]='\0';	/*her kelime wordStr adlı arraye yazılır ve sonuna null koyulur.*/

			wordLenght=find_size_of_line(wordStr);		/*her kelimenin uzunluğu bulunur ve ters çevrilmesi için*/		 
			reverse_line(wordStr,wordLenght); 		/*reverse_line fonksiyonuna wordStr stringi yollanır.*/
			if(str[i] == ' ')	/*eğer wordStr e str nin bosluğa kadar gelmiş olduğu bir stringse*/
			{					/*wordStr nin j. indexi bosluk lur ve j+1. indexi null olarak kelime öyle şifrelenir.*/ 
				wordStr[j]=' ';
				wordStr[j+1]='\0';
				++i;	/*str stringinin indexi bir artıralarak kıyaslamaya öyle devam edilir.*/
				wordLenght=find_size_of_line(wordStr);/*wordStr nin bosluk eklenmis halinin uzunluğu alınır.*/ 
			}	
			j=0;	/*wordStr nin ilk elemanından başlayarak şifrelenmesi için j yi 0 a eşitleriz.*/
			while(wordLenght > 0){	/*wordStr nin uzunluğu kadar char şifrelenir.*/	
				if(wordStr[j] == ' ')	/*eğer char bosluksa,bosluğun yerine '_' işareti konulur.*/ 
					encryptedStr[k]='_';
					
				else if(wordStr[j] == '.'){ /*eğer char noktaysa ve kelimenin sonundaki nokta kelime*/
					if(j ==0 || j ==1){		/*ters cevrildiğinde kelimenin basına geççegi için j 0 ya da 1 ken*/
						a=0;				/*noktanın yerine * konulmaz ve sona konulması için a 0 a eşitlenir.*/
						k--;				/*aşagıda a nın 0 olması durumunu açıklayacağım*/
						/*şifrelenecek string arrayine j nin  0 ya da 1 olması durumunda * konulmayacağı için*/
						/*k 1 azaltılır.*/
					}	
					else	
						encryptedStr[k]='*';/*j 0 ve 1 den farklıysa nokta yerime * konulur.*/
						
				}		
				else if(wordStr[j]-key<123 && wordStr[j]-key > 96 &&  wordStr[j]<123 && wordStr[j] > 96)
					encryptedStr[k]=wordStr[j]-key;	/*eğer wordStr deki bir kelimenin key den çıkarılmış hali*/
						/*alfabenin küçük harflerinin arasındaysa encryptedStr[k] wordStrdeki harfin key den çıkarılmış*/
						/*haline eşittir.*/
				
				else if(wordStr[j]-key < 97 && wordStr[j]<123 && wordStr[j] > 96)
				{								/*eğer wordStr deki harfin keyden çıkarılmış alfabenin küçük harflerinin arasında değilse*/
					while(wordStr[j] != 'a')	/*wordStr deki harf a harfine gelinceye kadar 1 er 1 er azaltılır.*/
					{							/*aynı anda key de azaltılırki kalan key kadar daha wordStr deki harf ilerlesin.*/
						key--;
						wordStr[j]--;
					}
					wordStr[j]=wordStr[j]+25;	/*a ya gelen harfe 25 eklenerek z harfine gelinir ve key de bir ilerlemiş*/
					for(m=0; m<key-1; m++)		/*olduğu için for döngüsündeki m key-1 e kadar döner.*/
						wordStr[j]--;			/*for döngüsü wordStr nin kalan key kadar daha azalması içindir.*/
					encryptedStr[k]=wordStr[j];	/*for döngüsü sonunda şifrelenmiş string arayinin k. indexi wordStr nin k.*/
				}								/*indexine eşit olur.*/
				else 
					k--; /* Bir harf veya bosluk veya nokta degil ise o karakteri atlayip yazmamasi icin k yi azaltiyorum.*/
				key=tempKey; /*wordStr deki her harf için key değişceği için keyi tekrar kullanıcının girdiği key değerine eşitliyorum*/
				k++;
				j++;	
				wordLenght--;
				
			}
			if(a==0){	/*eğer a 0 ise k nokta olur ve * olarak şifrelenir.k nın bir artırılmasıyla da şifrelenmiş string*/
				encryptedStr[k++]='*';	/*arrayinin k+1 . indexi de null a eşit olur.*/
				encryptedStr[k]='\0';
			}
			else
				encryptedStr[k]='\0';
			a=1;	/*wordStr nin nokta işareti her kelime için kontrol edileceği için a yı tekrar 1 e eşitledim.*/
		}
		fprintf(fileSecret,"%s\n",encryptedStr); /*şifrelenmiş strin arrayi fileSecret dosyasına yazdırılır.*/
		fprintf(stdout,"EncryptedStr ==> %s\n",encryptedStr);	 /*şifrelenmiş string arrayi terminal ekranına bastırılır.*/		
	}
	fclose (file);/*işlemler sonunda dosyalar kapatılır.*/
	fclose (fileSecret);
}

void decrypt_secret_msg()
{
	FILE *file,*fileOpen;
	char str[150],wordStr[150];
	char decryptedStr[150];
	int wordLenght;
	int key,i=0,j,k=0,m;
	int tempKey;
	int a=1;
	
	printf("Enter key:");
	scanf("%d",&key);
	tempKey=key;/*Aşağıdaki işlemler sonunda key değişeceği için tempKey tuttum.*/

	file =fopen("secret_msg.txt","r");/*dosyayı okumak için açtım*/
	if(file == NULL)	/*eğer dosya yoksa kullanıcıya hata mesajı verilir.*/
	{
		printf("File Open Error\n");
		exit(1);
	}
	
	fileOpen =fopen("open_msg.txt","w");/*dosyayı yazılma işlemi için açtım.*/
	if(fileOpen == NULL)/*eğer dosya yoksa kullanıcıya hata mesajı verilir.*/
	{
		printf("FileOpen Open Error\n");
		exit(1);
	}
	
	while( ! feof(file) )
	{
		if (fgets(str,150, file) == NULL){/*bu kısmı son str yi fazladan yaptığı için hatayı*/
			fclose(file);		/*düzeltmek için yaptım.*/
			fclose(fileOpen);
			return;
		}
		for(i=0;str[i] != '\0';++i){/*dosyadaki strlerin sonunda \n varsa null a eşitlenir.*/
			if(str[i] == '\n')
				str[i] = '\0';
		}		
		fprintf(stdout,"%s\n",str ); /*şifresi çözülecek stringler dosyadan ekrana bastırılır.*/ 
		i=0;k=0;
		while(str[i] != '\0') 
		{
			for(j=0; str[i] !='_' && str[i] !='\0'; j++,i++)/*string i kelime kelime ters cevirip şifresini*/ 
				wordStr[j]=str[i];		/*çözeceğimiz için strig de _ veya null görene kadar kelime alınır.*/
			
			wordStr[j]='\0';	/*her kelime wordStr adlı arraye yazılır ve sonuna null koyulur.*/

			wordLenght=find_size_of_line(wordStr);/*wordStr nin uzunluğu bulunur,wordStr deki kelime ters çevrilmesi */		 
			reverse_line(wordStr,wordLenght); /*için reverse_line fonksiyonuna  wordStr ve onun uzunlugu gönderilir.*/
			if(str[i] == '_')	/*eğer wordStr e str nin '_' e kadar gelmiş olduğu bir stringse*/
						/*wordStr nin j. indexi '_'lur ve j+1. indexi null olarak kelime öyle şifrelenir.*/ 		
			{
				wordStr[j]='_';
				wordStr[j+1]='\0';
				++i;				/*str stringinin indexi bir artıralarak kıyaslamaya öyle devam edilir.*/
				wordLenght=find_size_of_line(wordStr);/*wordStr nin '_' eklenmis halinin uzunluğu alınır.*/ 

			}	
			j=0;	/*wordStr nin ilk elemanından başlayarak şifrelenmesi için j yi 0 a eşitleriz.*/
			while(wordLenght > 0){	
				if(wordStr[j] == '_')
					decryptedStr[k]=' ';
				else if(wordStr[j] == '*'){ /*eğer char '_' sa ve kelimenin sonundaki '_' kelime*/
					if(j==0 || j==1){		/*ters cevrildiğinde kelimenin basına geççegi için j 0 ya da 1 ken*/
						a=0;				/*noktanın yerine * konulmaz ve sona konulması için a 0 a eşitlenir.*/
						k--;				/*aşagıda a nın 0 olması durumunu açıklayacağım*/		
					}						/*şifrelenecek string arrayine j nin  0 ya da 1 olması durumunda nokta konulmayacağı için*/
					else					/*k 1 azaltılır.*/
						decryptedStr[k]='.';						
				}		
				else if(wordStr[j]+key<123 && wordStr[j]+key > 96 &&  wordStr[j]<123 && wordStr[j] > 96)
						decryptedStr[k]=wordStr[j]+key;	/*wordStr deki harfe keyi eklendiğimizde  123 den küçük*/
					/* ve 96 dan büyükse wordStr ye key eklenmiş hali decryptedStr[k] e atanır.*/
				else if(wordStr[j]+key>122 && wordStr[j]<123 && wordStr[j] > 96)
				{/*wordStr deki harfe keyi eklendiğimizde 122 den büyükse wordStr deki harf z harfine gelen kadar 1 artırılır..*/
					while(wordStr[j] != 'z')
					{
						key--;	/*aynı zamanda key de 1 er 1 er azaltılırki wordStr a olduktan sonra key kadar daha artsın.*/
						wordStr[j]++;
					}
					wordStr[j]=wordStr[j]-25; /*wordStr deki harf z den a olabilmesi için harften 25 çıkarılır.*/
					for(m=0; m<key-1; m++)  /*a harfine gelen harf key -1 e kadar daha for döngüsüyle döndürülür ve */
						wordStr[j]++;		/*her seferinde 1 artar.*/	
					decryptedStr[k]=wordStr[j];	
				}
				else 
					k--; /* Bir harf veya bosluk veya nokta degil ise o karakteri atlayip yazmamasi icin k yi azaltiyorum.*/
				key=tempKey; /*her harf için key eski değeriyle kullanılacağı için key tekrar kullanıcının girdiği değere eşitlenir.*/
				k++;
				j++;	
				wordLenght--;
				
			}
			if(a==0){/*eğer a 0 ise k * olur ve nokta olarak şifrelenir.k nın bir artırılmasıyla da şifrelenmiş string*/
				decryptedStr[k++]='.';	/*arrayinin k+1 . indexi de null a eşit olur.*/
				decryptedStr[k]='\0';
				
			}
			else
				decryptedStr[k]='\0';
			a=1; /*her kelime için * için karşılaştılacağı için a tekrar 1 e eşitlenir.*/
		}
		/*şifresi çözülmüş strin arrayi fileOpen dosyasına yazdırılır.*/
		fprintf(fileOpen,"%s\n",decryptedStr); /*şifresi çözülmüş stringler fileOpen dosyasına yazdırılır.*/
		fprintf(stdout,"DecryptedStr ==> %s\n",decryptedStr); /*şifrelenmiş string arrayi terminal ekranına bastırılır.*/	
						
	}
	fclose (file); /*işlemler sonunda dosyalar kapatılır.*/
	fclose (fileOpen);
}
