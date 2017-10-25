#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>




int main(int argc, char *argv[])
{
long taille;
//if(sizeof(argv[1]) == sizeof(int)); 

	FILE *f = fopen("test.txt", "r"); //Ouverture fichier
			if(f!=NULL)
			{
			
				fseek(f,0,SEEK_END);
				taille = ftell(f);
				rewind(f);				//Replacement au debut
				printf("%i", taille);
		
			}
	
	


}
