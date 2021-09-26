typedef struct environment_ *environment;
typedef struct envEntry_ *envEntry;

environment Environment();

void AddBuiltinTypes(environment env);
void AddBuiltinFunctions(environment env);

void beginScope(environment env);
void endScope(environment env);

void enter(environment env, char * key, envEntry entry);
envEntry find(environment env, char *key);
