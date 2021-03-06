/*-------------- Telecommunications & Signal Processing Lab ---------------
                             McGill University

Routine:
  void VRfScale (double a, const float x[], float y[], int N)

Purpose:
  Multiply each element of a float array by a scalar value

Description:
  This routine multiplies each element of a float array by a scalar value,
    y[i] = a * x[i],  0 <= i < N.

Parameters:
   -> double a
      A scalar value
   -> const float x[]
      Input array (N elements)
  <-  float y[]
      Output array (N elements).  The output array can be the same as the
      input array.
   -> int N
      Number of elements in the arrays (may be zero).

Author / revision:
  J. Stachurski
  $Revision: 1.9 $  $Date: 2003/05/09 03:33:10 $

-------------------------------------------------------------------------*/

#include <libtsp.h>


void
VRfScale (double a, const float x[], float y[], int N)

{
  int i;

  for (i = 0; i < N; ++i)
    y[i] = (float) a * x[i];

  return;
}
