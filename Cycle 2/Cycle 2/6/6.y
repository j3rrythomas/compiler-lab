%{
    #include <stdio.h>
    int valid = 1;
%}

%token id

%%

S : id; 

%%

int yyerror(){
    valid=0;
    return 0;
}

int main(){
    printf("Enter identifier\n");
    yyparse();
    if(valid){
        printf("Valid identifier\n");
    }
    else{
        printf("Invalid Identifier\n");
    }
    return 1;
}