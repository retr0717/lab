#include <stdio.h>

void FirstFit(int bsize[], int psize[], int bno, int pno, int flags[], int allocation[])
{
    // initial setup
    for (int i = 0; i < 10; i++)
    {
        flags[i] = 0;
        allocation[i] = -1;
    }

    // logic
    for (int i = 0; i < pno; i++)
    {
        for (int j = 0; j < bno; j++)
        {
            if (bsize[j] >= psize[i])
            {
                // allocate block psize[i] to block j.
                allocation[i] = j;

                // reduce the block size if there is any left.
                bsize[j] -= psize[i];
                break;
            }
        }
    }

    // display
    printf("\nProcess No\tProcess Size\tBlock No\tFree Space");
    printf("\n-----------------------------------------------\n");

    for (int i = 0; i < pno; i++)
    {
        printf("\n%d\t\t%d\t\t", i + 1, psize[i]);
        if (allocation[i] != -1)
            printf("%d\t\t", allocation[i] + 1);
        else
            printf("Not allocated\t");

        printf("%d\n", bsize[i]);
    }
}

void BestFit(int bsize[], int psize[], int bno, int pno)
{
    int lowest = 9999, temp;
    int barray[20]= {0}, parray[20] = {0}, fragment[20];

    for (int i = 0; i < pno; i++)
    {
        for (int j = 0; j < bno; j++)
        {
            if(barray[j] != 1)
            {
                temp = bsize[j] - psize[i];
                if (temp >= 0)
                {
                    if(temp<lowest)
                    {
                        parray[i] = j;
                        lowest = temp;
                    }
                }
            }
        }

        fragment[i] = lowest;
        barray[parray[i]] = 1;
        lowest=10000;
    }

    printf("\nProcess No\tProcess Size\tBlock size\tFragment\n");
    printf("-----------------------------------------------------\n");
    for(int i = 0 ; i < pno && parray[i] != 0 ; i++)
    {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,psize[i],parray[i]+1,bsize[parray[i]],fragment[i]);
    }
}

void WorstFit(int bsize[], int psize[], int bno, int pno)
{
    int all[20];
    for(int i = 0 ; i < pno; i++)
        all[i] = -1;
    
    for(int i = 0 ; i< pno ; i++)
    {
        int worstplace = -1;
        for(int j = 0 ; j < bno ; j++)
        {
            if(bsize[j] >= psize[i])
            {
                if(worstplace == -1)
                    worstplace = j;  
                else if(bsize[worstplace] < bsize[j])
                    worstplace = j;
            }
        }

        if(worstplace != -1)
        {
            all[i] = worstplace;
            bsize[worstplace] -= psize[i];
        }
    }

        printf("\nProcess No\tProcess Size\tBlock No\tFree\n");
        for(int i = 0 ; i < pno ; i++)
        {
            printf("%d\t\t%d\t\t",i+1,psize[i]);
            if(all[i] != -1)
            {
                printf("%d\t\t",all[i]+1);
            }
            else
                printf("Not Allocated\t");
            printf("%d\n",bsize[i]);
        }
}

int main()
{
    int bsize[20], psize[20], bno, pno, flags[20], allocation[20];

    printf("Enter the no of blocks : ");
    scanf("%d", &bno);
    printf("\nEnter the size of each block\n");
    for (int i = 0; i < bno; i++)
        scanf("%d", &bsize[i]);

    printf("\nEnter the no of process : ");
    scanf("%d", &pno);
    printf("\nEnter the size of each process\n");
    for (int i = 0; i < pno; i++)
        scanf("%d", &psize[i]);

    while (1)
    {
        int choice;
        printf("\n\n1.First Fit\n2.Best Fit\n3. Worst Fit\n");
        printf("\nEnter the choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            FirstFit(bsize, psize, bno, pno, flags, allocation);
            break;
        case 2:
            BestFit(bsize,psize,bno,pno);
            break;
        case 3:
            WorstFit(bsize,psize,bno,pno);
            break;
        default:
            printf("\nInvalid Option\n");
        }
    }

    return 0;
}