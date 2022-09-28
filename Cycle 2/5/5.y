%{                          
    #include <stdio.h>           /* imports */
    #include <stdlib.h>  
    #include <ctype.h>                            
    int yylex(void);             /* function prototype */
    int yyerror();  
    int valid=1;
%}

%token num id op

%%

start : id '=' s ';'

s :     id x       

      | num x       

      | '-' num x   

      | '(' s ')' x 

      ;

x :     op s        

      | '-' s       

      |             

      ;

%%

int yyerror()

{

    valid=0;

    printf("\nInvalid expression!\n");

    return 0;

}

int main()

{

    printf("Enter the expression:\n");

    yyparse();

    if(valid)

    {

        printf("\nValid expression.\n");

    }

}
