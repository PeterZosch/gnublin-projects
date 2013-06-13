#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
   printf("Insgesamt %d Argumente\n", argc-1);
   printf("Letztes Argument: %s\n", argv[argc-1]);
   return EXIT_SUCCESS;
}
