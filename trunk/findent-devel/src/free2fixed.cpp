#include <iostream>
#include <string>
#include <sstream>

#include "debug.h"
#include "findent.h"
#include "findent_functions.h"
#include "free2fixed.h"
#include "free2free.h"
#include "fixed2fixed.h"
#include "findent_types.h"
#include "functions.h"

void free2fixed(lines_t &lines)
{
   lines_t fixedlines;

   free2free(lines, &fixedlines);
   fortranline::g_format(FIXED);
   fixed2fixed(fixedlines);
   fortranline::g_format(FREE);
}
