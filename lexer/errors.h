#ifndef errors_h
#define errors_h
extern int current_line;


void Error(int position, char * message,...);
int numErrors();
int anyErrors();
#endif
