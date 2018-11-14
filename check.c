#include "myas.h"

int is_valid(char *op, char *args)
{
	char regi[] = "%eax%ecx%edx%ebx%esp%ebp%esi%edi";
	char hx_digit[] = "0 1 2 3 4 5 6 7 8 9 a b c d e f A B C D E F";
	char scale[] = "1 2 4 8";

	char copy[100] = { NULL , };

	strcpy(copy, args);

	char ch1[100] = { NULL , };
	char ch2[100] = { NULL , };

	char *re_save[100] = { NULL , };
	char *re1;
	char *re2;
	char *rere1 = malloc(sizeof(char) * 30);
	char *rere2 = malloc(sizeof(char) * 30);

	int len = strlen(args);

	int c = 0;
	int i = 0;
	int k = 0;
	int l = 0;
	int j = 0;
	
	int com_count = 0;
	int lp_count = 0;
	int flag = 0;
	int value_count = 0;
	int com2_count = 0;
	int lp2_count = 0;

	int lastcmm = 0;


	if (copy[0] == '0' || copy[0] == '$' || copy[0] == '(' || copy[0] == '-')
	{
		for (c = len - 1; c >= 0; c--)
		{
			if (copy[c] == ',')
			{
				lastcmm = c;
				break;
			}
		}
	}else
	{
		for (c = 0; c < len; c++)
		{
			if (copy[c] == ',')
			{
				lastcmm = c;
				break;
			}
		}
	}


	for (k = 0; k < lastcmm; k++)
	{
		if (copy[k] == ',')
		{
			com_count++;
			ch1[k] = ' ';
		}
		else
		ch1[k] = copy[j];

		j++;
	}

	if (copy[lastcmm - 1] == ')')
	{
		lp_count++;
		ch1[lastcmm - 1] = ' ';
	}


	for (i = 0; i < lastcmm; i++)
	{
		if (copy[i] == '(')
		{
			lp_count++;
			ch1[i] = ' ';
		}
	}

	for (i = lastcmm + 1; i <= len; i++)
	{
		if (copy[i] == ',')
		{
			com2_count++;
			ch2[l] = ' ';
		}
		else
			ch2[l] = copy[i];

		l++;
	}
	for(i = 0; i < 15; i++)
	{
		if (ch2[i] == '(')
		{
		lp2_count++;
		ch2[i] = ' ';
		}
	}

	if (ch2[l-2] == ')')
	{
		lp2_count++;
		ch2[l-2] = ' ';
	}

	re1 = ch1;
	re2 = ch2;

	c = 0;

	if (com_count != 0 || lp_count == 2)
	{
		rere1 = strtok(ch1, " ");

		while (rere1 != NULL)
		{
			re_save[c] = rere1;
			rere1 = strtok(NULL, " ");

			c++;
		}
	} 
	else if (com_count > 2)
	{
		return 0;
	}



	if (com2_count != 0 || lp2_count == 2)
	{
		rere2 = strtok(ch2, " ");

		while (rere2 != NULL)
		{
			re_save[c] = rere2;
			rere2 = strtok(NULL, " ");

			c++;
		}
	} 
	else if (com2_count > 2)
	{
		return 0;
	}

	value_count = c;

	i = 0;
	k = 0;
	l = 0;

	if (strcmp(op, "mov") == 1)
	{
		return 0;
	}

	while (1)
	{
		if (lp_count == NULL)
		{
			switch (ch1[k])
			{
			case '%':
				if (strstr(regi, re1) != NULL) printf("This is register\n");
				else
				{
					return 0;
				}
				break;
			case '0':
				if (ch1[1] == 'x')
				{
					for (i = 2; i < lastcmm; i++)
					{
						if (strchr(hx_digit, ch1[i]) != NULL);
						else
						{
							return 0;
						}
					}
				}
				printf("This is memory\n");
				break;
			case '$':
				if (ch1[1] == '0' && ch1[2] == 'x')
				{
					for (i = 3; i < lastcmm; i++)
					{
						if (strchr(hx_digit, ch1[i]) != NULL);
						else
						{
							return 0;
						}
					}
				}
				printf("This is immediate \n");
				break;
			default:
				printf("not value\n");
				return 0;
				break;
			}
		}
		else if (lp_count == 2)
		{

			switch (com_count)
			{
			case 0:
				switch (ch1[k])
				{
				case '-':
					if (ch1[1] == '0' && ch1[2] == 'x' && strstr(regi,re_save[1]) !=0 )
					{
						for (i = 3; i < strlen(re_save[0]); i++)
						{
							if (strchr(hx_digit, ch1[i]) != NULL);
							else
							{
								return 0;
							}
						}
					}
					printf("This is Memmory \n");
					break;
				case ' ':
					if (strstr(regi, re1) == NULL) printf("This is Memmory \n");
					else
					{
						return 0;
					}
					break;
				default:
					printf("not value\n");
					return 0;
					break;
				}
				break;
			case 1:
				switch (ch1[k])
				{
				case ' ':
					if (strstr(regi, re_save[0]) != NULL &&strstr(regi, re_save[1]) != NULL) printf("This is Memmory \n");
					else
					{
						return 0;
					}
					break;
				default:
					printf("not value\n");
					return 0;
					break;
				}
				break;
			case 2:
				switch (ch1[k])
					{
				case ' ':
					if (strstr(regi, re_save[0]) != NULL && strstr(regi, re_save[1]) != NULL && strstr(scale, re_save[2]) != NULL) printf("This is Memmory \n");
					else
					{
						return 0;
					}
					break;
				case '0':
					if (ch1[1] == 'x')
					{
						for (i = 2; i < strlen(re_save[0]); i++)
						{
							if (strchr(hx_digit, ch1[i]) != NULL);
							else
							{
								return 0;
							}
						}
						if (strstr(regi, re_save[1]) != NULL && strstr(regi, re_save[2]) != NULL && strstr(scale, re_save[3]) != NULL) printf("This is Memmory \n");
						else return 0;
					}
					break;
				case '-':
					if (ch1[1] == '0' && ch1[2] == 'x')
					{
						for (i = 3; i < strlen(re_save[0]); i++)
						{
							if (strchr(hx_digit, ch1[i]) != NULL);
							else
							{
								return 0;
							}
						}
						if (strstr(regi, re_save[1]) != NULL && strstr(regi, re_save[2]) != NULL && strstr(scale, re_save[3]) != NULL) printf("This is Memmory \n");
						else return 0;
					}
					break;
				default:
					printf("not value\n");
					return 0;
					break;
					}
				break;
			default:
				printf("not value\n");
				return 0;
				break;
			}
		}
		else
			return 0;
		break;
	}

	k = 0;

	while (1)
	{
		if (lp2_count == NULL)
		{
			switch (ch2[k])
			{
			case '%':
				if (strstr(regi, re2) != NULL) printf("This is register\n");
				else
				{
					return 0;
				}
				break;
			case '0':
				if (ch2[1] == 'x')
				{
					for (i = 2; i < strlen(ch2); i++)
					{
						if (strchr(hx_digit, ch2[i]) != NULL);
						else
						{
							return 0;
						}
					}
				}
				printf("This is memory\n");
				break;
			default:
				printf("not value\n");
				return 0;
				break;
			}
		}
		else if (lp2_count == 2)
		{
			switch (com2_count)
			{
			case 0:
				switch (ch2[k])
				{
				case '-':
					if (ch2[1] == '0' && ch2[2] == 'x' && strstr(regi, re_save[1]) != 0)
					{
						for (i = 3; i < strlen(re_save[0]); i++)
						{
							if (strchr(hx_digit, ch2[i]) != NULL);
							else
							{
								return 0;
							}
						}
					}
					printf("This is Memmory \n");
					break;
				case ' ':
					if (strstr(regi, re2) == NULL) printf("This is Memmory \n");
					else
					{
						return 0;
					}
					break;
				case '0':
					if (strstr(regi, re2) == NULL) printf("This is Memmory \n");
					else
					{
						return 0;
					}
					break;
				default:
					printf("not value\n");
					return 0;
					break;
				}
				break;
			case 1:
				switch (ch2[k])
				{
				case ' ':
					if (strstr(regi, re_save[0]) != NULL &&strstr(regi, re_save[1]) != NULL) printf("This is Memmory \n");
					else
					{
						return 0;
					}
					break;
				default:
					printf("not value\n");
					return 0;
					break;
				}
				break;
			case 2:
				switch (ch2[k])
				{
				case ' ':
					if (strstr(regi, re_save[0]) != NULL && strstr(regi, re_save[1]) != NULL && strstr(scale, re_save[2]) != NULL) printf("This is Memmory \n");
					else
					{
						return 0;
					}
					break;
				case '0':
					if (ch2[1] == 'x')
					{
						for (i = 2; i < strlen(re_save[0]); i++)
						{
							if (strchr(hx_digit, ch2[i]) != NULL);
							else
							{
								return 0;
							}
						}
						if (strstr(regi, re_save[1]) != NULL && strstr(regi, re_save[2]) != NULL && strstr(scale, re_save[3]) != NULL) printf("This is Memmory \n");
						else return 0;
					}
					break;
				case '-':
					if (ch2[1] == '0' && ch2[2] == 'x')
					{
						for (i = 3; i < strlen(re_save[0]); i++)
						{
							if (strchr(hx_digit, ch2[i]) != NULL);
							else
							{
								return 0;
							}
						}
						if (strstr(regi, re_save[1]) != NULL && strstr(regi, re_save[2]) != NULL && strstr(scale, re_save[3]) != NULL) printf("This is Memmory \n");
						else return 0;
					}
					break;
				default:
					printf("not value\n");
					return 0;
					break;
				}
				break;
			default:
				printf("not value\n");
				return 0;
				break;
			}
		}
		else
			return 0;
		break;
	}

	free(rere1);
	free(rere2);
	return 1;

}

