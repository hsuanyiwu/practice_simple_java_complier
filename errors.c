/*
 * errors.c - functions used in all phases of the compiler to give
 *              error messages 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "errors.h"

int Number_Of_Errors = 0;

void Error(int line, int column, char *message,...)
{va_list ap;
 Number_Of_Errors++;
 fprintf(stderr,"Error in Ln:%2d Col:%2d", line, column);
 va_start(ap,message);
 vfprintf(stderr, message, ap);
 va_end(ap);
 fprintf(stderr,"\n");
}

int numErrors() {
 return Number_Of_Errors;
}
int anyErrors() {
 return Number_Of_Errors;
}
