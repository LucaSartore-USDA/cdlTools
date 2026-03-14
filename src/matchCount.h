/* Copyright (c) 2015-2017  Jonathan Lisic 
 * License: GPL (>=2) 
 */  
#ifndef __MATCHCOUNT_H__
#define __MATCHCOUNT_H__

#include "myomp.h"
#include <stdio.h> 
#include <stdlib.h>
//#include <time.h>

/***********************************/
/* Function Prototypes             */
/***********************************/

void rMatchCount( 
    int * pixel,           /* this is the raster image of assignments */ 
    int * match,           /* this is what to match against */ 
    int * assign,
    int * count,
    int * mPtr,     /* max number of matches */
    int * nPtr
    ); 

#endif
