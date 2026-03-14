/* Copyright (c) 2015-2017  Jonathan Lisic 
 * License: GPL (>=2) 
 */  

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>
#include <R_ext/Rdynload.h>

#include "matchCount.h"
#include "conf_matrix.h"
/***********************************/
/* Register SO's                   */
/***********************************/

static R_NativePrimitiveArgType rMatchCount_t[] = {
  INTSXP, INTSXP, INTSXP,
  INTSXP, INTSXP, INTSXP
};

static const R_CMethodDef cMethods[] = {
    {"rMatchCount", (DL_FUNC) &rMatchCount, 6, rMatchCount_t},
    {"conf_matrix", (DL_FUNC) &conf_matrix, 3, NULL},
    {NULL, NULL, 0, NULL}
};

void R_init_myLib(DllInfo *info)
{
     R_registerRoutines(info, cMethods, NULL, NULL, NULL);
     R_useDynamicSymbols(info, TRUE); 
}
