%{

typedef struct tree_t {
    struct tree_t **links;
    int nb_links;
    char* type; // the grammar rule
};

#define YYDEBUG 1
//int yydebug = 1;

tree_t *_C_treeRoot;
%}
%union tree_t

%start S

%token id

%%

S : E    { _C_treeRoot = &$1.t; }
    | hack;

E :     E '+' T    
    |   E '-' T     
    | T             
    ;

T :     T '*' F    
 |   T '/' F     
    | F               
    ;

F :     '(' E ')'      
      |  num           

      ;

hack:  {
    // called at each reduction in YYDEBUG mode
    #undef YY_SYMBOL_PRINT
    #define YY_SYMBOL_PRINT(A,B,C,D) \
        do { \
            int n = yyr2[yyn]; \
            int i; \
            yyval.t.nb_links = n; \
            yyval.t.links = malloc(sizeof *yyval.t.links * yyval.t.nb_links);\
            yyval.t.str = NULL; \
            yyval.t.type = yytname[yyr1[yyn]]; \
            for (i = 0; i < n; i++) { \
              yyval.t.links[i] = malloc(sizeof (YYSTYPE)); \
              memcpy(yyval.t.links[i], &yyvsp[(i + 1) - n], sizeof(YYSTYPE)); \
            } \
        } while (0)

    }
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