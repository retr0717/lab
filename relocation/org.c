#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convert(char h[12]);
char bitmask[12];
char bit[12] = {0};

int main() {
    char add[6], length[10], input[10], relocbit, ch, pn[5];
    int start, inp, len, i, address, opcode, addr, actualadd, tlen;
    FILE *fp1, *fp2;

    // Get the starting address
    printf("Enter the actual starting address: ");
    scanf("%x", &start);

    // Open files
    fp1 = fopen("RLIN.txt", "r");
    if (fp1 == NULL) {
        perror("Error opening RLIN.TXT");
        return 1;
    }
    fp2 = fopen("RLOUT.TXT", "w");
    if (fp2 == NULL) {
        perror("Error opening RLOUT.TXT");
        fclose(fp1);
        return 1;
    }

    fscanf(fp1, "%s", input);

    // Write header to output file
    fprintf(fp2, "-------------------------------------------\n");
    fprintf(fp2, "ADDRESS\tCONTENT\n");
    fprintf(fp2, "-------------------------------------------\n");

    // Read the input until the 'E' character
    while (strcmp(input, "E") != 0) {
        if (strcmp(input, "H") == 0) {
            fscanf(fp1, "%s", pn);    // Program name
            fscanf(fp1, "%x", &add);  // Starting address
            fscanf(fp1, "%x", &length); // Program length
            fscanf(fp1, "%s", input);  // Read next line
        }

        if (strcmp(input, "T") == 0) {
            fscanf(fp1, "%x", &address);  // Address
            fscanf(fp1, "%x", &tlen);     // Text length
            fscanf(fp1, "%s", bitmask);   // Bitmask
            address += start;

            convert(bitmask);
            len = strlen(bit);
            if (len >= 11) len = 10;

            for (i = 0; i < len; i++) {
                fscanf(fp1, "%x", &opcode);  // Opcode
                fscanf(fp1, "%x", &addr);    // Address
                relocbit = bit[i];

                if (relocbit == '0')
                    actualadd = addr;
                else
                    actualadd = addr + start;

                // Write to output file
                fprintf(fp2, "\n%x\t\t%x%x\n", address, opcode, actualadd);
                address += 3;
            }

            fscanf(fp1, "%s", input);  // Read next record
        }
    }

    // Write footer to output file
    fprintf(fp2, "-------------------------------------------\n");

    // Close files
    fclose(fp1);
    fclose(fp2);

    // Display the contents of the output file
    printf("\n\nThe contents of output file (RLOUT.TXT):\n\n");
    fp2 = fopen("RLOUT.TXT", "r");
    if (fp2 == NULL) {
        perror("Error opening RLOUT.TXT");
        return 1;
    }

    ch = fgetc(fp2);
    while (ch != EOF) {
        printf("%c", ch);
        ch = fgetc(fp2);
    }

    fclose(fp2);
    return 0;
}

// Convert the bitmask from hexadecimal to binary
void convert(char h[12]) {
    int i, l;
    strcpy(bit, "");
    l = strlen(h);
    for (i = 0; i < l; i++) {
        switch (h[i]) {
            case '0': strcat(bit, "0"); break;
            case '1': strcat(bit, "1"); break;
            case '2': strcat(bit, "10"); break;
            case '3': strcat(bit, "11"); break;
            case '4': strcat(bit, "100"); break;
            case '5': strcat(bit, "101"); break;
            case '6': strcat(bit, "110"); break;
            case '7': strcat(bit, "111"); break;
            case '8': strcat(bit, "1000"); break;
            case '9': strcat(bit, "1001"); break;
            case 'A': strcat(bit, "1010"); break;
            case 'B': strcat(bit, "1011"); break;
            case 'C': strcat(bit, "1100"); break;
            case 'D': strcat(bit, "1101"); break;
            case 'E': strcat(bit, "1110"); break;
            case 'F': strcat(bit, "1111"); break;
        }
    }
}