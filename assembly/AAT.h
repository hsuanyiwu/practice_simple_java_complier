typedef struct AATexpression_ *AATexpression;
typedef struct AATstatement_ *AATstatement;
typedef struct AATexpressionList_ *AATexpressionList;

typedef enum {AAT_PLUS, AAT_MINUS, AAT_MULTIPLY, AAT_DIVIDE, AAT_LT,
	      AAT_GT, AAT_LEQ, AAT_GEQ, AAT_EQ, AAT_NEQ, AAT_AND, AAT_OR,
              AAT_NOT} AAToperator;


struct AATexpressionList_ {
  AATexpression first;
  AATexpressionList rest;
};

struct AATstatement_ {
  enum {AAT_MOVE, AAT_JUMP, AAT_CONDITIONALJUMP, AAT_PROCEDURECALL, AAT_SEQ, AAT_EMPTY, AAT_LABEL, AAT_RETURN, AAT_HALT} kind; 
  union {
    struct {
      AATexpression lhs;
      AATexpression rhs;
    } move;
    Label jump;
    struct {
      AATexpression test;
      Label jump;
    } conditionalJump;
    struct {
      Label jump;
      AATexpressionList actuals;
    } procedureCall;
    struct {
      AATstatement left;
      AATstatement right;
    } sequential;
    Label label;
  } u;
};

struct AATexpression_ {
  enum {AAT_MEMORY, AAT_OPERATOR, AAT_FUNCTIONCALL, AAT_CONSTANT, AAT_REGISTER} kind;
  union {
    AATexpression memory;
    int constant;
    struct {
      AATexpression left;
      AATexpression right;
      AAToperator op;
    } operator;
    struct {
      Label jump;
      AATexpressionList actuals;
    } functionCall;
    Register reg;
  } u;
};

AATexpressionList AATExpressionList(AATexpression first, AATexpressionList rest);
AATstatement AATMove(AATexpression lhs, AATexpression rhs);
AATstatement AATLabel(Label);
AATstatement AATJump(Label jump);
AATstatement AATConditionalJump(AATexpression test,Label jump);
AATstatement AATProcedureCall(Label jump, AATexpressionList actuals);
AATstatement AATSequential(AATstatement left, AATstatement right);
AATstatement AATEmpty(void);
AATstatement AATReturn(void);
AATstatement AATHalt(void);
AATexpression AATMemory(AATexpression mem);
AATexpression AATOperator(AATexpression left, AATexpression right, AAToperator op);
AATexpression AATFunctionCall(Label jump, AATexpressionList actuals);
AATexpression AATConstant(int constant);
AATexpression AATRegister(Register reg);
