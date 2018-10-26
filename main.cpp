#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

bool AllocateMatrix(int **&a, const unsigned int rowsCount,
  const unsigned int columnsCount, const int start, const int rowIncrement,
  const int columnIncrement) {
  a = (int**)malloc(sizeof(int*)*rowsCount);
  if (a == NULL)
    return false;
  for (unsigned int u, i = 0; i < rowsCount; ++i) {
    a[i] = (int*)malloc(sizeof(int)*columnsCount);
    if(a[i] == NULL) {
      for (u = 0; u < i; ++u)
        free(a[u]);
      free(a);
      return false;
    }
    for (u = 0; u < columnsCount; ++u)
      a[i][u] = start + i*columnIncrement + u*rowIncrement;
  }
  return true;
}

void FreeMatrix(int **a, const unsigned int rowsCount) {
  for (unsigned int i = 0; i != rowsCount; ++i)
    free(a[i]);
  free(a);
}

void PrintMatrix(int **a, const unsigned int rowsCount,
  const unsigned int columnsCount) {
  for (unsigned int j, i = 0; i != rowsCount; ++i) {
    for (j = 0; j != columnsCount; ++j)
      printf("%4d%c", a[i][j], j == columnsCount - 1 ? '\n' : ' ');
  }
}

int main(void) {
  const unsigned short xM = 2, xN = 3, yM = 3, yN = 4;
  int **X = NULL, **Y = NULL, **Z = NULL;
  if(!AllocateMatrix(X, xM, xN, 1, 1, xN))
    goto MemoryFailure1;
  if (!AllocateMatrix(Y, yM, yN, 5, 1, 1))
    goto MemoryFailure2;
  Y[yM - 1][yN - 1] = 0;
  if (!AllocateMatrix(Z, xM, yN, 0, 0, 0))
    goto MemoryFailure3;

  for (size_t i = 0; i != xM; ++i) {
    for (size_t j = 0; j != yN; ++j) {
      for (size_t k = 0; k != xN; ++k) {
        Z[i][j] += X[i][k] * Y[k][j];
      }
    }
  }

  printf("X:\n");
  PrintMatrix(X, xM, xN);
  
  printf("\nY:\n");
  PrintMatrix(Y, yM, yN);
  
  printf("\nZ:\n");
  PrintMatrix(Z, xM, yN);

  FreeMatrix(X, xM);
  FreeMatrix(Y, yM);
  FreeMatrix(Z, xM);
  _getch();
  return 0;
MemoryFailure3:
  FreeMatrix(Y, yM);
MemoryFailure2:
  FreeMatrix(X, xM);
MemoryFailure1:
  printf("Error: memory failure");
  _getch();
  return -1;
}
