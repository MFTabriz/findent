#include "findentclass.h"
#include "free.h"
#include "fixed.h"
#include "fortran.h"
#include "ndebug.h"

int Findent::run()
{

   handle_reading_from_tty();

   if (input_format == UNKNOWN)
      input_format = determine_fix_or_free();

   Fortranline::g_format(input_format);
   if (flags.only_fix_free)
   {
      std::cout << Fortranline::g_format2txt() << std::endl;
      return what_to_return();
   }

   start_indent = flags.start_indent;

   output_format = flags.output_format;
   if(output_format == 0)
      output_format = input_format;

   Fortran *source;
   switch (input_format)
   {
      case FREE: source = new Free(this); break;
      case FIXED: source = new Fixed(this); break;
   }

   init_indent();

   if (flags.last_usable_only)
   {
      mycout.setoutput(0);
      source->handle_last_usable_only();
      delete source;
      return what_to_return();
   }
   delete source;
   return 0;

}

