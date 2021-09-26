#define IDENTIFIER 257
#define INTEGER_LITERAL 258
#define CLASS 259
#define DO 260
#define ELSE 261
#define TRUE 262
#define FALSE 263
#define FOR 264
#define IF 265
#define WHILE 266
#define PLUS 267
#define MINUS 268
#define MULTIPLY 269
#define DIVIDE 270
#define LBRACK 271
#define RBRACK 272
#define LBRACE 273
#define RBRACE 274
#define LPAREN 275
#define RPAREN 276
#define DOT 277
#define COMMA 278
#define SEMICOLON 279
#define EQ 280
#define NEQ 281
#define LT 282
#define GT 283
#define LEQ 284
#define GEQ 285
#define GETS 286
#define AND 287
#define OR 288
#define NOT 289
#define PLUSPLUS 290
#define MINUSMINUS 291
#define RETURN 292
#define NEW 293

typedef union { 
     struct {
         int value;
         int line_number;
     } integer_value;
     struct {
         char *value;
         int line_number;
     } string_value;
     int line_number;
} YYSTYPE;
extern YYSTYPE yylval;
