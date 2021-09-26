envEntry VarEntry(type typ);
envEntry FunctionEntry(type returntyp, typeList formals);
envEntry TypeEntry(type typ);


struct envEntry_ {
  enum {Var_Entry, Function_Entry,Type_Entry} kind;
  union {
    struct {
      type typ;
    } varEntry;
    struct {
      type returntyp;
      typeList formals;
    } functionEntry;
    struct {
      type typ;
    } typeEntry;
  } u;
};
