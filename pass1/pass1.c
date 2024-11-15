#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
  FILE *f1, *f2, *f3, *f4;
  char s[100], lab[30], opcode[30], opa[30], opcode1[30], opa1[30];
  int locctr, x = 0;

  // open files.
  f1 = fopen("input.txt", "r");
  f2 = fopen("opcode.txt", "r");
  f3 = fopen("out1.txt", "w");
  f4 = fopen("sym1.txt", "w");

  // read till the end.
  while (fscanf(f1, "%s %s %s", lab, opcode, opa) != EOF) 
  {
    // check if it is START directive.
    if (strcmp(lab, "**") == 0 && strcmp(opcode, "START") == 0) 
    {

      // write out START to out1.txt and set locctr to start address.
      fprintf(f3, "%s\t%s\t%s", lab, opcode, opa);
      locctr = atoi(opa); // ascii to interger conversion.
    } 
    else 
    {
      rewind(f2);
      x = 0;

      // search for opcode.
      while (fscanf(f2, "%s %s", opcode1, opa1) != EOF) 
      {
        if (strcmp(opcode, opcode1) == 0) // found opcode
        {
          x = 1; // set the opcode found flag.
          break;
        }
      }

      if (x == 1) 
      {
        // write to out1.txt and increment locctr by 1.
        fprintf(f3, "\n%d\t%s\t%s\t%s", locctr, lab, opcode, opa);
        locctr += 3;
      } 
      else 
      {
        // opcode not found.
        // handle storage directives and other cases.
        if (strcmp(opcode, "RESW") == 0) 
        {
          fprintf(f3, "\n%d\t%s\t%s\t%s", locctr, lab, opcode, opa);
          fprintf(f4, "\n%d\t%s", locctr, lab); // write label to the sym1.txt
          locctr += 3 * atoi(opa);
        } 
        else if (strcmp(opcode, "WORD") == 0) 
        {
          fprintf(f3, "\n%d\t%s\t%s\t%s", locctr, lab, opcode, opa);
          fprintf(f4, "\n%d\t%s", locctr, lab);
          locctr += 3; // Increment location counter by 3
        } 
        else if (strcmp(opcode, "BYTE") == 0) 
        {
          fprintf(f3, "\n%d\t%s\t%s\t%s", locctr, lab, opcode, opa);
          fprintf(f4, "\n%d\t%s", locctr, lab);
          locctr += 1; // Increment location counter by 1
        } 
        else if (strcmp(opcode, "RESB") == 0) 
        {
          fprintf(f3, "\n%d\t%s\t%s\t%s", locctr, lab, opcode, opa);
          fprintf(f4, "\n%d\t%s", locctr, lab);
          locctr += atoi(opa); // Increment location counter by operand
        } 
        else // For any other instruction, assume operand value as size
        {
          fprintf(f3, "\n%d\t%s\t%s\t%s", locctr, lab, opcode, opa);
          fprintf(f4, "\n%d\t%s", locctr, lab);
          locctr += atoi(opa); // Increment location counter by operand
        }
      }
    }
  }

  fclose(f1);
  fclose(f2);
  fclose(f3);
  fclose(f4);
}
