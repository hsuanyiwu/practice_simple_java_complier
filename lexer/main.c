#include <stdio.h>
#include "tokens.h"
#include "errors.h"

extern FILE *yyin;
YYSTYPE yylval;
int yylex(void);

char *tokenNames[] = { "IDENTIFIER","INTEGER_LITERAL","CLASS","DO","ELSE",
		       "TRUE","FALSE","FOR","IF","WHILE","PLUS","MINUS", 
		       "MULTIPLY", "DIVIDE", "LBRACK","RBRACK", "LBRACE",
		       "RBRACE","LPAREN","RPAREN","DOT","COMMA","SEMICOLON",
		       "EQ","NEQ","LT","GT","LEQ","GEQ","GETS","AND","OR",
		       "NOT","PLUSPLUS","MINUSMINUS","RETURN","NEW" };

char *tokenName(int token) {
  if (token < 257 || token > 294)
    return "BAD TOKEN";
  else
    return tokenNames[token-257];
}

int main(int argc, char **argv) {
 char *filename; 
 int token;
 if (argc!=2) {
   fprintf(stderr,"usage: %s filename\n",argv[0]); 
   exit(1);
 }
 filename=argv[1];
 yyin = fopen(filename,"r");
 if (yyin == NULL) {
   fprintf(stderr,"Cannot open file:%s\n",filename);
 } else {
   for(;;) {
     token=yylex();
     if (token==0) break;
     switch(token) {
     case IDENTIFIER: 
       printf("line:%2d %15s  value = %s\n",
	      yylval.string_value.line_number, tokenName(token),
	      yylval.string_value.value);
       break;
     case INTEGER_LITERAL:
       printf("line:%2d %15s  value = %d\n",
	      yylval.integer_value.line_number,tokenName(token),
	      yylval.integer_value.value);
       break;
     default:
       printf("line:%2d %15s\n",yylval.line_number,tokenName(token));
     }
   }
 }
 return 0;
}








