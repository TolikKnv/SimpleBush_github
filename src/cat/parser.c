#include "parser.h"

#include <getopt.h>
#include <stdio.h>

void parse_flags(int argc, char *argv[], CatFlags *flags) {
  static struct option long_options[] = {
      {"number-nonblank", no_argument, 0, 'b'},
      {"number", no_argument, 0, 'n'},
      {"squeeze-blank", no_argument, 0, 's'},
      {0, 0, 0, 0}};

  int opt = 0;

  while ((opt = getopt_long(argc, argv, "benstvET", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        flags->b = 1;
        break;

      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;

      case 'n':
        flags->n = 1;
        break;

      case 's':
        flags->s = 1;
        break;

      case 't':
        flags->t = 1;
        flags->v = 1;
        break;

      case 'v':
        flags->v = 1;
        break;

      case 'E':
        flags->E = 1;
        break;

      case 'T':
        flags->T = 1;
        break;

      default:
        fprintf(stderr, "Invalid flag\n");
        break;
    }
  }

  if (flags->b) {
    flags->n = 0;
  }
}