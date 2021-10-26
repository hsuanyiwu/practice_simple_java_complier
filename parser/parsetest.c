#include <stdio.h>
#include <stdlib.h>
#include "..\errors.h"

extern int yyparse(void);
extern FILE *yyin;

void parse(char *filename) {
  yyin = fopen(filename,"r");
  if (yyin == NULL) {
    fprintf(stderr,"Could not open file:%s\n",filename);
  } else {
    
    if (yyparse() == 0) /* parsing worked */
      fprintf(stderr,"Parsing successful!\n");
    else 
      fprintf(stderr,"Parsing failed\n");
  }
}


int main(int argc, char **argv) {
 if (argc!=2) {
   fprintf(stderr,"usage: %s filename\n",argv[0]); 
   exit(1);
 }
 parse(argv[1]);
 return 0;
}
