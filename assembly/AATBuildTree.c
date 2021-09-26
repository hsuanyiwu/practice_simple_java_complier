#include <stdio.h>
#include "label.h"
#include "register.h"
#include "AAT.h"
#include "MachineDependent.h"



AATexpression Allocate(AATexpression size) {
  AATexpressionList actuals = AATExpressionList(size, NULL);
  return AATFunctionCall("allocate",actuals);

}

AATstatement EmptyStatement() {
  return AATEmpty();
}

/* implementation of the rest of the interface */
