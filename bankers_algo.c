#include <stdio.h>

int n,m,i,j,k,alloc[20][20],max[20][20],avail[50],ind = 0;

int SafeSequenceCheck(int need[][10], int request[], int n , int m, int pid)
{
    int ss[n];
    int alloc_cp[n][m], avail_cp[50], ind_cp = 0, need_cp[n][m], finish[n];
    //copy all matrix to new
    for( i = 0 ; i < n ; i++)
        for( j = 0 ; j < n ; j++)
            alloc_cp[i][j] = alloc[i][j];
    
    for( i = 0 ; i < n ; i++)
        for( j = 0 ; j < n ; j++)
            need_cp[i][j] = need[i][j];
    for( i = 0 ; i < m ; i++)
            avail_cp[i] = avail[i];
    
    for(i = 0 ; i < n ; i++)
    {
            finish[i] = 0;
    }

    //change avail matrix
    for(i = 0; i < m ; i++)
    {
        avail_cp[i] -= request[i];
        alloc_cp[pid][i] += request[i];
        need_cp[pid][i] += request[i];
    }
    
    for( k = 0 ; k < n ; k++)
    {
        for(i = 0 ; i < n ; i++)
        {
            if(finish[i] == 0)
            {
                //check of the resource need against available(work).
                int flag = 0;
                for( j = 0 ; j < m ; j++)
                {
                    //if the need is > work ==> means we cant satisfy to indicate that we have flag set to 1.
                    //if not flag = 0.
                    //after an entire loop if the break statement is not executed means the need can be satisfied.
                    if(need_cp[i][j] > avail_cp[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                //only reached here if the resource need <= available.
                //means the availability satisfies current process need.
                if(flag == 0)
                {
                    ss[ind_cp++] = i; 
                    //add released reource instance to available(work).
                    for( int y = 0 ; y < m ; y++)
                        avail_cp[y] += alloc_cp[i][j];
                    finish[i] = 1;
                }
            }
        }
   }

   int len = sizeof(ss)/sizeof(ss[0]);

   printf("\nlen : %d\n",len);
   for(i = 0 ; i < n ; i++)
        printf("%d  ",ss[i]);

   if(len == n)
   {
    return 1;
   }
   else
   {
        return 0;
    }
}

int main()
{
   
    
    //read no of processes
    printf("Enter the no of processes : ");
    scanf("%d",&n);

    //read no of resources
    printf("\nEnter the no of resources : ");
    scanf("%d",&m);

    //read allocation matrix
    printf("\nEnter the allocation matrix\n");
    for(i = 0 ; i < n ; i++)
        for(j = 0 ; j < m ; j++)
            scanf("%d",&alloc[i][j]);
    
    //read max matrix
    printf("\nEnter the max matrix\n");
    for(i = 0 ; i < n ; i++)
        for(j = 0 ; j < m ; j++)
            scanf("%d",&max[i][j]);
    
    //read available matrix
    printf("\nEnter the available matrix\n");
    for(i = 0 ; i < m ; i++)
        scanf("%d",&avail[i]);
    
    int finish[n], safeseq[n], work[m], need[n][m];

    //copying the available resource info to work for temp calculation.
    for(i = 0 ; i < m ; i++)
    {
        work[i] = avail[i];
    }

    //initially setting status of finished process to 0.
    for(i = 0 ; i < n ; i++)
    {
            finish[i] = 0;
    }

    //NEED matrix calculation.
    for(i = 0; i < n ;i++)
        for(j = 0 ; j < m ; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    printf("\nNEED matrix\n");
    for(i = 0 ; i < n; i++)
    {
        for(j = 0 ; j < m ; j++)
            printf("%d  ",need[i][j]);
        printf("\n");
    } 
    
    for(i = 0 ; i < m ; i++)
        work[i] = avail[i];
    
    for(i = 0 ; i < n ; i++)
        finish[i] = 0;
    
    for( k = 0 ; k < n ; k++)
    {
        for(i = 0 ; i < n ; i++)
        {
            if(finish[i] == 0)
            {
                //check of the resource need against available(work).
                int flag = 0;
                for( j = 0 ; j < m ; j++)
                {
                    //if the need is > work ==> means we cant satisfy to indicate that we have flag set to 1.
                    //if not flag = 0.
                    //after an entire loop if the break statement is not executed means the need can be satisfied.
                    if(need[i][j] > work[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                //only reached here if the resource need <= available.
                //means the availability satisfies current process need.
                if(flag == 0)
                {
                    //add the process to safesequence.
                    safeseq[ind++] = i;

                    //add released reource instance to available(work).
                    for( int y = 0 ; y < m ; y++)
                        work[y] += alloc[i][j];
                    finish[i] = 1;
                }
            }
        }
   }

    printf("\nFollowing is the SAFE  sequence\n");
    printf("< ");
    for(i = 0 ; i < n ; i++)
        printf("P-%d  ", safeseq[i]);
    printf(">\n");

    //resource allocation algorithm
    //predicting if the deaklock occurs or not.
    int pid;
    printf("\nEnter the request process no : ");
    scanf("%d",&pid);

    //read the request.
    int request[m];
    for(int i = 0 ; i < m ; i++)
    {
        scanf("%d",&request[i]);
    }

    //check the request exceeds the need.
    //if yes terminate.
    //if not continue => means it is eligible for the safesequence check.
    int flag_r = 0;
    for(i = 0 ; i < m ; i++ )
    {
        if(request[i] > need[pid][i])
        {
            flag_r = 1;
            break;
        }
    }

    if(flag_r == 0)
    {
        //check for safesequence.
        int result = SafeSequenceCheck(need, request, n, m , pid);

        if(result == 1)
        {
            printf("permission grnated!");
        }
        else{
            printf("permission not granted");
        }
    }

    return 0;
}