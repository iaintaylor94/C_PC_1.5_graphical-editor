// Program to manipulate a bitmap

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/errno.h>

// Declare Functions
void usage (char *);

int main(int argc, char *argv[]) {

  // File Initialization
  FILE *inputFile = NULL;

  if (argc != 2) usage (argv[0]);

  if (NULL == (inputFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
    fprintf (stderr, "%s opened for reading.\n" , argv[1]);
  }








  


  fclose (inputFile);

  return 0;
}

// Define Functions
void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}