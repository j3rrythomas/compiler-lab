// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// char lhs[10] = {'\0'};
// // char glob_res[40] = {'\0'};
// char res[100][10] = {'\0'};
// int res_ct = 0;
// // char first[10][10] = {'\0'};

// char glob_rhs[10][10][10] = {'\0'};
// int ct = 0;

// int ret_index_lhs(char ch);
// char *extract(char lh, char *rh);

// void main()
// {
//     int tml_ct, non_tml_ct;
//     char tmls[10] = {'\0'}, non_tmls[10] = {'\0'};
//     char rhs[10][10][10] = {'\0'};
//     int first_ct[10] = {'\0'};

//     while (1)
//     {
//         int temp;
//         char *temp2;
//         printf("Enter LHS symbol\n");
//         scanf("%s", temp2);
//         lhs[ct] = temp2[0];
//         printf("Enter number of productions\n");
//         scanf("%d", &temp);
//         rhs[ct][0][0] = (char)(temp + 48);
//         for (int i = 1; i <= temp; i++)
//         {
//             char temp[10] = {'\0'};
//             printf("Enter production (# for epsilon)\n");
//             scanf("%s", temp);
//             memmove(rhs[ct][i], temp, strlen(temp));
//             // printf("%s %d %d\n", rhs[ct][i], ct, i);
//         }
//         ct++;

//         printf("Enter -1 to exit\n");
//         scanf("%d", &temp);
//         if (temp == -1)
//             break;
//     }
//     printf("Productions are\n");
//     for (int i = 0; i < ct; i++)
//     {
//         // printf("%s %d\n", rhs[i][0], i);
//         for (int j = 1; j <= (int)(rhs[i][0][0]) - 48; j++)
//         {
//             printf("%c -> %s\n", lhs[i], rhs[i][j]);
//         }
//     }

//     memcpy(glob_rhs, rhs, 1000);

//     for (int i = 0; i < ct; i++)
//     {
//         char first[20] = {'\0'};
//         for (int j = 1; j <= (int)(rhs[i][0][0]) - 48; j++)
//         {
//             char ch[10] = {'\0'};
//             memmove(ch, rhs[i][j], strlen(rhs[i][j]));
//             strcat(first, extract(lhs[i], ch));
//         }
//         printf("First of %c is {", lhs[i]);
//         for (int j = 0; j < strlen(first); j++)
//         {
//             printf("%c,", first[j]);
//         }
//         printf("\b}\n");
//     }

//     // for (int i = 0; i < ct; i++)
//     // {
//     //     printf("FIRST for %c is {", lhs[i]);

//     //     // printf("%s %d\n", rhs[i][0], i);
//     //     for (int j = 0; j < strlen(first[i]); j++)
//     //     {
//     //         printf("%c,", first[i][j]);
//     //     }
//     //     printf("}\n");
//     // }
// }

// int ret_index_lhs(char ch)
// {

//     for (int i = 0; i < ct; i++)
//     {
//         if (lhs[i] == ch)
//         {
//             return i;
//         }
//     }
//     return -1;
// }

