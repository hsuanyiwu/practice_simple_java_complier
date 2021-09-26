#include "AST.h"
#include "environment1.h"
#include "type.h"
#include "environment2.h"
#include "semantic.h"
#include <stdio.h>

void analyzeProgram(ASTprogram program) {
  environment typeEnv;
  environment functionEnv;
  environment varEnv;

  typeEnv = Environment();
  functionEnv = Environment();
  varEnv = Environment();

  AddBuiltinTypes(typeEnv);
  AddBuiltinFunctions(functionEnv);

  /* analyze classes */
  /* analyze functions */
}


void analyzeStatement(environment typeEnv, environment functionEnv,
		      environment varEnv, ASTstatement statement) {
  switch(statement->kind) {
  case AssignStm:
    { 
      type LHS, RHS;
      LHS = analyzeVar(typeEnv,functionEnv,varEnv,statement->u.assignStm.lhs);
      RHS = analyzeExpression(typeEnv,functionEnv,varEnv,statement->u.assignStm.rhs);
      if (LHS != RHS) {
	Error(statement->line,"Type mismatch on assignment");
      }
    }
    break;
  case IfStm:
    {
      type test = analyzeExpression(typeEnv, functionEnv, varEnv,
				    statement->u.ifStm.test);
      if (test != BooleanType()) {
	Error(statement->line,"If test must be a boolean");
      }
      analyzeStatement(typeEnv, functionEnv, varEnv, statement->u.ifStm.thenstm);
      if (statement->u.ifStm.elsestm != NULL) {
	analyzeStatement(typeEnv, functionEnv, varEnv, statement->u.ifStm.elsestm);
      }
    }
    break;
    /* more cases */
  default:
    Error(statement->line,"Bad Statement");
  }
}


type analyzeExpression(environment typeEnv, environment functionEnv,
		       environment varEnv, ASTexpression exp) {
  switch(exp->kind) {
  case IntLiteralExp:
    return IntegerType();
  case BoolLiteralExp:
    return BooleanType();
  case OpExp:
    return analyzeOpExpression(typeEnv,functionEnv, varEnv, exp);
   case VarExp:
    return analyzeVar(typeEnv,functionEnv,varEnv,exp->u.varExp.var);
    /* more cases */

  default:
    Error(exp->line,"Bad Expression");
    return IntegerType();
  }
}


type analyzeVar(environment typeEnv, environment functionEnv,
		environment varEnv, ASTvariable var) {
  envEntry base;
  switch(var->kind) {
  case BaseVar:
    base = find(varEnv, var->u.baseVar.name);
    if (base == NULL) {
      Error(var->line,"Variable %s not defined",var->u.baseVar.name);
      return IntegerType();
    }
    return base->u.varEntry.typ;
    break;
  case ClassVar:
    /* class variables */
    break;
  case ArrayVar:
    /* array variables */
    break;
  default:
    Error(var->line,"Malformed Variable");
  }
}

type analyzeOpExpression(environment typeEnv, environment functionEnv,
			 environment varEnv, ASTexpression exp) {
  switch(exp->u.opExp.operator) {
  case AST_PLUS:
    {
      type LHS = analyzeExpression(typeEnv,functionEnv,varEnv,exp->u.opExp.left);
      type RHS = analyzeExpression(typeEnv,functionEnv,varEnv,exp->u.opExp.right);
      if ((LHS != IntegerType()) || (RHS != IntegerType())) 
	Error(exp->line,"Both arguments to + must be integers");
      return IntegerType();
    } 
    break;
    /* more cases */
  }
}

