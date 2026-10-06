%{
#include <stdio.h>
%}

%%

[ \t\n]+                    ;

"//".*                      ;

"/*"([^*]|\*+[^*/])*\*+"/"  ; 

"int"|"float"|"char"|"if"|"else"|"while"|"for"|"return"|"void"
                            { printf("Keyword: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*      { printf("Identifier: %s\n", yytext); }

[0-9]+(\.[0-9]+)?           { printf("Number: %s\n", yytext); }

"=="|"!="|"<="|">="|"++"|"--"
                            { printf("Operator: %s\n", yytext); }

"+"|"-"|"*"|"/"|"%"|"="|"<"|">"
                            { printf("Operator: %s\n", yytext); }

";"|","|"("|")"|"{"|"}"|"["|"]"
                            { printf("Symbol: %s\n", yytext); }

.                           { printf("Unknown: %s\n", yytext); }

%%

int main()
{
    printf("Enter source code (Ctrl+Z then Enter to stop):\n\n");
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}




/* 
 
 How to RUn 

  vi filename.l
  flex filename.l
  gcc lex.yy.c
  ./a.out
Enter input : code (press enter after writing code u will get ouput)
*/
