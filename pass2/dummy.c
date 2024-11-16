#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    char label[30], operand[30], opcode[30], character, code[30], objectcode[30], mnemonic[30], symbol[20], add[30];
    int locctr, location, loc, flag, flag1;

    // File pointers for input and output files
	FILE *fp1, *fp2, *fp3, *fp4;

    // Open necessary files: output file from pass 1, new output file, opcode table, and symbol table
	fp1 = fopen("out1.txt", "r");
	fp2 = fopen("twoout.txt", "w");
	fp3 = fopen("opcode.txt", "r");
	fp4 = fopen("sym1.txt", "r");

    fscanf(fp1, "%s %s %s", label, opcode, operand);

    if(strcmp(opcode, "START") == 0)
    {
        fprintf(fp2, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1,"%d %s %s %s", &locctr, label, opcode, operand);
    }

    while(strcmp(opcode, "END") != 0)
    {
        flag = 0;

        while(strcmp(code, "END") != 0)
        {
            if((strcmp(opcode, code) == 0)  && (strcmp(mnemonic, "*") != 0))
            {
                flag = 1;
                break;
            }

            fscanf(fp3,"%s %s", code, mnemonic);
        }

        if(flag == 1)
        {
            flag1 = 0;

            rewind(fp4);
            while(!feof(fp4))
            {
                fscanf(fp4, "%d %s", &loc, symbol);
                if(strcmp(operand, symbol) == 0)
                {
                    flag1 = 1;
                    break;
                }
            }

            if(flag1 == 1)
            {
                sprintf(add, "%d", loc);
                strcpy(objectcode, strcat(mnemonic, add));
            }
        }
        else if((strcmp(opcode, "BYTE") == 0) || (strcmp(opcode, "WORD") == 0))
        {
            if(operand[0] == 'C' || operand[0] == 'X')
            {
                character = operand[2];
                sprintf(add, "%x", character);
                strcpy(objectcode, add);
            }
            else
                strcpy(objectcode, operand);
        }
        else
            strcpy(objectcode, "\0");
        
        fprintf(fp2, "%s\t%s\t%s\t%d\t%s\n", label, opcode, operand, locctr, objectcode);
        fscanf(fp1,"%d %s %s %s", &locctr, label, opcode, operand);
    }

    // Write the END directive line to the output file
	fprintf(fp2, "%s\t%s\t%s\t%d\n", label, opcode, operand, locctr);

	// Close all open files
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}