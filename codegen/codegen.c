#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "label.h"
#include "register.h"
#include "MachineDependent.h"
#include "AAT.h"

FILE *outfile;

void generateStatement(AATstatement tree); 
void generateExpression(AATexpression tree);
void generateMove(AATstatement tree);
void generateMemoryExpression(AATexpression tree);

void emit(char *assem,...);
void emitLibrary(void);
void emitSetupCode(void);


void generateCode(AATstatement tree, FILE *output) {
  outfile = output; 
  emitSetupCode();
  generateStatement(tree);
  fprintf(output,"\n");
  emitLibrary();
}



void emit(char *assem,...) {
  va_list ap;
  if (assem[strlen(assem)-1] != ':') 
    fprintf(outfile,"\t");
 va_start(ap,assem);
  vfprintf(outfile, assem, ap);
  va_end(ap);
  fprintf(outfile,"\n");
}


void generateExpression(AATexpression tree) {
  switch (tree->kind) {
  case AAT_MEMORY:
    generateMemoryExpression(tree);
    break;
  case AAT_CONSTANT:
    emit("addi %s, %s, %d",Acc(),Zero(),tree->u.constant);
    break;
    /* More cases */
  }
}


void generateStatement(AATstatement tree) {

  switch (tree->kind) {
  case AAT_MOVE:
    generateMove(tree);
    break;
    /* more cases */
  }

}


void generateMove(AATstatement tree) {

  /* Generates inefficient assembly */

  if (tree->u.move.lhs->kind == AAT_REGISTER) {
    generateExpression(tree->u.move.rhs);
    emit("addi %s,%s,0 ",tree->u.move.lhs->u.reg,Acc());
  } else if (tree->u.move.lhs->kind == AAT_MEMORY) {
    generateExpression(tree->u.move.rhs)
    emit("sw %s, 0(%s)",Acc(),AccSP());
    emit("addi %s,%s,%d",AccSP(),AccSP(),0-WORDSIZE);
    generateExpression(tree->u.move.lhs->u.memory);
    emit("addi %s,%s,%d",AccSP(),AccSP(),WORDSIZE);    
    emit("lw %s,0(%s)" ,Tmp1(),AccSP());
    emit("sw %s,0(%s) ",Tmp1(),Acc());
  } else {
    fprintf(stderr,"Bad MOVE node -- LHS should be T_mem or T_register\n");
  }
}

void generateMemoryExpression(AATexpression tree) {
  /* generates inefficent code */
  generateExpression(tree->u.memory);
  emit("lw %s, 0(%s)", Acc(), Acc());
}

void emitSetupCode(void) {
  emit(".globl main");
  emit("main:");
  emit("addi %s,%s,0", AccSP(), SP());
  emit("addi %s, %s, %d", SP(), SP(), - WORDSIZE * STACKSIZE);
  emit("addi %s, %s, 0", Tmp1(), SP());
  emit("addi %s, %s, %d", Tmp1(), Tmp1(), - WORDSIZE * STACKSIZE);
  emit("la %s, HEAPPTR", Tmp2());
  emit("sw %s, 0(%s)", Tmp1(), Tmp2());
  emit("sw %s, %d(%s)", ReturnAddr() , WORDSIZE, SP());
  emit("jal main1");
  emit("lw %s,%d(%s)", ReturnAddr(), WORDSIZE, SP());
  emit("jr %s", ReturnAddr());
}

void emitLibrary() {
  emit("Print:");
  emit("lw $a0, 4(%s)",SP());
  emit("li $v0, 1");
  emit("syscall");
  emit("li $v0,4");
  emit("la $a0, sp");
  emit("syscall");
  emit("jr $ra");
  emit("Println:");
  emit("li $v0,4");
  emit("la $a0, cr");
  emit("syscall");
  emit("jr $ra");
  emit("Read:");
  emit("li $v0,5");
  emit("syscall");
  emit("jr $ra");
  emit("allocate:");
  emit("la %s, HEAPPTR", Tmp1()); 
  emit("lw %s, 0(%s)", Result(), Tmp1());
  emit("lw %s, %d(%s)", Tmp2(), WORDSIZE, SP());
  emit("sub %s, %s, %s", Tmp2(), Result(), Tmp2());
  emit("sw %s, 0(%s)", Tmp2(), Tmp1());
  emit("jr $ra");
  emit(".data");
  emit("cr:");
  emit(".asciiz \"\\n\"");
  emit("sp:");
  emit(".asciiz \" \"");
  emit("HEAPPTR:");
  emit(".word 0");
}
