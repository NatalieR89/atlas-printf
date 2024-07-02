#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h> /* for variadic functions */
#include <unistd.h> /* write */

int _printf(const char *format, ...);

void print_char(va_list args, int *count);

void print_string(va_list args, int *count);

void handle_int(va_list args, int *count);

void handle_uint(va_list args, int *count);

void print_number(int n, int *count);

void print_unsigned_int(unsigned int n, int *count);


#endif
