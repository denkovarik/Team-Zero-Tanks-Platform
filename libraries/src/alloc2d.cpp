#include <cstring>

int** alloc2D(int rows, int cols)
{
  int i;

  // allocate a row of pointers
  int** twoD = new int* [rows];
  // if we can't get pointers return NULL instead
  if(twoD == NULL) return NULL;

  // allocate the columns below those rows
  int* twoCols = new int [ rows * cols ];
  //if we can't get columns, delete the pointers and return NULL
  if(twoCols == NULL)
  {
    delete [] twoD;
    return NULL;
  }

  // use memset to initizialize our entire data set to 0
  memset(twoCols, 0, rows * cols * sizeof(int));

  // Build the 2D array in a one line for loop.
  //i = our rows, and we use the number of columns to space out
  //where we set our pointers
  for(i = 0; i < rows; ++i, twoCols += cols)
    twoD[ i ] = twoCols;

  // and return the array
  return twoD;
}

// deallocate 2-D array
void free2D(int** twoD)
{
  //Check if it exists
  if(twoD)
  {
    //Because our array is a single array we can delete the entire
    //array at once and then remove the array of pointers after
    delete [] *twoD;
    delete [] twoD;
  }
}


