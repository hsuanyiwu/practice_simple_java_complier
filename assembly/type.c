#include <stdio.h>
#include "environment1.h"
#include "type.h"
type integertypeINST = NULL;
type booleantypeINST = NULL;
type voidtypeINST = NULL;


type IntegerType() {
  if (integertypeINST == NULL) {
    integertypeINST = (type) malloc(sizeof(struct type_));
    integertypeINST->kind = integer_type;
  }
  return integertypeINST;
}

type BooleanType() {
  if (booleantypeINST == NULL) {
    booleantypeINST = (type) malloc(sizeof(struct type_));
    booleantypeINST->kind = boolean_type;
  }
  return booleantypeINST;
}

type VoidType() {
  if (voidtypeINST == NULL) {
    voidtypeINST = (type) malloc(sizeof(struct type_));
    voidtypeINST->kind = void_type;
  }
  return voidtypeINST;
}
type ClassType(environment instancevars) {
  type retval = (type) malloc(sizeof(struct type_));
  retval->kind=class_type;
  retval->u.class.instancevars = instancevars;
  return retval;
}

type ArrayType(type basetype) {
  type retval = (type) malloc(sizeof(struct type_));
  retval->kind=array_type;
  retval->u.array=basetype;
  return retval;
}
  
typeList TypeList(type first, typeList rest) {
  typeList retval = (typeList) malloc(sizeof(struct typeList_));
  retval->first = first;
  retval->rest = rest;
  return retval;
}
