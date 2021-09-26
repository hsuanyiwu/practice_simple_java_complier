AATstatement functionDefinition(AATstatement body, int framesize, 
                                Label start, Label end);
AATstatement IfStatement(AATexpression test, AATstatement ifbody, 
                         AATstatement elsebody);
AATexpression Allocate(AATexpression size);
AATstatement WhileStatement(AATexpression test, 
                            AATstatement whilebody);
AATstatement DoWhileStatement(AATexpression test, 
                              AATstatement dowhilebody);
AATstatement ForStatement(AATstatement init, AATexpression test, 
                          AATstatement increment, AATstatement body);
AATstatement EmptyStatement(void);
AATstatement CallStatement(AATexpressionList actuals, Label name);
AATstatement AssignmentStatement(AATexpression lhs,
                                 AATexpression rhs);
AATstatement SequentialStatement(AATstatement first,
                                 AATstatement second);
AATexpression BaseVariable(int offset);
AATexpression ArrayVariable(AATexpression base,
                            AATexpression index,
                            int elementSize);
AATexpression ClassVariable(AATexpression base, int offset);
AATexpression ConstantExpression(int value);
AATexpression OperatorExpression(AATexpression left,
                                 AATexpression right,
                                 AAToperator operator);
AATexpression CallExpression(AATexpressionList actuals, Label name);
AATstatement ReturnStatement(AATexpression value, Label functionend); 
