#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int contains(char *sym);
int allocReg(char *sym);
char *getOp(char op);

typedef struct
{
    char lhs[10];
    char rhs[10];
} codetab;

typedef struct
{
    char sym[10];
} regtab;

char as_code[10][20] = {'\0'};
regtab registers[10] = {'\0'};
codetab codes[10] = {'\0'};
int reg_ct = 0;
int code_ct = 0;
int as_ct = 0;
char temp[10] = {'\0'};

int contains(char *sym)
{
    for (int i = 0; i < reg_ct; i++)
    {
        if (strcmp(sym, registers[i].sym) == 0)
        {
            return i;
        }
    }
    return -1;
}

int allocReg(char *sym)
{
    strcpy(registers[reg_ct++].sym, sym);
    return reg_ct - 1;
}

char *getStrReg(int reg)
{
    bzero(temp, sizeof(temp));
    char a = (char)(reg + 48);
    strcat(temp, "R");
    strncat(temp, &a, 1);
    return temp;
}
char *getOp(char op)
{
    switch (op)
    {
    case '+':
        return "ADD";
    case '-':
        return "SUB";
    case '*':
        return "MUL";
    case '/':
        return "DIV";
    default:
        return NULL;
    }
}
// int getValue(char *code)
// {
//     char op[2][10], opn;
//     int ix = 0;
//     int opval[2];

//     char str[10] = {'\0'};
//     for (int i = 0; i <= strlen(code); i++)
//     {
//         if (i != strlen(code))
//         {
//             if (code[i] != '+' && code[i] != '-' && code[i] != '*' && code[i] != '/')
//             {
//                 strncat(str, &code[i], 1);
//             }
//             else
//             {
//                 opn = code[i];
//                 if (ix == 2)
//                 {
//                     return -1;
//                 }
//                 strcpy(op[ix], str);
//                 bzero(str, sizeof(str));
//                 ix++;
//             }
//         }
//         else
//         {
//             if (ix == 2)
//             {
//                 return -1;
//             }
//             strcpy(op[ix], str);
//             bzero(str, sizeof(str));
//             ix++;
//         }
//     }
//     // printf("%s %c %s\n", op[0], opn, op[1]);
//     for (int i = 0; i < ix; i++)
//     {
//         int flag = 0;
//         for (int j = 0; j < strlen(op[i]); j++)
//         {
//             if (!(op[i][j] >= 48 && op[i][j] <= 57))
//             {
//                 flag = 1;
//             }
//         }
//         if (flag == 0)
//         {
//             opval[i] = atoi(op[i]);
//         }
//         else
//         {
//             opval[i] = registers[contains(op[i])].value;
//         }
//     }
//     if (ix == 1)
//     {
//         // printf("Values for %s are %d\n", code, opval[0]);
//         return opval[0];
//     }
//     else
//     {
//         switch (opn)
//         {
//         case '+':
//             return opval[0] + opval[1];
//         case '*':
//             return opval[0] * opval[1];
//         case '/':
//             return opval[0] / opval[1];
//         case '-':
//             return opval[0] - opval[1];
//         default:
//             return -1;
//         }
//     }
// }

void main()
{
    printf("Enter the number of equations\n");
    scanf("%d", &code_ct);
    printf("Enter equations\n");
    for (int i = 0; i < code_ct; i++)
    {
        scanf("%s = %s", codes[i].lhs, codes[i].rhs);
    }
    char str[10] = {'\0'};
    for (int i = 0; i < code_ct; i++)
    {
        strcpy(str, codes[i].rhs);
        char op[10] = {'\0'};
        // for (int j = 0; j <= strlen(codes[i].rhs); j++)
        // {

        // }
        int reg_no, reg_no2;
        if ((reg_no = contains(&str[0])) < 0)
        {
            reg_no = allocReg(&str[0]);
            strcat(as_code[as_ct], "MOV ");
            strcat(as_code[as_ct], getStrReg(reg_no));
            strcat(as_code[as_ct], ",");
            strncat(as_code[as_ct++], &str[0], 1);
        }

        if (strlen(codes[i].rhs) == 1)
        {
            strcat(as_code[as_ct], "MOV ");
            allocReg(&codes[i].lhs[0]);
            strcat(as_code[as_ct], &codes[i].lhs[0]);
            strcat(as_code[as_ct], ",");
            strcat(as_code[as_ct++], getStrReg(reg_no));
        }
        else
        {
            strcpy(op, getOp(str[1]));
            if ((reg_no2 = contains(&str[2])) < 0)
            {
                reg_no2 = allocReg(&str[0]);
                strcat(as_code[as_ct], "MOV ");
                strcat(as_code[as_ct], getStrReg(reg_no2));
                strcat(as_code[as_ct], ",");
                strncat(as_code[as_ct++], &str[2], 1);
            }
            strcat(as_code[as_ct], getOp(str[1]));
            strcat(as_code[as_ct], " ");
            strcat(as_code[as_ct], getStrReg(reg_no));
            strcat(as_code[as_ct], ",");
            strcat(as_code[as_ct++], getStrReg(reg_no2));
            strcat(as_code[as_ct], "MOV ");
            allocReg(&codes[i].lhs[0]);
            strcat(as_code[as_ct], &codes[i].lhs[0]);
            strcat(as_code[as_ct], ",");
            strcat(as_code[as_ct++], getStrReg(reg_no));
        }
    }
    printf("8086 Instructions\n");
    for (int i = 0; i < as_ct; i++)
    {
        printf("%s\n", as_code[i]);
    }
}
