#ifndef errors_h
#define errors_h
extern int Current_Line;


void Error(int position, char * message,...);
int numErrors();
int anyErrors();
#endif
