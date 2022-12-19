#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
    int states, transitions[10][10][10] = {'\0'}, fin_states[10], fin_st_ct, etrans[10][10];
    printf("Enter number of states\n");
    scanf("%d", &states);
    printf("Enter number of final states\n");
    scanf("%d", &fin_st_ct);

    for (int i = 0; i < fin_st_ct; i++)
    {
        int fin_state;
        printf("Enter final state\n");
        scanf("%d", &fin_state);
        fin_states[fin_state] = 1;
    }

    int from, to, alph;
    do
    {
        printf("Enter from state,to state and transition symbol(9 for epsilon) or-1 to exit\n");
        scanf("%d", &from);
        if (from == -1)
            break;
        scanf("%d", &to);
        scanf("%d", &alph);
        transitions[from][alph][to] = 1;
        if (alph == 9)
        {
            etrans[from][to] = 1;
        }
    } while (1);

    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("\nTransitions for state %d for alphabet %d are ", i, j);
            for (int k = 0; k < states; k++)
            {
                if (transitions[i][j][k] == 1)
                {
                    printf("%d ", k);
                }
            }
        }
    }
    printf("\n");

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
    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < states; j++)
        {
            if (fin_states[i] == 1)
            {
                if (etrans[j][i] == 1)
                {
                    fin_states[j] = 1;
                }
            }

        }
    }
    printf("Final states\n");
    for (int i = 0; i < 10; i++)
    {
        if (fin_states[i] == 1)
        {
            printf("%d ", i);
        }
    }
    // do
    // {
    //     count = 0;
    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < states; j++)
        {
            if (etrans[i][j] == 1)
            {
                for (int k = 0; k < 9; k++)
                {

                    for (int l = 0; l < states; l++)
                    {
                        if (transitions[j][k][l] == 1)
                        {
                            // transitions[i][k][j] = 1;
                            // if (transitions[i][k][l] != 1)
                            // {
                            transitions[i][k][l] = 1;
                            // count++;
                            // }
                        }
                    }
                }
            }
        }
        for (int j = 0; j < 9; j++)
        {
            for (int k = 0; k < states; k++)
            {
                if (transitions[i][j][k] == 1)
                {
                    for (int l = 0; l < states; l++)
                    {
                        if (etrans[k][l] == 1)
                        {
                            transitions[i][j][l] = 1;
                        }
                    }
                }
            }
        }
    }
    // } while (count != 0);

    for (int i = 0; i < states; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            printf("\nTransitions for state %d for alphabet %d are ", i, j);
            for (int k = 0; k < states; k++)
            {
                if (transitions[i][j][k] == 1)
                {
                    printf("%d ", k);
                }
            }
        }
    }
    printf("\n");
}