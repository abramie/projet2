#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//mode, read, nom fichier


int main(int argc, char *argv[])
{
	char * message;
	char * tableau2;
	int pid_fils;
	int tube[2];
	long taille=0;
	FILE *f;
	
	pipe(tube);
	pid_fils = fork();

	//if(argc >= 2 ) //verifie qu'on a bien le bon nombre d'argument
	{
		if(pid_fils != 0 ) //Pere (Emetteur ) 
		{
			f = fopen(argv[1], "r"); //Ouverture fichier
			if(f!=NULL)
			{
			
				fseek(f,0,SEEK_END);
				taille = ftell(f);
				rewind(f);				//Replacement au debut
				message = (char*)malloc(taille * sizeof(char));
		
				for(int i =0; i< taille; i++)
				{
					message[i] = fgetc(f);		
				}
				
				//while(fgets(message,taille,f)!= NULL);	
				//Gestion envoie pipe
				//Envoie des instructions : taille, valeur paramaetre, tableau
				write(tube[1], &taille, sizeof(taille));
				write(tube [1],argv[2], sizeof(char));
				write(tube[1],message, taille*sizeof(char));
				printf("\nemission: %s", message);
				wait(NULL);
				
				//Fermeture fichier + pipe
				fclose(f);
				close(tube[1]);		
				
			}
		

		}
		else	  			//Fils (recepteur ) 
		{
			char mode;
			f = fopen("reception.txt", "w"); //Ouverture / Creation fichier
			//Receptions des infos
			read(tube[0],&taille,sizeof(taille));
			read(tube[0],&mode, sizeof(char));
			message = (char*)malloc(taille * sizeof(char));
			read(tube[0], message, taille*sizeof(char));
			
			int nbvoyelle;
			printf("\nreception : %s", message);
			switch(mode ) //Opperations sur le message
			{
				case '1':
					tableau2= (char*)malloc(taille * sizeof(char));
					for(int i =0; i< taille; i++)
					{
						tableau2[i] = message[taille-i] ;
						printf("%c", tableau2[i]);
					}
					printf("1");
				break;
				
				case '2':
				
					nbvoyelle = 0;
					for(int i =0; i< taille; i++)
					{
						if(message[i] == 'a' || message[i] == 'e' || 
						message[i] == 'i' || message[i] == 'o' || 
						message[i] == 'u' || message[i] == 'y')
						{
							nbvoyelle ++;			
						}
					}
					tableau2= (char*)malloc((taille-nbvoyelle) * sizeof(char));
					int j = 0;
					for(int i =0; i< taille; i++)
					{
						if(message[i] != 'a' || message[i] != 'e' || 
						message[i] != 'i' || message[i] != 'o' || 
						message[i] != 'u' || message[i] != 'y')
						{
							tableau2[j] = message[i];
							j++;				
						}
					}
					taille = taille-nbvoyelle;
					printf("2");
				break;
			
			}
			
			//Ecriture du message modifié
			/*for(int i =0; i< taille; i++)
			{
				fputs(tableau2,f);
			}*/
			//fputs("salut",f);
			printf("\ntransformation : %s", tableau2);
			fputs(tableau2,f);
			//Fermeture fichier et pipe
			fclose(f);
			close(tube[0]);		
		}
	}

}
