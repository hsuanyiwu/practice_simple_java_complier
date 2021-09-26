typedef struct variableEnvironment_ *variableEnvironment;
typedef struct functionEnvironment_ *functionEnvironemt;
typedef struct typeEnvironment_ *typeEnvironment;


typedef struct variableEntry_ *variableEntry;
typedef struct typeEntry *typeEntry;
typedef struct functionEntry *functionEntry;



variableEnvironment VariableEnvironment();
functionEnvironment FunctionEnvironment();
typeEnvironment TypeEnvironment();

void AddBuiltinTypes(TypeEnvironment typenv);
void AddBuiltinFunctions(FunctionEnvironment functionenv);

void beginScope(
