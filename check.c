#include "myas.h"

int is_valid(char *op, char *args)
{
	char regi[] = "%eax %ecx %edx %ebx %ebp %edi %esp";
	char copy[256] = {NULL, };

	strcpy(copy,args);

	char* ptr = strtok(copy, ",");
	char* value[40] = {NULL, }; 
	char ch[20] = {NULL, };
        
	int i = 0;
        int j = 0;
        int k = 0;
        int flag = 0;
        
        //printf("if valid, return 1\n");
	//printf("otherwise, return 0\n");

        while(ptr != NULL)
        {
           value[i] = ptr;
           i++;

           ptr - strtok(NULL, " ");
        }

        for(j = 0; j < 40; j++)
        {
           if(value[j] != NULL)
           {
              ch[j] = *value[j];
           }
        }


        if(strcmp(op, "mov") == 1)
        {
           flag++;
        }

        while(k < i)
        {
          switch(ch[k])
          {
          case '%':
             if(strstr(regi, value[k]) == NULL)
             {
                flag++;
             }
             break;
          case '+':
             break;
          case '-':
             break;
          case '(':
             break;
          case '0':
             break;
          case '$':
             break;
          default:
             flag++;
             break;
          }
          k++;
        }

        if(flag != 0)
        {
           return 0;
        }
        	
	return 1;
}
