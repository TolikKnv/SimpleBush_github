#ifndef CAT_LOGIC_H
#define CAT_LOGIC_H

#include "s21_cat.h"

void process_file(const char *filename, CatFlags flags);
void print_char(int ch, CatFlags flags);
void print_line_number(int ch, CatFlags flags, int *line_number);

#endif