#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(char *str);
int parse(char *str);
char *strrev(char *str);

typedef struct
{
    char lhs[10];
    char rhs[10];
} prod;

prod prods[10];
int prod_ct, ip_ptr = 0, top = 0;
char ip_buf[20] = {'\0'}, stack[20] = {'\0'};

void main()
{
    char str[20] = {'\0'};
    printf("Enter number of productions\n");
    scanf("%d", &prod_ct);
    for (int i = 0; i < prod_ct; i++)
    {
        printf("Enter LHS and RHS\n");
        scanf("%s -> %s", prods[i].lhs, prods[i].rhs);
    }

    // for (int i = 0; i < prod_ct; i++)
    // {
    //     printf("%s -> %s\n", prods[i].lhs, prods[i].rhs);
    // }

    stack[top] = '$';
    printf("Enter string\n");
    scanf("%s", str);
    strncat(ip_buf, str, strlen(str));
    ip_buf[strlen(str)] = '$';
    stack[++top] = ip_buf[ip_ptr++];

    int op = parse(str);
    if (op == 1)
    {
        printf("String parsed\n");
    }
    else if (op == 0)
    {
        printf("String not parsed\n");
    }
    else
    {
        printf("Conflict occurred\n");
    }
}

int match(char *ip)
{
    for (int i = 0; i < prod_ct; i++)
    {
        if (strcmp(ip, prods[i].rhs) == 0)
        {
            return i;
        }
    }
    return -1;
}

int parse(char *str)
{
    printf("%s     %s(%d)\n", stack, ip_buf, ip_ptr);

    if (strcmp(str, "e") == 0)
    {
        for (int i = 0; i < prod_ct; i++)
        {
            if (strcmp(prods[i].rhs, "e") == 0 && strcmp(prods[0].lhs, prods[i].lhs) == 0)
            {
                return 1;
            }
        }
    }
    int tot_flag;
    while (1)
    {
        tot_flag=0;
        printf("%s(%d)     %s(%d)\n", stack, top, ip_buf, ip_ptr);
        if (stack[top] == prods[0].lhs[0] && ip_buf[ip_ptr] == '$' && top == 1)
        {
            return 1;
        }
        else if (ip_ptr > strlen(str))
            return 0;
        char temp[10] = {'\0'};
        int flag = 0;
        for (int i = top; i >= 1; i--)
        {
            if (flag == 1)
                break;
            strncat(temp, &stack[i], 1);
            // printf("%s \n", temp);

            int idx = match(strrev(temp));
            if (idx > -1)
            {
                flag = 1;
                if (ip_buf[ip_ptr] != '$')
                {
                    char temp2[10] = {'\0'};
                    strcat(temp2, temp);
                    strncat(temp2, &ip_buf[ip_ptr], 1);
                    // printf("%s %s \n", strrev(temp), temp2);
                    if (match(temp2) > -1)
                    {
                        return -1;
                    }
                }
                for (int j = top; j >= i; j--)
                {
                    stack[j] = '\0';
                }
                top = i;
                stack[top] = prods[idx].lhs[0];
                tot_flag = 1;
            }
        }
        if (flag == 0)
        {
            if (ip_buf[ip_ptr] != '$')
            {
                stack[++top] = ip_buf[ip_ptr++];
                tot_flag = 1;
            }
        }

        printf("%s(%d)     %s(%d)\n", stack, top, ip_buf, ip_ptr);
        if (!tot_flag)
        {
            return 0;
        }
    }
    return 0;
}

char *strrev(char *str)
{
    char *p1, *p2;

    if (!str || !*str)
        return str;
    for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return str;
}
