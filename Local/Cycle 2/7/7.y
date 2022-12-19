%{

    #include<stdio.h>

    int valid=1;   

%}

%token id num;
%start S

%%

S : id '=' E ';'     {printf("Output %d",$3);}

E :     E '+' T    {$$=$1+$3;}
    |   E '-' T     {$$=$1-$3;}
    | T              {$$=$1;}
    ;

T :     T '*' F    {$$=$1*$3;}
 |   T '/' F     {$$=$1/$3;}
    | F                {$$=$1;}
    ;

F :     '(' E ')'      {$$=$2;}
      |  num           {$$=$1;}

      ;

%%

int yyerror() {
    valid=0;
    return 0;
}

int main() {
    printf("Enter the expression:\n");
    yyparse();
    if(valid) {
        printf("\nValid expression.\n");
    }
    else {
        printf("\nInvalid Expression\n");
    }
}