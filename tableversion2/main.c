#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error. Usage: calcula <code>\n");
    return EXIT_FAILURE;
  }

  FILE *fd;

  fd = fopen(argv[1], "r");
  if (fd == NULL) {
    fprintf(stderr, "Error opening file\n");
    return EXIT_FAILURE;
  }

  // ungetc is very good
  char c;
  while (c != EOF) {
    c = fgetc(fd);
    printf("%c ", c);
    if (c == ')') {
      ungetc(c, fd);
    }
  }

  return EXIT_SUCCESS;
}
