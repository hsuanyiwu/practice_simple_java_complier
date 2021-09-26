%{
#include <string.h>
#include "errors.h"
#include "tokens.h"
  
int yywrap(void) {
  return 1;
}

void newline() {
  Current_Line++;
}

%}

%%
" "            { }
\n             { newline();}
class          { yylval.line_number = Current_Line;
                 return CLASS;}
%%


     


