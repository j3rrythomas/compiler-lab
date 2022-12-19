#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[40] = {'\0'};
int str_idx;

int E();
int Ep();
int T();
int Tp();
int F();

void main()
{
    printf("Enter string to parse\n");
    scanf("%s", str);

    if (E() && str_idx == strlen(str))
    {
        printf("String parsed\n");
    }
    else
    {
        printf("String not parsed\n");
    }
}

int E()
{
    printf("E %s %d\n", str, str_idx);
    if (T())
    {
        if (Ep())
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

int Ep()
{
    printf("E' %s %d\n", str, str_idx);
    if (str[str_idx] == '+')
    {
        str_idx++;
        if (T())
        {
            if (Ep())
            {
                return 1;
            }
            return 0;
        }
        str_idx--;
        return 0;
    }
    // else if (str_idx == strlen(str))
    // {
    //     return 1;
    // }
    return 1;
}

int T()
{
    printf("T %s %d\n", str, str_idx);
    if (F())
    {
        if (Tp())
        {
            return 1;
        }
        return 0;
    }
    return 0;
}

int Tp()
{
    printf("T' %s %d\n", str, str_idx);
    if (str[str_idx] == '*')
    {
        str_idx++;
        if (F())
        {
            if (Tp())
            {
                return 1;
            }
            return 0;
        }
        str_idx--;
        return 0;
    }
    // else if (str_idx == strlen(str))
    // {
    //     return 1;
    // }
    return 1;
}

int F()
{
    printf("F %s %d\n", str, str_idx);
    if (str[str_idx] == '(')
    {
        str_idx++;
        if (E())
        {
            if (str[str_idx] == ')')
            {
                str_idx++;
                return 1;
            }
            return 0;
        }
        str_idx--;
        return 0;
    }

    else if (str[str_idx] == 'n')
    {
        str_idx++;
        return 1;
    }
    return 0;
}