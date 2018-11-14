#include "myas.h"

 

int instr_trans(char *op, char *args, char* mcode)

{

	char save_argu[100] = { NULL , };

	char fir_argu[100] = { NULL , };

	char sec_argu[100] = { NULL , };

	char sum[4] = { NULL , };

 

	char copy[256] = { NULL, };

 

	strcpy(copy, args);

 

	char *argu1; // 앞에 argument

	char *argu2; // 뒤에 argument

 

	int i = 0;

	int j = 0;

	int c = 0;

	int len = strlen(args);

 

	int last_com = 0;

	int argu1_mode = 0;

	int argu2_mode = 0;

 

	printf("op = %s, args = %s\n", op, args);

 

	// check syntax 

	if (!is_valid(op, args))

	{

		printf("Error: %s %s is not valid\n", op, args);

		return 0;

	}

 

	if (copy[0] == '0' || copy[0] == '$' || copy[0] == '(' || copy[0] == '-')

	{

		for (c = len - 1; c >= 0; c--)

		{

			if (copy[c] == ',')

			{

				last_com = c;

				break;

			}

		}

	}

	else

	{

		for (c = 0; c < len; c++)

		{

			if (copy[c] == ',')

			{

				last_com = c;

				break;

			}

		}

	}

 

	for (i = 0; i < last_com; i++)

	{

		fir_argu[i] = copy[i];

	}

 

	for (i = last_com+1; i < len; i++)

	{

		sec_argu[j] = copy[i];

		j++;

	}

 

	argu1 = fir_argu;

	argu2 = sec_argu;

 

	// register = 8 memory(addressing w.o) = 9  memory = 12

	// memory(addressing w) = 10 immediate = 11

	// %eax = 0 %ecx = 1 %edx = 2 

	// %ebx = 3 %esp = 4 %ebp = 5

	// %esi = 6 %edi = 7

	while (1)

	{

		switch (fir_argu[0])

		{

		case '%':

			argu1_mode = 8;

			break;

		case '(':

			argu1_mode = 9;

			break;

		case '0': case '-':

			argu1_mode = 10;

			break;

		case '$':

			argu1_mode = 11;

			break;

		default:

			printf("not value\n");

			return 0;

			break;

		}

		

		switch (sec_argu[0])

		{

		case '%':

			if (strcmp(argu2, "%eax") == NULL) sum[1] = '8';

			else if(strcmp(argu2, "%ecx") == NULL)  sum[1] = '9';

			else if (strcmp(argu2, "%edx") == NULL)  sum[1] = 'a';

			else if (strcmp(argu2, "%ebx") == NULL)  sum[1] = 'b';

			else if (strcmp(argu2, "%esp") == NULL)  sum[1] = 'c';

			else if (strcmp(argu2, "%ebp") == NULL)  sum[1] = 'd';

			else if (strcmp(argu2, "%esi") == NULL)  sum[1] = 'e';

			else  sum[1] = 'f';

			break;

		case '(': case '0': case '-':

			argu2_mode = 12;

			break;

		default:

			printf("not value\n");

			return 0;

			break;

		}

		break;

	}

 

	while (1)

	{

		switch (argu1_mode)

		{

		case 8:									//register to register

			sum[0] = '8';

			sum[1] = '9';

			break;

		case 9:									//memory to register(addressing w.o/ disp.)

			if(sum[1] != '8') sum[0] = '8';		//exception register eax

			break;

		case 10:

			if (sum[1] == '8')					//memory to register(eax)

			{

				sum[0] = 'a';

				sum[1] = '1';

			}

			else sum[0] = '8';

			break;

		case 11:

			sum[0] = 'b';					//immediate to register

			break;

		default:

			break;

		}

		break;

	}

 

	printf("sum = %s\n", sum);

 

	strcpy(mcode, sum);

 

	return 1;

}

