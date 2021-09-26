#include <stdio.h>
#include "errors.h"
#include "label.h"
#include "register.h"
#include "AST.h"
#include "ASTPrintTree.h"
#include "AAT.h"
#include "AATPrintTree.h"
#include "semantic.h"
#include "codegen.h"

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
  FILE *output;
  char *outfilename;
  
  ASTprogram program;
  AATstatement assem;
  if (argc!=2) {
    fprintf(stderr,"usage: %s filename\n",argv[0]); 
    exit(1);
  }
  outfilename = (char *) malloc((strlen(argv[1]) + 3) * sizeof(char));
  strcpy(outfilename,argv[1]);
  strcat(outfilename,".s");
  
  program = parse(argv[1]);
  if (program != NULL) {
    printf("Abstract Syntax Tree\n");
    printf("--------------------\n");
    printAST(program);
    assem = analyzeProgram(program);
    if (!anyErrors()) {
      printf("\nAbstract Assembly Tree\n");
      printf("----------------------\n");
      printAAT(assem);
      output = fopen(outfilename, "w");
      generateCode(assem, output);
    } else {
      printf("# of errors = %d",numErrors());
    }
 }
 
 return 0;
}

