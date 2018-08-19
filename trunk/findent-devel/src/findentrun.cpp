#include "findentclass.h"

int Findent::run(Flags &f)
{
   init(f);

   handle_reading_from_tty();

   if (input_format == UNKNOWN)
      input_format = determine_fix_or_free();

   fortranline::g_format(input_format);
   if (flags.only_fix_free)
   {
      std::cout << fortranline::g_format2txt() << std::endl;
      return what_to_return();
   }

   start_indent = flags.start_indent;

   output_format = flags.output_format;
   if(output_format == 0)
      output_format = input_format;

   init_indent();

   if (flags.last_usable_only)
   {
      mycout.setoutput(0);
      //handle_last_usable_only();
      return what_to_return();
   }
   return 0;

}

