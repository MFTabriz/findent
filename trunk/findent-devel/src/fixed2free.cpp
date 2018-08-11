#include <string>
#include <vector>

#include "debug.h"
#include "findent.h"
#include "findent_functions.h"
#include "fixed2fixed.h"
#include "fortranline.h"
#include "free2free.h"

void fixed2free(lines_t &lines)
{
   lines_t freelines;

   ppp<<"fixed2free lines "<<lines<<endchar;

   fixed2fixed(lines, &freelines);
   ppp<<"fixed2free freelines "<<freelines<<endchar;
   fortranline::g_format(FREE);
   free2free(freelines);
   fortranline::g_format(FIXED);
}
