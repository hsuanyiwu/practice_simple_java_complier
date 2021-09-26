#include "register.h"
#include "label.h"
#include "AAT.h"

AATexpressionList AATExpressionList(AATexpression first, AATexpressionList rest) {
  AATexpressionList retval = (AATexpressionList) malloc(sizeof(struct AATexpressionList_));
  retval->first = first;
  retval->rest = rest;
  return retval;
}

AATstatement AATMove(AATexpression lhs, AATexpression rhs) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_MOVE;
  retval->u.move.lhs = lhs;
  retval->u.move.rhs = rhs;
  return retval;
}

AATstatement AATLabel(Label label) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_LABEL;
  retval->u.label = label;
  return retval;
}
AATstatement AATJump(Label jump) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_JUMP;
  retval->u.jump = jump;
  return retval;
}

AATstatement AATConditionalJump(AATexpression test,Label jump) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_CONDITIONALJUMP;
  retval->u.conditionalJump.jump = jump;
  retval->u.conditionalJump.test = test;
  return retval;
}

AATstatement AATCallStatement(Label jump, AATexpressionList actuals) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_CALLSTATEMENT;
  retval->u.callStatement.jump = jump;
  retval->u.callStatement.actuals = actuals;
  return retval;
}
AATstatement AATSequential(AATstatement left, AATstatement right) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_SEQ;
  retval->u.sequential.left = left;
  retval->u.sequential.right = right;
  return retval;
}
AATstatement AATEmpty(void) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_EMPTY;
  return retval;
}
AATstatement AATReturn(void) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_RETURN;
  return retval;
}

AATstatement AATHalt(void) {
  AATstatement retval = (AATstatement) malloc(sizeof(struct AATstatement_));
  retval->kind = AAT_HALT;
  return retval;
}

AATexpression AATMemory(AATexpression memory){
  AATexpression retval = (AATexpression) malloc(sizeof(struct AATexpression_));
  retval->kind = AAT_MEMORY;
  retval->u.memory = memory;
  return retval;
}

AATexpression AATOperator(AATexpression left, AATexpression right, AAToperator op) {
  AATexpression retval = (AATexpression) malloc(sizeof(struct AATexpression_));
  retval->kind = AAT_OPERATOR;
  retval->u.operator.left = left;
  retval->u.operator.right = right;
  retval->u.operator.op = op;
  return retval;
}
AATexpression AATCallExpression(Label jump, AATexpressionList actuals) {
  AATexpression retval = (AATexpression) malloc(sizeof(struct AATexpression_));
  retval->kind = AAT_CALLEXPRESSION;
  retval->u.callExpression.jump = jump;
  retval->u.callExpression.actuals = actuals;
  return retval;
}
AATexpression AATConstant(int constant) {
  AATexpression retval = (AATexpression) malloc(sizeof(struct AATexpression_));
  retval->kind = AAT_CONSTANT;
  retval->u.constant = constant;
  return retval;
}
AATexpression AATRegister(Register reg){
  AATexpression retval = (AATexpression) malloc(sizeof(struct AATexpression_));
  retval->kind = AAT_REGISTER;
  retval->u.reg = reg;
  return retval;
}
