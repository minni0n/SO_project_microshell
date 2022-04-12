#include<stdio.h>
#include<string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
	int k=1, n, i, time, r=0;
	char str[100], str1[100];
	char cwd[100];
	char *path=NULL, *istr, *path2;
	char sep [10]=" ";
	printf("*** MicroShell SOP ***\nAutor: Serhii Hrosh\n\n");
	while(k!=0)
	{
		memset (str, 0, sizeof(str));
		memset (str1, 0, sizeof(str1));
		n=-1;
		if (getcwd(cwd, sizeof(cwd)) != NULL) 
   		{
       		printf("[{%s}]$ ", cwd);
   		}
		for(i=0;i<100;i++)
		{
			scanf("%c",&str[i]);
			n++;
			if(str[i]=='\n') break;
		}
		for(i=0;i<n;i++)
		{
			str1[i]=str[i];
		}
		istr = strtok (str1,sep);
		   while (istr != NULL)
		   {
		      	  path = istr;
			  path2 = istr;	
			  r++;
			  istr = strtok (NULL,sep);
		   }
		if (r==1) path2 = NULL;
		r = 0;
		if (memcmp(str1,"exit",4)==0) return 0;
		else if (memcmp(str1,"help",4)==0) printf("Tworca tego programu jest Serhii Hrosh.\nMoj program moze wykonywac takie polecenia: help, exit, cd, rm, pwd, clear, sleep \n");
		else if (memcmp(str1,"cd",2)==0)
		{
			if(memcmp(path,"cd",2)==0 || (memcmp(path,"~",1)==0))
			{
				if ((chdir("/home/students/s452641"))==-1) perror("Error");				
			}
			else 
			{
				if (chdir(path)==-1) perror("Error");			
			}
		}
		
		else if (memcmp(str1,"rm",2)==0) 
		{
			if (unlink(path)==-1) printf("rm: Cannot remove '%s': No such file or directory\n",path);
			else unlink(path);
		}
		else if (memcmp(str1,"pwd",3)==0) printf("%s\n",cwd);
		else if (memcmp(str1,"clear",5)==0) system("clear");
		else if (memcmp(str1,"sleep",5)==0) 
		{
			time = atoi(path);
			if (memcmp(path,"sleep",5)==0) printf("sleep: missing operand\n");
			else sleep(time);	
		}
		else if (memcmp(str1,"",1)==0) continue;
		else 
		{
				pid_t F=fork();
			if(F==0)
			{
				if (path2==NULL) 
				{
				execlp(str1,str1,NULL);
				}
				else execlp(str1,str1,path,NULL);
				perror("Error");
				_exit(0);
			}
			if (F>0)
			{
				wait(0);
			}
			if (F<0)
			{
				perror("Error");
			}

		}
	}
	return 0;
}
