%{
#include <string.h>
#include "..\errors.h"
//#include "tokens.h"
#include "ast.h"
#include "y.tab.h"

int current_line = 1;
int current_colunm = 1;
static int comment=0;
  
int yywrap(void) {
  return 1;
}

static void newline() {
  current_line++;
  current_colunm = 1;
}

static struct position new_pos() {
  struct position p = { current_line, current_colunm };
  current_colunm += yyleng;
  return p;
}

static void pos() {
  yylval.pos = new_pos();
}

static void val_int() {
  yylval.integer_value.pos = new_pos();  
  yylval.integer_value.value=atoi(yytext);
}

static void val_str() {
  yylval.string_value.pos = new_pos();  
  yylval.string_value.value = malloc(yyleng+1);
  strcpy(yylval.string_value.value, yytext);
}

%}

%x COMMENT

%%

"/*"      { BEGIN(COMMENT); comment=1; }
<COMMENT>"/*" { ++comment; }
<COMMENT>"*/" { if(--comment==0) BEGIN(INITIAL); }
<COMMENT>.    { }
<COMMENT>\n   { newline(); }

" "       { current_colunm+=1; }
"\t"      { current_colunm+=4; }
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
"-"       { pos(); return MINUS; }
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
"="       { pos(); return ASSIGN; }
"&&"      { pos(); return AND; }
"||"      { pos(); return OR; }
"!"       { pos(); return NOT; }
"++"      { pos(); return PLUSPLUS; }
"--"      { pos(); return MINUSMINUS; }
return    { pos(); return RETURN; }
new       { pos(); return NEW; }

[a-zA-Z_][a-zA-Z0-9_]*  { val_str(); return IDENTIFIER; }
0|[1-9][0-9]*           { val_int(); return INTEGER_LITERAL; }
.         { current_colunm+=1;  }

%%


     


