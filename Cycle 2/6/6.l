%{
    #include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]*    return id;

.                      return yytext[0];

\n                     return 0;

%%

int yywrap(){
    return 1;
}