#ifndef errors_h
#define errors_h

struct position {
    int line_number;
    int column_number;
};

void Error(int line, int column, char * message,...);
int numErrors();
int anyErrors();

#endif
