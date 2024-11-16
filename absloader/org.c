#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main()
{
	// Declare variables for file handling, addresses, and strings
	FILE *fp;
	int i, addr1, l, j, staddr1;
	char name[10], line[50], name1[10], addr[10], rec[10], ch, staddr[10];

	// Prompt user for program name and read input
	printf("Enter program name: ");
	scanf("%s", name);

	// Open the object file for reading
	fp = fopen("objectcode.txt", "r");

	// Read the first line of the object file
	fscanf(fp, "%s", line);

	// Extract program name from the line (characters at positions 2 to 7)
	for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
		name1[j] = line[i];
	name1[j] = '\0';  // Null-terminate the extracted name

	// Display program name extracted from the object file
	printf("Name from obj: %s\n", name1);

	// Check if the entered name matches the name in the object file
	if (strcmp(name, name1) == 0)
	{
		// Read the next line from the object file
		fscanf(fp, "%s", line);

		// Loop through each line until end of file
		do
		{
			// Process lines starting with 'T' (Text record)
			if (line[0] == 'T')
			{
				// Extract starting address from the line (characters at positions 2 to 7)
				for (i = 2, j = 0; i < 8 && j < 6; i++, j++)
					staddr[j] = line[i];
				staddr[j] = '\0';  // Null-terminate the extracted address

				// Convert starting address to integer
				staddr1 = atoi(staddr);

				i = 12;  // Initialize index to read the object codes

				// Read object codes from the line until end marker ('$')
				while (line[i] != '$')
				{
					// Skip the '^' delimiter
					if (line[i] != '^')
					{
						// Print address and object code (two characters at a time)
						printf("00%d\t%c%c\n", staddr1, line[i], line[i + 1]);

						// Increment address and index to move to the next object code
						staddr1++;
						i = i + 2;
					}
					else
					{
						i++;  // Move to the next character if '^' is found
					}
				}
			}
			// Process lines starting with 'E' (End record)
			else if (line[0] == 'E')
			{
				// Print execution start address
				printf("Jump to execution address: %s\n", line[2]);
			}

			// Read the next line from the object file
			fscanf(fp, "%s", line);
		} while (!feof(fp));  // Continue until end of file
	}

	// Close the file after processing
	fclose(fp);
}