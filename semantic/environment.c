#include <stdio.h>
#include "hash.h"
#include "environment1.h"
#include "type.h"
#include "environment2.h"
/* Use a reasonable (PRIME!) hash table size */
#define HASHTABLESIZE 503

/* Local Type definitions */

typedef struct stackElem_ *stackElem;

struct stackElem_ {
  char *key;
  stackElem next;
};

struct environment_ {
  H_hashTable table;
  stackElem stack;
};
/* Local Prototypes */

stackElem StackElem(char *key, stackElem next);
char *Marker();

/* Static variables */

char *stackmarker = NULL;

/* Function Definitions */


char *Marker() {
  if (stackmarker != NULL) {
    stackmarker = (char *) malloc(6 * sizeof(char));
    strcpy(stackmarker,"0mark");
  }
  return stackmarker;
}

void enter(environment env, char * key, envEntry entry) {
  H_insert(env->table,key,(void *) entry);
  env->stack = StackElem(key,env->stack); 
}

envEntry find(environment env, char *key) {
  return (envEntry) H_find(env->table,key);
}

void beginScope(environment env) {
  env->stack = StackElem(Marker(),env->stack);
}
    
void endScope(environment env) {
  while(env->stack && (env->stack->key != Marker())) {
    H_delete(env->table,env->stack->key);
    env->stack = env->stack->next;
  }
  
  if (env->stack)
    env->stack = env->stack->next;
}


void AddBuiltinTypes(environment env) {
  enter(env,"int",TypeEntry(IntegerType()));
  enter(env,"boolean",TypeEntry(BooleanType()));
  enter(env,"void",TypeEntry(VoidType()));
}

void AddBuiltinFunctions(environment env) {
  typeList formals = NULL;
  enter(env, "Read", FunctionEntry(IntegerType(),NULL));
  enter(env, "Println", FunctionEntry(VoidType(),NULL));
  enter(env, "Print", FunctionEntry(VoidType(), TypeList(IntegerType(), NULL)));
}
 

environment Environment() {
  environment retval = (environment) malloc(sizeof(struct environment_));
  retval->table = H_HashTable(HASHTABLESIZE);
  retval->stack = NULL;
  return retval;
}


envEntry VarEntry(type typ) {
  envEntry retval = (envEntry) malloc(sizeof(struct envEntry_));
  retval->kind = Var_Entry;
  retval->u.varEntry.typ = typ;
  return retval;
}
envEntry FunctionEntry(type returntyp, typeList formals) {
  envEntry retval = (envEntry) malloc(sizeof(struct envEntry_));
  retval->kind = Function_Entry;
  retval->u.functionEntry.returntyp = returntyp;
  retval->u.functionEntry.formals = formals;
  return retval;
}


envEntry TypeEntry(type typ) {
  envEntry retval = (envEntry) malloc(sizeof(struct envEntry_));
  retval->kind = Type_Entry;
  retval->u.typeEntry.typ = typ;
  return retval;
}

stackElem StackElem(char *key, stackElem next) {
  stackElem retval = (stackElem) malloc(sizeof(struct stackElem_));
  retval->key = key;
  retval->next = next;
  return retval;
}
