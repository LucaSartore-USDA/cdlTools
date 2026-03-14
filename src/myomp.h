/*  CLANG-compatible OpenMP support header file
    Copyright (C) 2025  Luca Sartore, Ph.D.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/agpl-3.0.html>
*/

#ifndef __MYOMP_H__
#define __MYOMP_H__

#if defined _OPENMP
  #if (_OPENMP > 200800)
    #ifdef __clang__
    #define __VOPENMP 0
    #else
    #include <omp.h>
    #define __VOPENMP 1
    #endif
  #endif
#else
  #define __VOPENMP 0
#endif

#if __VOPENMP
  #define _pragma(X) _Pragma(#X)
#else
  #define _pragma(X)
#endif

#endif