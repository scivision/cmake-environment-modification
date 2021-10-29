#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

if(argc != 2) {
  fprintf(stderr, "please specify environment variable name to print\n"); return 1;
}
printf("%s\n", getenv(argv[1]));

return 0;
}
