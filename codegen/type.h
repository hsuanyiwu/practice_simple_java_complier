typedef struct type_ *type;
typedef struct typeList_ *typeList;

struct type_ {
  enum {integer_type, boolean_type, void_type,
	class_type, array_type} kind;
  union {
    type array;
    struct {
      environment instancevars;
    } class;
  } u;
};

struct typeList_ { 
  type first;
  typeList rest;
};

type IntegerType();
type BooleanType();
type VoidType();
type ClassType(environment instancevars);
type ArrayType(type basetype);
typeList TypeList(type first, typeList rest);


