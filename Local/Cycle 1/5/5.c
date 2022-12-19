#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int states, syms, init_state, fin_st_ct, fin_states[10] = {'\0'}, st_tb[10][10] = {'\0'}, new_states[10] = {'\0'}, trans[10][10] = {'\0'};
    printf("Enter the number of states\n");
    scanf("%d", &states);
    printf("Enter the number of symbols\n");
    scanf("%d", &syms);
    printf("Enter the initial state\n");
    scanf("%d", &init_state);
    printf("Enter the number of final states\n");
    scanf("%d", &fin_st_ct);
    for (int i = 0; i < fin_st_ct; i++)
    {
        int k;
        printf("Enter final state\n");
        scanf("%d", &k);
        fin_states[k] = 1;
    }
    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < syms; j++)
        {
            printf("Enter transition from state %d for symbol %d\n", i, j);
            scanf("%d", &trans[i][j]);
        }
    }

    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < states; j++)
        {
            if (fin_states[j] == 1 && fin_states[i] != 1)
            {
                st_tb[i][j] = 1;
            }
            if (fin_states[i] == 1 && fin_states[j] != 1)
            {
                st_tb[i][j] = 1;
            }
        }
    }
    int count;
    do
    {
        count = 0;
        for (int i = 0; i < states; i++)
        {
            for (int j = 0; j < states; j++)
            {
                if (st_tb[i][j] != 1)
                {
                    for (int k = 0; k < syms; k++)
                    {
                        if (st_tb[trans[i][k]][trans[j][k]] == 1)
                        {
                            count++;
                            st_tb[i][j] = 1;
                        }
                    }
                }
            }
        }
    } while (count != 0);

    for (int i = 0; i < states; i++)
    {
        for (int j = i+1; j < states; j++)
        {
            if (st_tb[i][j] == 0)
            {
                printf("States %d %d to be combined\n", i, j);
            }
        }
    }
}