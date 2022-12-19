#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int states, etrans[10][10] = {'\0'}, i, j;
    char closures[10][10] = {'\0'};
    char clos[100];
    printf("Enter number of states\n");
    scanf("%d", &states);
    do
    {
        printf("Enter state from which epsilon transition arises(-1 if none)\n");
        scanf("%d", &i);
        if (i == -1)
            break;
        printf("Enter state to which epsilon transition points\n");
        scanf("%d", &j);
        etrans[i][j] = 1;
    } while (1);

    int count;
    do
    {
        count = 0;
        for (int k = 0; k < states; k++)
        {
            etrans[k][k] = 1;
            for (int l = 0; l < states; l++)
            {
                if (etrans[k][l] == 1)
                {
                    for (int m = 0; m < states; m++)
                    {
                        if (etrans[l][m] == 1)
                        {
                            if (etrans[k][m] != 1)
                            {
                                etrans[k][m] = 1;
                                count++;
                            }
                        }
                    }
                }
            }
        }
    } while (count != 0);

    for (int k = 0; k < states; k++)
    {
        for (int l = 0; l < states; l++)
        {
            printf("%d ", etrans[k][l]);
        }
        printf("\n");
    }

    for (int i = 0; i < states; i++)
    {
        printf("Closure of %d is ", i);
        for (int j = 0; j < states; j++)
        {
            if (etrans[i][j] == 1)
            {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}