#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    // Declare variables to hold opcode, operand, symbol, label, and other intermediate data
	char opcode[20], operand[20], symbol[20], label[20], code[20], mnemonic[25], character, add[20], objectcode[20];
	int flag, flag1, locctr, location, loc;

	// File pointers for input and output files
	FILE *fp1, *fp2, *fp3, *fp4;

    // Open necessary files: output file from pass 1, new output file, opcode table, and symbol table
	fp1 = fopen("out1.txt", "r");
	fp2 = fopen("twoout.txt", "w");
	fp3 = fopen("opcode.txt", "r");
	fp4 = fopen("sym1.txt", "r");

	// Read the first line from pass 1 output file
	fscanf(fp1, "%s %s %s", label, opcode, operand);

    // Check if the program starts with a START directive
	if (strcmp(opcode, "START") == 0)
	{
		// Write the START line to the output file for pass 2
		fprintf(fp2, "%s\t%s\t%s\n", label, opcode, operand);
		
		// Read the next line containing the starting address and initialize the location counter
		fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand);
	}

    while(strcmp(opcode, "END") != 0)
    {
        flag = 0; //opcode found flag.

        while (strcmp(code, "END") != 0)
		{
			// Check if the current opcode matches and is not a pseudo-op
			if ((strcmp(opcode, code) == 0) && (strcmp(mnemonic, "*") != 0))
			{
				flag = 1;  // Set flag if a match is found
				break;
			}
			fscanf(fp3, "%s %s", code, mnemonic);
		}

        // If the opcode is found in the opcode table
		if (flag == 1)
		{
			flag1 = 0;  // Reset flag1 to indicate if operand symbol is found in symbol table

			// Search the symbol table to find the address of the operand symbol
			rewind(fp4);  // Reset file pointer for symbol table
			while (!feof(fp4))
			{
				fscanf(fp4, "%d %s", &loc, symbol);

				// Check if the operand symbol matches
				if (strcmp(symbol, operand) == 0)
				{
					flag1 = 1;  // Set flag if symbol is found
					break;
				}
			}

			// If the operand symbol is found, construct the object code
			if (flag1 == 1)
			{
				sprintf(add, "%d", loc);              // Convert address to string format
				strcpy(objectcode, strcat(mnemonic, add));  // Concatenate mnemonic and address
			}
		}
        // If opcode is BYTE or WORD, handle data definitions
		else if ((strcmp(opcode, "BYTE") == 0) || (strcmp(opcode, "WORD") == 0))
		{
			// Check if operand is character or hexadecimal constant
			if ((operand[0] == 'C') || (operand[0] == 'X'))
			{
				character = operand[2];              // Extract character from operand
				sprintf(add, "%x", character);       // Convert character to hexadecimal
				strcpy(objectcode, add);            // Store as object code
			}
			else
			{
				strcpy(objectcode, operand);         // Use operand directly as object code
			}
		}
        else
			strcpy(objectcode, "\0");
        
        // Write the assembled line to the output file
		fprintf(fp2, "%s\t%s\t%s\t%d\t%s\n", label, opcode, operand, locctr, objectcode);

		// Read the next line from the pass 1 output file
		fscanf(fp1, "%d %s %s %s", &locctr, label, opcode, operand);
    }


	// Write the END directive line to the output file
	fprintf(fp2, "%s\t%s\t%s\t%d\n", label, opcode, operand, locctr);

	// Close all open files
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}