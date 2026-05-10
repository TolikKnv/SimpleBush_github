#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>

#include "cat_logic.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  CatFlags flags = {0};

  parse_flags(argc, argv, &flags);

  for (int i = optind; i < argc; i++) {
    process_file(argv[i], flags);
  }

  return 0;
}