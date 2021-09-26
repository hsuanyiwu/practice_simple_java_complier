#include "label.h"
#include "register.h"
#include "AAT.h"
#include "AATBuildTree.h"
#include "AST.h"
#include "environment1.h"
#include "type.h"
#include "environment2.h"
#include "semantic.h"
#include "MachineDependent.h"
#include <stdio.h>

typedef struct expressionRec_ expressionRec;

struct expressionRec_ {
   type typ;
   AATexpression tree;
};

int offset;  /* offset of last declared variable */
/* other globals */

expressionRec ExpressionRec(type typ, AATexpression tree);


AATstatement analyzeStatement(environment typeEnv, environment functionEnv,
		      environment varEnv, ASTstatement statement);

expressionRec analyzeExpression(environment typeEnv, environment functionEnv,
		      environment varEnv, ASTexpression exp);

expressionRec analyzeVar(environment typeEnv, environment functionEnv,
		environment varEnv, ASTvariable var);


AATstatement analyzeStatement(environment typeEnv, environment functionEnv,
			      environment varEnv, ASTstatement statement) {
  switch(statement->kind) {
  case AssignStm:
    { 
      expressionRec LHS, RHS;
      LHS = analyzeVar(typeEnv,functionEnv,varEnv,statement->u.assignStm.lhs);
      RHS = analyzeExpression(typeEnv,functionEnv,varEnv,statement->u.assignStm.rhs);
      if (LHS.typ != RHS.typ) {
	Error(statement->line,"Type mismatch on assignment");
      }
      return AssignmentStatement(LHS.tree, RHS.tree);
    }
    break;
  case IfStm:
    {
      AATstatement iftree;
      AATstatement elsetree;
      expressionRec test = analyzeExpression(typeEnv, functionEnv, varEnv,
					     statement->u.ifStm.test);
      if (test.typ != BooleanType()) {
	Error(statement->line,"If test must be a boolean");
      }
      iftree = analyzeStatement(typeEnv, functionEnv, varEnv, statement->u.ifStm.thenstm);
      if (statement->u.ifStm.elsestm != NULL) {
	elsetree = analyzeStatement(typeEnv, functionEnv, varEnv, statement->u.ifStm.elsestm);
      } else
	elsetree = NULL;
      return IfStatement(test.tree, iftree, elsetree);
    }
    break;
    /* more cases */
  default:
    Error(statement->line,"Bad Statement");
    return NULL;
  }
}


expressionRec analyzeExpression(environment typeEnv, environment functionEnv,
				environment varEnv, ASTexpression exp) {
  switch(exp->kind) {
  case IntLiteralExp:
    return ExpressionRec(IntegerType(),ConstantExpression(exp->u.intLiteralExp.value));
  case OpExp:
    return analyzeOpExpression(typeEnv,functionEnv, varEnv, exp);
   case VarExp:
    return analyzeVar(typeEnv,functionEnv,varEnv,exp->u.varExp.var);
    
    /* more cases */
  default:
    Error(exp->line,"Bad Expression");
    return ExpressionRec(IntegerType(),NULL);
  }
}

expressionRec analyzeVar(environment typeEnv, environment functionEnv,
			 environment varEnv, ASTvariable var) {
  envEntry base;
  switch(var->kind) {
  case BaseVar:
    base = find(varEnv, var->u.baseVar.name);
    if (base == NULL) {
      Error(var->line,"Variable %s not defined",var->u.baseVar.name);
      return ExpressionRec(IntegerType(),NULL);
    }
    return ExpressionRec(base->u.varEntry.typ,BaseVariable(base->u.varEntry.offset));
    break;
  case ClassVar:

    break;
  case ArrayVar:

    break;
  default:
    Error(var->line,"Malformed Variable");
  }
}



expressionRec analyzeOpExpression(environment typeEnv, environment functionEnv,
				  environment varEnv, ASTexpression exp) {
  switch(exp->u.opExp.operator) {
  case AST_PLUS:
    {
      expressionRec LHS = analyzeExpression(typeEnv,functionEnv,varEnv,exp->u.opExp.left);
      expressionRec RHS = analyzeExpression(typeEnv,functionEnv,varEnv,exp->u.opExp.right);
      if ((LHS.typ != IntegerType()) || (RHS.typ != IntegerType())) 
	Error(exp->line,"Both arguments to + must be integers");
      return ExpressionRec(IntegerType(),OperatorExpression(LHS.tree,RHS.tree,AAT_PLUS));
    } 
    break;
    /* more cases */
  }
}
 
expressionRec ExpressionRec(type typ, AATexpression tree) {
  expressionRec retval;
  retval.typ = typ;
  retval.tree = tree;
  return retval;
}

