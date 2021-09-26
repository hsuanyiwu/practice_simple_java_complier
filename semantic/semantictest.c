#include <stdio.h>
#include "errors.h"
#include "AST.h"
#include "ASTPrintTree.h"
#include "semantic.h"

extern int yyparse(void);
extern FILE *yyin;

ASTprogram parse(char *filename) {
  yyin = fopen(filename,"r");
  if (yyin == NULL) {
    fprintf(stderr,"Cannot open file:%s\n",filename);
  }
  if  (yyin != NULL && yyparse() == 0)  { /* parsing worked */
    return ASTroot;
  } else { 
    fprintf(stderr,"Parsing failed\n");
    return NULL;
  }
}


int main(int argc, char **argv) {
  ASTprogram program;
 if (argc!=2) {
   fprintf(stderr,"usage: %s filename\n",argv[0]); 
   exit(1);
 }
 program = parse(argv[1]);
 if (program != NULL) {
   printTree(program);
   analyzeProgram(program);
 }
 
 return 0;
}