// char *extract(char lh, char *rh)
// {
//     int index = res_ct;
//     // printf("Production %c->%s\n", lh, rh);
//     if (strlen(rh) < 0)
//         return "";
//     if (((rh[0] >= 97 && rh[0] <= 122) || (rh[0] >= 36 && rh[0] <= 57)) && strstr(res[index], &rh[0]) == NULL)
//     {
//         strncat(res[index], &rh[0], sizeof(char));
//     }
//     else if (rh[0] == '#')
//     {
//         if (strlen(rh) == 1 && strstr(res[index], &rh[0]) == NULL)
//         {
//             strncat(res[index], &rh[0], sizeof(char));
//         }
//         else
//         {
//             for (int k = 1; k < strlen(rh); k++)
//             {
//                 if (((rh[0] >= 97 && rh[0] <= 122) || (rh[0] >= 36 && rh[0] <= 57)) && strstr(res[index], &rh[k]) == NULL)
//                 {
//                     strncat(res[index], &rh[k], sizeof(char));
//                     break;
//                 }
//                 else if (rh[k] == '#')
//                 {
//                     if (k == strlen(rh) - 1 && strstr(res[index], &rh[k]) == NULL)
//                     {
//                         strncat(res[index], &rh[k], sizeof(char));
//                     }
//                     else
//                     {
//                         continue;
//                     }
//                 }
//                 else
//                 {
//                     char tempx[10];
//                     memmove(tempx, extract(lh, &rh[k]), strlen(extract(lh, &rh[k])));
//                     if (strstr(tempx, "#") == NULL)
//                     {
//                         for (int q = 0; q < strlen(tempx); q++)
//                         {
//                             if (strstr(res[index], &tempx[q]) == NULL)
//                             {
//                                 strncat(res[index], &tempx[q], sizeof(char));
//                             }
//                         }
//                         break;
//                     }
//                     else
//                     {
//                         for (int l = 0; l < strlen(tempx); l++)
//                         {
//                             if (tempx[l] != '#' && strstr(res[index], &tempx[l]) == NULL)
//                             {
//                                 strncat(res[index], &tempx[l], sizeof(char));
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     else
//     {
//         if (rh[0] != lh)
//         {
//             int idx = ret_index_lhs(rh[0]);
//             for (int p = 1; p <= (int)(glob_rhs[idx][0][0]) - 48; p++)
//             {
//                 // char temp_res[10] = {'\0'};
//                 char tempx[10] = {'\0'};
//                 memcpy(tempx, extract(rh[0], glob_rhs[idx][p]), strlen(extract(rh[0], glob_rhs[idx][p])));
//                 // printf("%c %s %s %s %d\n", lh, rh, tempx, res[index], p);
//                 if (strstr(tempx, "#") == NULL)
//                 {
//                     for (int q = 0; q < strlen(tempx); q++)
//                     {
//                         if (strstr(res[index], &tempx[q]) == NULL)
//                         {
//                             strncat(res[index], &tempx[q], sizeof(char));
//                         }
//                     }
//                     break;
//                 }
//                 else
//                 {
//                     printf("Else %s\n", rh);
//                     if (strlen(rh) == 1 && strstr(res[index], &rh[0]) == NULL)
//                     {
//                         strncat(res[index], &rh[0], sizeof(char));
//                     }
//                     else
//                     {
//                         for (int k = 1; k < strlen(rh); k++)
//                         {
//                             if (((rh[0] >= 97 && rh[0] <= 122) || (rh[0] >= 36 && rh[0] <= 57)) && strstr(res[index], &rh[k]) == NULL)
//                             {
//                                 strncat(res[index], &rh[k], sizeof(char));
//                                 break;
//                             }
//                             else if (rh[k] == '#')
//                             {
//                                 if (k == strlen(rh) - 1 && strstr(res[index], &rh[k]) == NULL)
//                                 {
//                                     strncat(res[index], &rh[k], sizeof(char));
//                                 }
//                                 else
//                                 {
//                                     continue;
//                                 }
//                             }
//                             else
//                             {
//                                 char tempx[10];
//                                 memmove(tempx, extract(lh, &rh[k]), strlen(extract(lh, &rh[k])));
//                                 if (strstr(tempx, "#") == NULL)
//                                 {
//                                     for (int q = 0; q < strlen(tempx); q++)
//                                     {
//                                         if (strstr(res[index], &tempx[q]) == NULL)
//                                         {
//                                             strncat(res[index], &tempx[q], sizeof(char));
//                                         }
//                                     }
//                                     break;
//                                 }
//                                 else
//                                 {
//                                     for (int l = 0; l < strlen(tempx); l++)
//                                     {
//                                         if (tempx[l] != '#' && strstr(res[index], &tempx[l]) == NULL)
//                                         {
//                                             strncat(res[index], &tempx[l], sizeof(char));
//                                         }
//                                     }
//                                 }
//                             }
//                         }
//                     }
//                 }
//                 // for (int q = 0; q < strlen(tempx); q++)
//                 // {
//                 //     // printf("%c %s\n", tempx[q], strstr(res[index], &tempx[q]));
//                 //     if (strstr(res[index], &tempx[q]) == NULL)
//                 //     {
//                 //         // printf("%c %c %s\n", lh, tempx[q], glob_rhs[idx][p]);
//                 //         strncat(res[index], &tempx[q], sizeof(char));
//                 //         // printf("%s\n", res[index]);
//                 //     }
//                 // }
//             }
//         }
//     }
//     int idx = ret_index_lhs(lh);
//     // printf("%s\n", res[index]);
//     res_ct++;
//     return res[index];
// }

// //         // if (ch[0] >= 97 && ch[0] <= 122)
// //         // {
// //         //     first[i][first_ct[i]++] = ch[0];
// //         // }
// //         // else if (ch[0] == '#')
// //         // {
// //         //     if (strlen(ch) == 1)
// //         //     {
// //         //         first[i][first_ct[i]++] = ch[0];
// //         //     }
// //         //     else
// //         //     {
// //         //         for (int k = 1; k < strlen(ch); k++)
// //         //         {
// //         //             if (ch[k] >= 97 && ch[k] <= 122)
// //         //             {
// //         //                 first[i][first_ct[i]++] = ch[k];
// //         //                 break;
// //         //             }
// //         //             else if (ch[k] == '#')
// //         //             {
// //         //                 continue;
// //         //             }
// //         //             else{
// //         //                 if(strstr(extract))
// //         //             }
// //         //         }
// //         //     }
// //         // }
// //         // else
// //         // {
// //         //     extract
// //         // }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct prod
{
    char lhs[10];
    char rhs[10];
} prod;

