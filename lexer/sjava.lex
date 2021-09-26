%{
#include <string.h>
#include "errors.h"
#include "tokens.h"

int current_colunm = 1;
int current_length = 0;
  
int yywrap(void) {
  return 1;
}

void newline() {
  current_line++;
  current_colunm = 1;
}

struct position _pos() {
  struct position p = { current_line, current_colunm };
  current_length = strlen(yytext);
  current_colunm += current_length;
  return p;
}

void pos() {
  yylval.pos = _pos();
}

void val_int() {
  yylval.integer_value.pos = _pos();  
  yylval.integer_value.value=atoi(yytext);
}

void val_str() {
  yylval.string_value.pos = _pos();  
  yylval.string_value.value = malloc(current_length+1);
  strcpy(yylval.string_value.value, yytext);
}

%}

%%

" "       { current_colunm+=1; }
\n        { newline();}

class     { pos(); return CLASS; }
do        { pos(); return DO; }
else      { pos(); return ELSE; }
true      { pos(); return TRUE; }
false     { pos(); return FALSE; }
for       { pos(); return FOR; }
if        { pos(); return IF; }
while     { pos(); return WHILE; }
"+"       { pos(); return PLUS; }
"*"       { pos(); return MULTIPLY; }
"/"       { pos(); return DIVIDE; }
"["       { pos(); return LBRACK; }
"]"       { pos(); return RBRACK; }
"{"       { pos(); return LBRACE; }
"}"       { pos(); return RBRACE; }
"("       { pos(); return LPAREN; }
")"       { pos(); return RPAREN; }
"."       { pos(); return DOT; }
","       { pos(); return COMMA; }
";"       { pos(); return SEMICOLON;}
"=="      { pos(); return EQ; }
"!="      { pos(); return NEQ; }
"<"       { pos(); return LT; }
">"       { pos(); return GT; }
"<="      { pos(); return LEQ; }
">="      { pos(); return GEQ; }
"="       { pos(); return GETS; }
"&&"      { pos(); return AND; }
"||"      { pos(); return OR; }
"!"       { pos(); return NOT; }
"++"      { pos(); return PLUSPLUS; }
"--"      { pos(); return MINUSMINUS; }
return    { pos(); return RETURN; }
new       { pos(); return NEW; }

[a-zA-Z_][a-zA-Z0-9_]*  { val_str(); return IDENTIFIER; }
[0-9]+                  { val_int(); return INTEGER_LITERAL; }


%%


     


