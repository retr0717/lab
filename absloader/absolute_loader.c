#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
    FILE *fp;
    char name[10], line[50], name1[10], addr[10], rec[10], ch, staddr[10];
    int i, addr1, l, j, staddr1;

    printf("Enter the name : ");
    scanf("%s", name);

    fp = fopen("objectcode.txt", "r");

    fscanf(fp, "%s", line);

    //copy name from object code to name1
    for(i = 2, j = 0; i<8, j<6; i++, j++)
    {
        name1[j] = line[i]; 
    }

    name1[j] = '\0';

    //check for inputed name and program name in object code are the same.
    if(strcmp(name, name1) == 0)
    {
        //read text record.
        fscanf(fp, "%s", line);

        do{

            if(line[0] == 'T')
            {

                //read text record starting address from index 2 to 7.
                for(i = 2, j = 0; i<8, j<6; i++, j++)
                {
                    staddr[j] = line[i]; 
                }

                staddr[j] = '\0';

                //convert starting address to integer.
                staddr1 = atoi(staddr);

                //read the text record data from index 12.
                i = 12;

                //read until the '$' (end of the text record) symbol.
                while(line[i] != '$')
                {
                    //skip the ^(delimiter).
                    if(line[i] != '^')
                    {
                        //print the address and 2 bytes of data at index 12,13
                        printf("00%d\t%c%c\n", staddr1, line[i], line[i+1]);
                        staddr1++;//increment the address by 1 to show where the next two bytes are stored.
                        i+=2;//to the next 2 bytes (to index 14).
                    }
                    else
                        i++;
                }
            }
            else if(line[0] = 'E')
            {
                printf("\nJump Execution to address  : %s\n", line[2]);
            }

            //read next line.   
            fscanf(fp, "%s", line);

        }while(!feof(fp));
    }

    fclose(fp);
}