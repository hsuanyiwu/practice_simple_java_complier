#include <stdio.h>
#include "errors.h"
#include "label.h"
#include "register.h"
#include "AST.h"
#include "ASTPrintTree.h"
#include "AAT.h"
#include "AATPrintTree.h"
#include "semantic.h"
#include "AATBuildTree.h"

int main() {
  AATstatement s1;

  s1 = AssignmentStatement(BaseVariable(4),ConstantExpression(13));

  printAAT(s1);

  /* Add more tests, to test the rest of your AATBuildTree interface */

}
