#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void main()
{
    FILE *fp = fopen('lex.c', 'rb');
    char ch, str[100];
    while (fgetc(ch) != EOF)
    {
        strncat(str, &ch, 1);
        if (matchPattern(str) == NULL)
        {
            bzero(str, sizeof(str));
        }
        else
        {
            continue;
        }
    }
}

int isSync(char ch)
{
    if (ch == '}' || ch == ')' || ch == ']' || ch == '[' || ch == '(' || ch == '{' || ch == ';' || ch == ',')
    {
        return 1;
    }
    return 0;
}

int isOperator(char *ch)
{
    if ()
}