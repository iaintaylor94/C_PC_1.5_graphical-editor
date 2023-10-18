// Program to manipulate a bitmap

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/errno.h>

// Define Structures
struct image {
char bitMap [250][250];
int width;
int height;
};

// Global Pointers
struct image *gImage;
FILE *gInputFile = NULL;

// Declare Functions
void usage (char *);
void processLineI(void);
void processLineC(void);
void processLineL(void);
void processLineV(void);
void processLineH(void);
void processLineK(void);
bool borderLeft(int);
bool borderRight(int);
bool borderTop(int);
bool borderBottom(int);
void fillR (int, int, char, char);
void processLineF(void);
void processLineS(void);
void processLine(void);


int main(int argc, char *argv[]) {

  // File Initialization
  if (argc != 2) usage (argv[0]);

  if (NULL == (gInputFile = fopen(argv[1], "r"))) {
    fprintf (stderr, "inputFile: %s: %s\n", argv[1], strerror(errno));
    exit (EXIT_FAILURE);
  }
  else {
    fprintf (stderr, "%s opened for reading.\n" , argv[1]);
  }
  


  fclose (gInputFile);

  return 0;
}

// Define Functions
void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}

void processLineI(void) {
  fscanf (gInputFile, "%d %d", &gImage->width, &gImage->height);
}

void processLineC(void) {
  for (int i = 0; i <= gImage->height; i++) {
    for (int j = 0; j <= gImage->width; j++) {
      gImage->bitMap[i][j] = 'O';
    }
  }
}

void processLineL(void) {
  int Y, X;
  char c;
  
  fscanf (gInputFile, "%d %d %c", &Y, &X, &c);

  gImage->bitMap[Y][X] = c;
}

void processLineV(void) {
  int X;
  int Y1, Y2;
  char c;

  fscanf(gInputFile, "%d %d %d %c", &X, &Y1, &Y2, &c);

  for (int i = Y1; i <= Y2; i++) {
    gImage->bitMap[i][X] = c;
  }
}

void processLineH(void) {
  int X1, X2;
  int Y;
  char c;
  
  fscanf(gInputFile, "%d %d %d %c", &X1, &X2, &Y, &c);

  for (int i = X1; i <= X2; i++) {
    gImage->bitMap[Y][i] = c;
  }
}

void processLineK(void) {
  int X1, X2;
  int Y1, Y2;
  char c;
  
  fscanf(gInputFile, "%d %d %d %d %c", &X1, &X2, &Y1, &Y2, &c);

  for (int i = Y1; i <= Y2; i++) {
    for (int j = X1; j <= X2; j++) {
      gImage->bitMap[i][j] = c;
    }
  }
}

bool borderLeft(int X) {
  if (X == 0) {
      return true;
  }
  return false;
}

bool borderRight(int X) {
  if (X == gImage->width) {
    return true;
  }
  return false;
}

bool borderTop(int Y) {
  if (Y == 0) {
      return true;
  }
  return false;
}

bool borderBottom(int Y) {
  if (Y == gImage->height) {
    return true;
  }
  return false;
}

void fillR (int X, int Y, char F, char T) { // X, Y, From, To
  if (!(borderLeft(X - 1) || borderTop(Y - 1))) { // Top Left
    if (gImage->bitMap[Y - 1][X - 1] == F) {
      gImage->bitMap[Y - 1][X - 1] = T;
      fillR(X - 1, Y - 1, F, T);
    }
  }
  if (!borderTop(Y - 1)) { // Top Middle
    if (gImage->bitMap[Y - 1][X] == F) {
      gImage->bitMap[Y - 1][X] = T;
      fillR(X, Y - 1, F, T);
    }
  }
  if (!(borderTop(Y - 1) || borderRight(X + 1))) { // Top Right
    if (gImage->bitMap[Y - 1][X + 1] == F) {
      gImage->bitMap[Y - 1][X + 1] = T;
      fillR(X + 1, Y - 1, F, T);
    }
  }
  if (!borderLeft(X - 1)) { // Middle Left
    if (gImage->bitMap[Y][X - 1] == F) {
      gImage->bitMap[Y][X - 1] = T;
      fillR(X - 1, Y, F, T);
    }
  }
  if (!borderRight(X + 1)) { // Middle Right
    if (gImage->bitMap[Y][X + 1] == F) {
      gImage->bitMap[Y][X + 1] = T;
      fillR(X + 1, Y, F, T);
    }
  }
  if (!(borderLeft(X - 1) || borderBottom(Y + 1))) { // Bottom Left
    if (gImage->bitMap[Y + 1][X - 1] == F) {
      gImage->bitMap[Y + 1][X - 1] = T;
      fillR(X - 1, Y + 1, F, T);
    }
  }
  if (!borderBottom(Y + 1)) { // Bottom Middle
    if (gImage->bitMap[Y + 1][X] == F) {
      gImage->bitMap[Y + 1][X] = T;
      fillR(X, Y + 1, F, T);
    }
  }
  if (!(borderBottom(Y + 1) || borderRight(X + 1))) { // Bottom Right
    if (gImage->bitMap[Y + 1][X + 1] == F) {
      gImage->bitMap[Y + 1][X + 1] = T;
      fillR(X + 1, Y + 1, F, T);
    }
  }
}

void processLineF(void) {
  int X, Y;
  char c1, c2; // to : from
  
  fscanf(gInputFile, "%d %d %c", &X, &Y, &c1);
  c2 = gImage->bitMap[Y][X];

  if (c1 == c2) {
    fprintf (stderr, "Error: Cannot flip color %c to itself.\n", c1);
  }
  else {
    fillR (X, Y, c1, c2);
  }
  
}

void processLineS(void) {
  char prefix[80], postfix[80];

  fscanf(gInputFile, "%s %s", prefix, postfix);
  printf("%s.%s\n", prefix, postfix);

  for (int i = 0; i < gImage->height; i++) {
    for (int j = 0; j < gImage->width; j++) {
      printf ("%c" , gImage->bitMap[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}



void processLine() {
  int c = fgetc(gInputFile);

  switch (c) {
    case 'X':
      exit (EXIT_SUCCESS);
      break;
    case 'I':
      processLineI();
      break;
    case 'C':
      processLineC();
      break;
    case 'L':
      processLineL();
      break;
    case 'V':
      processLineV();
      break;
    case 'H':
      processLineH();
      break;
    case 'K':
      processLineK();
      break;
    case 'F':
      processLineF();
      break;
    case 'S':
      processLineS();
      break;
    default:
      fprintf (stderr, "unknown command: %c\n", c);
      break;
  }
  
}