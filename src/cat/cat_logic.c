#include "cat_logic.h"

#include <stdio.h>

void print_char(int ch, CatFlags flags) {
  if (flags.v) {
    if (ch != '\n' && ch != '\t' && ch < 32) {
      putchar('^');
      putchar(ch + 64);
    } else if (ch == 127) {
      printf("^?");
    } else {
      if ((flags.t || flags.T) && ch == '\t') {
        printf("^I");
      } else {
        if ((flags.e || flags.E) && ch == '\n') {
          putchar('$');
        }

        putchar(ch);
      }
    }
  } else {
    if ((flags.t || flags.T) && ch == '\t') {
      printf("^I");
    } else {
      if ((flags.e || flags.E) && ch == '\n') {
        putchar('$');
      }

      putchar(ch);
    }
  }
}

void process_file(const char* filename, CatFlags flags) {
  FILE* fp = fopen(filename, "r");

  if (fp != NULL) {
    int ch = 0;
    int line_number = 1;
    int start_line = 1;
    int empty_lines = 0;

    while ((ch = fgetc(fp)) != EOF) {
      if (start_line) {
        if (flags.b) {
          if (ch != '\n') {
            printf("%6d\t", line_number);
            line_number++;
          }
        } else if (flags.n) {
          printf("%6d\t", line_number);
          line_number++;
        }
      }

      int should_print = 1;

      if (flags.s) {
        if (ch == '\n') {
          empty_lines++;
        } else {
          empty_lines = 0;
        }

        if (empty_lines > 2) {
          should_print = 0;
        }
      }

      if (should_print) {
        print_char(ch, flags);
      }

      if (ch == '\n') {
        start_line = 1;
      } else {
        start_line = 0;
      }
    }

    fclose(fp);
  }
}