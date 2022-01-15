#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_char(char *string, char *delimit);

int main(int argc,char **argv)
{
	printf("Test\n");
	char **arr=split_char("1,2,3,4",",");
	if(arr != NULL)
	{
	//printf(arr[0]);
	
	free(arr);
	}
	return 0;
}

char** split_char(char *string, char *delimit)
{
	int i;
	int count=0;
	for(i=0;i<strlen(string);i++)
	{
		if(string[i] == delimit[0])
		{
			count++;
		}
	}
	if(count == 0)
	{
		return NULL;
	}
	printf("Count : %ld\n",count);
	char **array = (char**)malloc(count * sizeof(char*));
    for (i = 0; i < count; i++)
        array[i] = (char*)malloc(strlen(string) * sizeof(char));
	printf("alloc good\n");
	char* ptr = strtok(string, ",");
	if(ptr==NULL)
	{
		printf("None\n");
		free(array);
		return NULL;
	}
	printf("OK\n");
	
	i=0;
	
	while(ptr)
	{
			/*strcpy(array[i],ptr);
			i++;
			ptr = strtok(NULL, ",");*/
	}
	
	return array;
}