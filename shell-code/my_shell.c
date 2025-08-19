#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64

int handler = 0;

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}
void sigint_handler(int sig) {
	// kill(id,sig);
	handler=1;
}

int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	// int i;

	int bg[64];
	int f[64];
	for(int i=0;i<64;i++)
	{
		f[i]=0;
	}
	while(1) {			
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		signal(SIGINT,sigint_handler);
		scanf("%[^\n]", line);
		getchar();

		// printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
   
       //do whatever you want with the commands, here we just print them
		int size=0;
		for(int i=0;tokens[i]!=NULL;i++){
			// printf("found token %s (remove this debug output later)\n", tokens[i]);
			size++;
		}

		for(int i=0;i<64;i++)
			{
				if(f[i] == 1)
				{
					if(waitpid(bg[i],NULL,WNOHANG) >0)
					{
						printf("Background Process Finished\n");
						f[i]=0;
					}
				}
			}

		if(tokens[0]==NULL)
		{
			continue;
		}
		if(strcmp(tokens[0],"exit")==0)
		{	
			for(int i=0;i<64;i++)
			{
				if(f[i]==1)
				// {	printf("%d",bg[i]);
					{
					kill(bg[i],SIGKILL);
					// for(int j=0;tokens[j]!=NULL;i++){
					// 	free(tokens[j]);
					// }
					// free(tokens);
				}
			}
			break;
		}

		int c=0;
		for(int i=0;tokens[i]!=NULL;i++)
		{
			if(strcmp(tokens[i],"&&")==0)
			{
				c=1;
				break;
			}
			if(strcmp(tokens[i],"&&&")==0)
			{
				c=2;
				break;
			}
		}
		if(c!=0)
		{
			if(c==1)
			{
				
				char a[64][64][64];
				int j=0;
				int k=0;
				char c[1]={'\0',};
				for(int i=0;tokens[i]!=NULL;i++)
				{
					if(strcmp(tokens[i],"&&")==0)
					{
						strcpy(a[j][k], c);
						k=0;
						j++;
					}
					else {
						strcpy(a[j][k], tokens[i]);
						k++;
					}
					
				}
				strcpy(a[j][k], c);
				// fprintf(stderr,"hehe");
				for(int i=0;i<=j;i++)
				{
					// char * const* c=a[i];

					// printf("%s",)
					
					char* b[64];
					for(int l=0;l<64;l++)
					{
						if(strcmp(a[i][l],"\0")==0)
						{	
							b[l]=NULL;
							break;
						}
						
						b[l]=a[i][l];
					}
					int cc=fork();
					if(cc ==0)
					{
					// b[2] = NULL;
					// printf("%s\n%s\n%s\n",b[0],b[1],b[2]);
					if(execvp(a[i][0],b) == -1)
						{
							printf("Incorrect command entered\n");
							// printf("%s\n",tokens[0]);
							// exit(NULL);
						}
					exit(1);
					}
					else {
						signal(SIGINT,sigint_handler);
						
						int x= waitpid(cc,NULL,0);
						if(handler ==1)
						{
							handler=0;
							break;
						}
					}
				}

			}
			if(c==2)
			{
				char a[64][64][64];
				int j=0;
				int k=0;
				char c[1]={'\0',};
				for(int i=0;tokens[i]!=NULL;i++)
				{
					if(strcmp(tokens[i],"&&&")==0)
					{
						strcpy(a[j][k], c);
						k=0;
						j++;
					}
					else {
						strcpy(a[j][k], tokens[i]);
						k++;
					}
					
				}
				strcpy(a[j][k], c);
				int pl[64];
				int it=0;
				for(int i=0;i<=j;i++)
				{
					// char * const* c=a[i];

					// printf("%s",)
					
					char* b[64];
					for(int l=0;l<64;l++)
					{
						if(strcmp(a[i][l],"\0")==0)
						{	
							b[l]=NULL;
							break;
						}
						
						b[l]=a[i][l];
					}
					int cc=fork();
					pl[it]=cc;
					it++;
					if(cc ==0)
					{
					// b[2] = NULL;
					// printf("%s\n%s\n%s\n",b[0],b[1],b[2]);
					
					if(execvp(a[i][0],b) == -1)
						{
							printf("Incorrect command entered\n");
							// printf("%s\n",tokens[0]);
							// exit(NULL);
						}
						execl(const char *path, const char *arg, ...)
					exit(1);
					}
				}
				for(int i=0;i<it;i++)
				{
					signal(SIGINT,sigint_handler);
					waitpid(pl[i], NULL, 0);
				}

			}
			continue;
		}




		int cc= fork();
		if(strcmp(tokens[size-1],"&")==0 && cc!=0)
		{
			for(int i=0;i<64;i++)
			{
				if(f[i]==0)
				{
					f[i]=1;
					bg[i]=cc;
					break;
				}
			}
		}
		if(cc ==0)
		{
			if(strcmp(tokens[size-1],"&")==0)
			{	setpgid(0,0);
				tokens[size-1]=NULL;
				if(tokens[0]==NULL)
				{
					exit(1);
				}

				if(execvp(tokens[0],tokens) == -1 && strcmp(tokens[0]," ") !=0)
				{
					printf("Incorrect command entered\n");
					// printf("%s\n",tokens[0]);
					// exit(NULL);
				}
			}
			else if(strcmp(tokens[0],"cd")!=0)
			{
				if(execvp(tokens[0],tokens) == -1 && strcmp(tokens[0]," ") !=0)
				{
					printf("Incorrect command entered\n");
					// printf("%s\n",tokens[0]);
				}
			}
			exit(1);
		}
		else if(strcmp(tokens[size-1],"&")!=0){
			signal(SIGINT,sigint_handler);
			int x= waitpid(cc,NULL,0);
			if(strcmp(tokens[0],"cd")==0)
			{
				if(chdir(tokens[1]) == -1)
				{
					printf("Incorrect path entered\n");
				}
			}
		}
		
		
			
		
		
       
		// Freeing the allocated memory	
		for(int i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);

	}
	return 0;
}
