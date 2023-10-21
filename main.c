// Program to manipulate a bitmap

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/errno.h>

#define DEBUG 1

// Define Structures
struct image {
char bitMap [250][250];
int left; 
int right;
int top;
int bottom;
};

// Global Pointers
struct image *gImage;
FILE *gInputFile = NULL;

// Declare Functions
void usage (char *);
void printImage(void);
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
bool processLine(int);









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

  // Initialize Image
  gImage = (struct image*) calloc(1, sizeof(struct image));

  // Process File
  bool loop = true;
  while (loop) {
    int c = fgetc(gInputFile); // First character
    loop = processLine(c);
  } 

  // File Close
  fclose (gInputFile);

  return 0;
}









// Define Functions
void usage (char *cmd) {
  fprintf (stderr, "usage: %s inputFileName\n", cmd);
  exit (EXIT_SUCCESS);
}

void printImage () {
  for (int i = gImage->top; i < gImage->bottom; i++) {
    for (int j = gImage->left; j < gImage->right; j++) {
      printf ("%c", gImage->bitMap[i][j]);
    }
    printf ("\n");
  }
  printf ("\n");
}

void processLineI(void) {
  fscanf (gInputFile, "%d %d ", &gImage->right, &gImage->bottom);
  gImage->left = 1; gImage->right++;  
  gImage->top = 1; gImage->bottom++;
  processLineC ();
}

void processLineC(void) {
  for (int i = gImage->top; i <= gImage->bottom; i++) {
    for (int j = gImage->left; j <= gImage->right; j++) {
      gImage->bitMap[i][j] = 'O';
    }
  }
}

void processLineL(void) {
  int Y, X;
  char c;
  
  fscanf (gInputFile, "%d %d %c ", &X, &Y, &c);

  gImage->bitMap[Y][X] = c;
}

void processLineV(void) {
  int X;
  int Y1, Y2;
  char c;

  fscanf(gInputFile, "%d %d %d %c", &X, &Y1, &Y2, &c);
  while (fgetc(gInputFile) != '\n');

  for (int i = Y1; i <= Y2; i++) {
    gImage->bitMap[i][X] = c;
  }
}

void processLineH(void) {
  int X1, X2;
  int Y;
  char c;
  
  fscanf(gInputFile, "%d %d %d %c", &X1, &X2, &Y, &c);
  while (fgetc(gInputFile) != '\n');

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
  if (X == gImage->left - 1) {
      return true;
  }
  return false;
}

bool borderRight(int X) {
  if (X == gImage->right + 1) {
    return true;
  }
  return false;
}

bool borderTop(int Y) {
  if (Y == gImage->top - 1) {
      return true;
  }
  return false;
}

bool borderBottom(int Y) {
  if (Y == gImage->bottom + 1) {
    return true;
  }
  return false;
}

void fillR (int X, int Y, char T, char F) { // X, Y, From, To
  if (!(borderLeft(X - 1) || borderTop(Y - 1))) { // Top Left
    if (gImage->bitMap[Y - 1][X - 1] == F) {
      gImage->bitMap[Y - 1][X - 1] = T;
      fillR(X - 1, Y - 1, T, F);
    }
  }
  if (!borderTop(Y - 1)) { // Top Middle
    if (gImage->bitMap[Y - 1][X] == F) {
      gImage->bitMap[Y - 1][X] = T;
      fillR(X, Y - 1, T, F);
    }
  }
  if (!(borderTop(Y - 1) || borderRight(X + 1))) { // Top Right
    if (gImage->bitMap[Y - 1][X + 1] == F) {
      gImage->bitMap[Y - 1][X + 1] = T;
      fillR(X + 1, Y - 1, T, F);
    }
  }
  if (!borderLeft(X - 1)) { // Middle Left
    if (gImage->bitMap[Y][X - 1] == F) {
      gImage->bitMap[Y][X - 1] = T;
      fillR(X - 1, Y, T, F);
    }
  }
  if (!borderRight(X + 1)) { // Middle Right
    if (gImage->bitMap[Y][X + 1] == F) {
      gImage->bitMap[Y][X + 1] = T;
      fillR(X + 1, Y, T, F);
    }
  }
  if (!(borderLeft(X - 1) || borderBottom(Y + 1))) { // Bottom Left
    if (gImage->bitMap[Y + 1][X - 1] == F) {
      gImage->bitMap[Y + 1][X - 1] = T;
      fillR(X - 1, Y + 1, T, F);
    }
  }
  if (!borderBottom(Y + 1)) { // Bottom Middle
    if (gImage->bitMap[Y + 1][X] == F) {
      gImage->bitMap[Y + 1][X] = T;
      fillR(X, Y + 1, T, F);
    }
  }
  if (!(borderBottom(Y + 1) || borderRight(X + 1))) { // Bottom Right
    if (gImage->bitMap[Y + 1][X + 1] == F) {
      gImage->bitMap[Y + 1][X + 1] = T;
      fillR(X + 1, Y + 1, T, F);
    }
  }
}

void processLineF(void) {
  int X, Y;
  char T, F; // to : from
  
  fscanf(gInputFile, "%d %d %c", &X, &Y, &T);
  while (fgetc(gInputFile) != '\n');
  F = gImage->bitMap[Y][X];

  if (T == F) {
    fprintf (stderr, "Error: Cannot flip color %c to itself.\n", T);
  }
  else {
    fillR (X, Y, T, F);
  }

}

void processLineS(void) {
  const int kMaxLineLength = 81;
  char name[kMaxLineLength];

  fgetc(gInputFile); // strip space between 'S' and "name"
  fgets(name, kMaxLineLength, gInputFile);
    
  printf("%s", name);
  printImage();
}



bool processLine(int c) {

  switch (c) {
    case 'X':
      return false;
      break;
    case 'I':
      processLineI();
      return true;
      break;
    case 'C':
      processLineC();
      return true;
      break;
    case 'L':
      processLineL();
      return true;
      break;
    case 'V':
      processLineV();
      return true;
      break;
    case 'H':
      processLineH();
      return true;
      break;
    case 'K':
      processLineK();
      return true;
      break;
    case 'F':
      processLineF();
      return true;
      break;
    case 'S':
      processLineS();
      return true;
      break;
    default:
      fprintf (stderr, "Error: Unknown command %c\n\n", c);
      while (fgetc(gInputFile) != '\n'); // Ignore line
      return true;
      break;
  }
  
}