typedef struct firstStruct
{
    char arr[10];
    int count;
} firstStruct;

typedef struct followStruct
{
    char arr[10];
    int count;
} followStruct;

int n, nTemp;
prod grammar[30];
prod grammarTemp[30];
char temps[] = "PQRUVWXYZ";
int tempIndex = 0;

int contains(firstStruct *f, char c)
{
    for (int i = 0; i < f->count; i++)
    {
        if (f->arr[i] == c)
            return 1;
    }

    return 0;
}

firstStruct *first(char c)
{
    firstStruct *f = (firstStruct *)malloc(sizeof(firstStruct));
    f->count = 0;
    int flag;

    for (int i = 0; i < n; i++)
    {
        if (grammar[i].lhs[0] == c)
        {
            if (grammar[i].rhs[0] >= 'A' && grammar[i].rhs[0] <= 'Z')
            { 
                for (int j = 0;; j++)
                {
                    if (grammar[i].rhs[j] == '\0')
                    {
                        break;
                    }

                    if (grammar[i].rhs[j] < 'A' || grammar[i].rhs[j] > 'Z')
                    {
                        f->arr[f->count++] = grammar[i].rhs[j];
                        break;
                    }

                    firstStruct *f1 = first(grammar[i].rhs[j]);

                    if (contains(f1, 'e'))
                    {
                        for (int k = 0; k < f1->count; k++)
                        {
                            if (f1->arr[k] == 'e')
                                continue;

                            flag = 0;

                            for (int l = 0; l < f->count; l++)
                            {
                                if (f->arr[l] == f1->arr[k])
                                {
                                    flag = 1;
                                }
                            }

                            if (!flag)
                                f->arr[f->count++] = f1->arr[k];
                        }

                        if (grammar[i].rhs[j + 1] == '\0')
                        {
                            f->arr[f->count++] = 'e';
                            break;
                        }

                        continue;
                    }
                    else
                    {
                        for (int k = 0; k < f1->count; k++)
                        {
                            flag = 0;

                            for (int l = 0; l < f->count; l++)
                            {
                                if (f->arr[l] == f1->arr[k])
                                {
                                    flag = 1;
                                }
                            }

                            if (!flag)
                                f->arr[f->count++] = f1->arr[k];
                        }

                        break;
                    }
                }
            }
            else
            { 
                flag = 0;
                for (int j = 0; j < f->count; j++)
                {
                    if (f->arr[j] == grammar[i].rhs[0])
                    {
                        flag = 1;
                    }
                }

                if (!flag)
                    f->arr[f->count++] = grammar[i].rhs[0];
            }
        }
    }

    return f;
}

followStruct *follow(char c)
{
    followStruct *f = (followStruct *)malloc(sizeof(followStruct));
    int flag;

    if (grammarTemp[0].lhs[0] == c)
    {
        f->arr[f->count++] = '$';
    }

    for (int i = 0; i < nTemp; i++)
    {
        for (int j = 0;; j++)
        {
            flag = 0;

            if (grammarTemp[i].rhs[j] == '\0')
                break;

            if (grammarTemp[i].rhs[j] == c)
            {
                if (grammarTemp[i].rhs[j + 1] == '\0')
                {
                    if (grammarTemp[i].lhs[0] == c)
                        break;

                    followStruct *f2 = follow(grammarTemp[i].lhs[0]);

                    for (int k = 0; k < f2->count; k++)
                    {
                        flag = 0;

                        for (int l = 0; l < f->count; l++)
                        {
                            if (f->arr[l] == f2->arr[k])
                            {
                                flag = 1;
                            }
                        }

                        if (!flag)
                        {
                            f->arr[f->count++] = f2->arr[k];
                        }
                    }
                }
                else if (grammarTemp[i].rhs[j + 1] >= 'A' && grammarTemp[i].rhs[j + 1] <= 'Z')
                {
                    firstStruct *f1 = first(grammarTemp[i].rhs[j + 1]);

                    int m = 2;

                    while (grammarTemp[i].rhs[j + m] != '\0' && contains(f1, 'e'))
                    {
                        for (int k = 0; k < f1->count; k++)
                        {
                            if (f1->arr[k] == 'e')
                                continue;

                            flag = 0;

                            for (int l = 0; l < f->count; l++)
                            {
                                if (f->arr[l] == f1->arr[k])
                                {
                                    flag = 1;
                                }
                            }

                            if (!flag)
                            {
                                f->arr[f->count++] = f1->arr[k];
                            }
                        }

                        flag = 0;

                        if (grammarTemp[i].rhs[j + m] >= 'A' && grammarTemp[i].rhs[j + m] <= 'Z')
                        {
                            f1 = first(grammarTemp[i].rhs[j + m]);
                            m++;
                        }
                        else
                        {
                            f->arr[f->count++] = grammarTemp[i].rhs[j + m];
                            flag = 1;
                            break;
                        }
                    }

                    if (!flag)
                    {
                        for (int k = 0; k < f1->count; k++)
                        {
                            if (f1->arr[k] == 'e')
                                continue;

                            flag = 0;

                            for (int l = 0; l < f->count; l++)
                            {
                                if (f->arr[l] == f1->arr[k])
                                {
                                    flag = 1;
                                }
                            }

                            if (!flag)
                            {
                                f->arr[f->count++] = f1->arr[k];
                            }
                        }

                        if (grammarTemp[i].rhs[j + m] == '\0')
                        {
                            if (grammarTemp[i].lhs[0] == c)
                                break;

                            followStruct *f2 = follow(grammarTemp[i].lhs[0]);

                            for (int k = 0; k < f2->count; k++)
                            {
                                flag = 0;

                                for (int l = 0; l < f->count; l++)
                                {
                                    if (f->arr[l] == f2->arr[k])
                                    {
                                        flag = 1;
                                    }
                                }

                                if (!flag)
                                {
                                    f->arr[f->count++] = f2->arr[k];
                                }
                            }
                        }
                    }
                }
                else
                {
                    f->arr[f->count++] = grammarTemp[i].rhs[j + 1];
                }
            }
        }
    }

    return f;
}

