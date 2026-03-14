
#include "matchCount.h"


void rMatchCount( 
    int * pixel,           /* this is the raster image of assignments */ 
    int * match,           /* this is what to match against */ 
    int * assign,
    int * count,
    int * mPtr,     /* max number of matches */
    int * nPtr
    ) {
  
  size_t m = (size_t)*mPtr;

  size_t N = (size_t)*nPtr;

  size_t i,j; /* iterator */
  int index;
  size_t assignIndex;

  /* for each observation find another observation to replace it */
  for (i = 0; i < N; i++){ 
    index = pixel[i]; 

    if (pixel[i] >= 0) 
      if (match[i] >= 0)  {
        int done = 0;
        int matchVal = match[i];
        for (j = 0; j < m; j++) {
          assignIndex = index * m + j;
          int a = assign[assignIndex];
          int avail = (a < 0) | (a == matchVal);
          int take = avail & (1 - done);
          int mask = -take; /* 0 or -1 */
          assign[assignIndex] = (a & ~mask) | (matchVal & mask);
          count[assignIndex] += take;
          done |= take;
        }
      }
  }

  return;
}


