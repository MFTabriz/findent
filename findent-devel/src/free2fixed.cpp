#include "debug.h"
#include "findent_types.h"
#include "fixed2fixed.h"
#include "free2free.h"

void free2fixed(lines_t &lines)
{
   lines_t fixedlines;

   free2free(lines, &fixedlines);
   fortranline::g_format(FIXED);
   fixed2fixed(fixedlines);
   fortranline::g_format(FREE);
}