void main()
{
    int t1 = 0, t2 = 0;
    char non_terminals[10];
    char terminals[10];

    printf("Enter the number of productions: ");
    scanf("%d", &n);
    nTemp = n;

    for (int i = 0; i < n; i++)
    {
        scanf("%s -> %s", grammar[i].lhs, grammar[i].rhs);
        strcpy(grammarTemp[i].lhs, grammar[i].lhs);
        strcpy(grammarTemp[i].rhs, grammar[i].rhs);
    }

    int flag;

    for (int i = 0; i < n; i++)
    {
        flag = 0;

        for (int j = 0; j < t1; j++)
        {
            if (non_terminals[j] == grammar[i].lhs[0])
                flag = 1;
        }

        if (!flag)
        {
            non_terminals[t1++] = grammar[i].lhs[0];
        }

        for (int j = 0;; j++)
        {
            if (grammar[i].rhs[j] == '\0')
                break;
            else if (grammar[i].rhs[j] >= 'A' && grammar[i].rhs[j] <= 'Z')
            {
                flag = 0;

                for (int k = 0; k < t1; k++)
                {
                    if (non_terminals[k] == grammar[i].rhs[j])
                        flag = 1;
                }

                if (!flag)
                {
                    non_terminals[t1++] = grammar[i].rhs[j];
                }

                continue;
            }

            flag = 0;

            for (int k = 0; k < t2; k++)
            {
                if (terminals[k] == grammar[i].rhs[j])
                    flag = 1;
            }

            if (!flag)
            {
                terminals[t2++] = grammar[i].rhs[j];
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (grammar[i].lhs[0] == grammar[i].rhs[0])
        {
            for (int j = 0;; j++)
            {
                if (grammar[i].rhs[j + 1] == '\0')
                {
                    grammar[i].rhs[j] = temps[tempIndex];
                    break;
                }

                grammar[i].rhs[j] = grammar[i].rhs[j + 1];
            }

            for (int j = 0; j < n; j++)
            {
                if (j == i)
                    continue;

                if (grammar[j].lhs[0] == grammar[i].lhs[0])
                {
                    for (int k = 0;; k++)
                    {
                        if (grammar[j].rhs[k] == '\0')
                        {
                            grammar[j].rhs[k] = temps[tempIndex];
                            grammar[j].rhs[k + 1] = '\0';
                            break;
                        }
                    }
                }
            }

            grammar[i].lhs[0] = temps[tempIndex];
            grammar[n].lhs[0] = temps[tempIndex];
            grammar[n].lhs[1] = '\0';
            grammar[n].rhs[0] = 'e';
            grammar[n].rhs[1] = '\0';
            n++;
            tempIndex++;
        }
    }

    firstStruct *f;

    printf("\n");
    for (int i = 0; i < t1; i++)
    {
        printf("FIRST(%c):", non_terminals[i]);

        f = first(non_terminals[i]);

        for (int j = 0; j < f->count; j++)
        {
            printf(" %c", f->arr[j]);
        }

        printf("\n");
    }

    printf("\n");
}