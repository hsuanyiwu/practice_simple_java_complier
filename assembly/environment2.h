envEntry VarEntry(type typ, int offset);
envEntry FunctionEntry(type returntyp, typeList formals, Label startLabel, Label endLabel);
envEntry TypeEntry(type typ);


struct envEntry_ {
  enum {Var_Entry, Function_Entry,Type_Entry} kind;
  union {
    struct {
      type typ;
      int offset;
    } varEntry;
    struct {
      type returntyp;
      typeList formals;
      Label startLabel;
      Label endLabel;
    } functionEntry;
    struct {
      type typ;
    } typeEntry;
  } u;
};
