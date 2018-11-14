#include "myas.h"
	
	int instr_trans(char *op, char *args, char* mcode)
	{
		// check syntax 
		if(!is_valid(op, args)){
			printf("Error: %s %s is not valid\n", op, args);
			return 0;
		}
	
	
		strcpy(mcode, "AB CD EF");
	
		/********************************/
	    /*  							*/
		/*    generate machine code     */
	    /* 1.reg to reg 2.mem to reg 3.mem to reg(addressing/disp) 4.mem to reg(eax) 5.reg(eax) to mem 6. immediate to reg							*/
		/********************************/
		
		return 1;	
	}

