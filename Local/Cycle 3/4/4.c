#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct
{
    char lhs[10];
    char rhs[10];
} codetab;

typedef struct
{
    char sym[10];
    int value;
} symtab;

symtab symbols[10] = {'\0'};
codetab codes[10] = {'\0'};
int sym_ct = 0;
int code_ct = 0;

int contains(char *sym);
int isConstant(char *code);
int getValue(char *code);

int contains(char *sym)
{
    for (int i = 0; i < sym_ct; i++)
    {
        if (strcmp(sym, symbols[i].sym) == 0)
        {
            return i;
        }
    }
    return -1;
}

int isConstant(char *code)
{
    regex_t regex1, regex2;
    if (regcomp(&regex1, "^[0-9][0-9]*[+-/*][0-9][0-9]*$", 0) != 0)
    {
        printf("Regex compilation failed\n");
        exit(1);
    };

    if (regexec(&regex1, code, 0, NULL, 0) == 0)
    {
        return 1;
    }

    if (regcomp(&regex2, "^[0-9][0-9]*$", 0) != 0)
    {
        printf("Regex compilation failed\n");
        exit(1);
    };

    if (regexec(&regex2, code, 0, NULL, 0) == 0)
    {
        return 1;
    }

    char str[10] = {'\0'};
    for (int i = 0; i < strlen(code); i++)
    {
        if (code[i] != '+' && code[i] != '-' && code[i] != '*' && code[i] != '/')
        {
            strncat(str, &code[i], 1);
        }
        else
        {
            if (contains(str) >= 0)
            {
                bzero(str, sizeof(str));
            }
            else
            {
                return 0;
            }
        }
    }
    if (contains(str) >= 0)
    {
        return 1;
    }
    return 0;
}

int getValue(char *code)
{
    char op[2][10], opn;
    int ix = 0;
    int opval[2];

    char str[10] = {'\0'};
    for (int i = 0; i <= strlen(code); i++)
    {
        if (i != strlen(code))
        {
            if (code[i] != '+' && code[i] != '-' && code[i] != '*' && code[i] != '/')
            {
                strncat(str, &code[i], 1);
            }
            else
            {
                opn = code[i];
                if (ix == 2)
                {
                    return -1;
                }
                strcpy(op[ix], str);
                bzero(str, sizeof(str));
                ix++;
            }
        }
        else
        {
            if (ix == 2)
            {
                return -1;
            }
            strcpy(op[ix], str);
            bzero(str, sizeof(str));
            ix++;
        }
    }
    // printf("%s %c %s\n", op[0], opn, op[1]);
    for (int i = 0; i < ix; i++)
    {
        int flag = 0;
        for (int j = 0; j < strlen(op[i]); j++)
        {
            if (!(op[i][j] >= 48 && op[i][j] <= 57))
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            opval[i] = atoi(op[i]);
        }
        else
        {
            opval[i] = symbols[contains(op[i])].value;
        }
    }
    if (ix == 1)
    {
        // printf("Values for %s are %d\n", code, opval[0]);
        return opval[0];
    }
    else
    {
        switch (opn)
        {
        case '+':
            return opval[0] + opval[1];
        case '*':
            return opval[0] * opval[1];
        case '/':
            return opval[0] / opval[1];
        case '-':
            return opval[0] - opval[1];
        default:
            return -1;
        }
    }
}

void main()
{
    printf("Enter the number of equations\n");
    scanf("%d", &code_ct);
    printf("Enter equations\n");
    for (int i = 0; i < code_ct; i++)
    {
        scanf("%s = %s", codes[i].lhs, codes[i].rhs);
    }
    for (int i = 0; i < code_ct; i++)
    {
        if (isConstant(codes[i].rhs))
        {
            printf("%s\n", codes[i].rhs);
            strcpy(symbols[sym_ct].sym, codes[i].lhs);
            int val = getValue(codes[i].rhs);
            if (val == -1)
            {
                printf("Error trying to get value\n");
                exit(1);
            }
            // printf("%s %s : %d\n", codes[i].lhs, codes[i].rhs, val);
            symbols[sym_ct++].value = val;
        }
    }
    printf("SYMBOL TABLE\n");
    for (int i = 0; i < sym_ct; i++)
    {
        printf("%s : %d\n", symbols[i].sym, symbols[i].value);
    }
}
