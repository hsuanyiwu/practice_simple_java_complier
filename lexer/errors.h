#ifndef errors_h
#define errors_h

void Error(int line, int column, char * message,...);
int numErrors();
int anyErrors();

#endif
