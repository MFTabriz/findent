#include <iostream>
#include "docs.h"
#include "flags.h"
#include "version.h"
#include "functions.h"

bool Docs::print(int todo)
{
   switch(todo)
   {
      case Flags::DO_EMACS_FINDENT:
	 emacs_findent();
	 return 1;
      case Flags::DO_EMACS_HELP:
	 emacs_help();
	 return 1;
      case Flags::DO_GEDIT_EXTERNAL:
	 gedit_external();
	 return 1;
      case Flags::DO_GEDIT_HELP:
	 gedit_help();
	 return 1;
      case Flags::DO_GEDIT_PLUGIN:
	 gedit_plugin();
	 return 1;
      case Flags::DO_GEDIT_PLUGIN_PY:
	 gedit_plugin_py();
	 return 1;
      case Flags::DO_MAKEFDEPS:
	 makefdeps();
	 return 1;
      case Flags::DO_MANPAGE:
	 usage(1);
	 return 1;
      case Flags::DO_README:
	 readme();
	 return 1;
      case Flags::DO_USAGE:
	 usage(0);
	 return 1;
      case Flags::DO_VERSION:
	 std::cout << "findent version "<<VERSION<<std::endl;
	 return 1;
      case Flags::DO_VIM_FINDENT:
	 vim_findent();
	 return 1;
      case Flags::DO_VIM_FORTRAN:
	 vim_fortran();
	 return 1;
      case Flags::DO_VIM_HELP:
	 vim_help();
	 return 1;
      default:
	 return 0;
   }
}

void Docs::usage(bool man)
{

   if (man)
   {
      doman = 1;
      std::cout << ".\\\" DO NOT MODIFY THIS FILE! It was created by findent \\-H"                << std::endl;
      std::cout << ".TH FINDENT \"1\" \"2018\" \"findent\\-" << VERSION << "\" \"User Commands\"" << std::endl;
      std::cout << ".SH NAME"                                                                   << std::endl;
      std::cout << "findent \\- Indents and optionally converts Fortran program source"         << std::endl;
      std::cout << ".SH SYNOPSIS"                                                               << std::endl;
      std::cout << ".B findent"                                                                 << std::endl;
      std::cout << "[\\fIOPTION\\fR]..."                                                        << std::endl;
      std::cout << ".PP"                                                                        << std::endl;
      std::cout << "Findent reads from STDIN and writes to STDOUT."                             << std::endl;
      std::cout << ".SH DESCRIPTION"                                                            << std::endl;
      std::cout << "Findent indents a Fortran source. Findent uses various kinds of"            << std::endl;
      std::cout << "indentations, see OPTIONS. Findent can convert from fixed form to"          << std::endl;
      std::cout << "free form, and can supplement single END statements, see 'Refactor' below." << std::endl;
      std::cout << "Comment lines with '!' in column one are not indented."                     << std::endl;
      std::cout << " You can correct findent related indenting errors by inserting comment"     << std::endl;
      std::cout << "lines: "                                                                    << std::endl;
      std::cout << " !  findentfix: <fortran statement>"                                        << std::endl;
      std::cout << " where <fortran statement> is for example DO, END, WHERE() etcetera."       << std::endl;
      std::cout << "Findent will adjust the indentation according to <fortran statement>."      << std::endl;
      std::cout << " Errors in OPTIONS are silently ignored."                                   << std::endl;
      std::cout << ".PP" << std::endl << ".SS \"General options:"                               << std::endl;
   }
   else
   {
      doman = 0;
      std::cout << "findent [options]"                                                        << std::endl;
      std::cout << "   Format fortran source."                                                << std::endl;
      std::cout << "   Findent reads from STDIN, writes to STDOUT."                            << std::endl;
      std::cout << "   Findent uses various kinds of indentations, see OPTIONS."              << std::endl;
      std::cout << "   Findent can convert from fixed form to free form and vice versa and"   << std::endl;
      std::cout << "   can supplement END statements, see 'Refactor' below."                  << std::endl;
      std::cout << "   Comment lines with '!' in column one are not indented."                << std::endl;
      std::cout << "   You can correct findent related indenting errors by"                   << std::endl;
      std::cout << "   inserting comment lines: "                                             << std::endl;
      std::cout << "    !  findentfix: <fortran statement>"                                   << std::endl;
      std::cout << "   where <fortran statement> is for example DO, END, WHERE() etcetera."   << std::endl;
      std::cout << "   Findent will adjust the indentation according to <fortran statement>." << std::endl;
      std::cout << "OPTIONS (errors are silently ignored):"                                   << std::endl;
      std::cout                                                                               << std::endl;
      std::cout << "  General options:"                                                       << std::endl;
      std::cout                                                                               << std::endl;
   }

   manout(" ","Below: <n> denotes an unsigned decimal number.");
   manout(" ","       <c> denotes a character.");
   manout(" "," ");
   manout(" ","In the long options, you can replace '_' with '-'.");
   if (!doman)
      std::cout << std::endl;
   manout("-h, --help"                       ,"print this text");
   manout("-H, --manpage"                    ,"print man page");
   manout("--readme"                         ,"print some background information");
   manout("-v, --version"                    ,"prints findent version");
   manout("-q, --query_fix_free"             ,"guess free or fixed, prints 'fixed' or 'free' and exits");
   //manout("-Q","returncode=2 for free, 4 for fixed");
   //manout(" ","      (for usage with vim)");
   manout("--continuation=<c>"               ," ' ': (default) do not change continuation characters");
   manout(" "," '0': create numbered continuation characters");
   manout(" "," other: use that continuation character");
   manout(" "," default for conversion from free to fixed is '&'");
   manout("--include_left=<n>"               ,"(0/1) 1: indent include statements to starting indent (default:0)");
   manout("-l<n>, --label_left=<n>"          ,"(0/1) 1: move statement labels to start of line (default:1)");
   manout(" ","      (only for free format)");
   manout("-lastindent, --last_indent"       ,"prints computed indentation of last line");
   manout(" ","      (for usage with vim)");
   manout("-lastusable, --last_usable"       ,"prints line number of last line usable");
   manout(" ","      as start for indenting(for usage with vim)");
   manout("-iauto, --input_format=auto"      ,"determine automatically input format (free or fixed)");
   manout("-ifixed, --input_format=fixed"    ,"force input format fixed");
   manout(" ","(default: auto)");
   manout("-ifree, --input_format=free"      ,"force input format free");
   manout(" ","(default: auto)");
   manout("-i-, --indent=none"               ,"do not change indent (useful in combination with -R)");
   manout("-L<n>, --input_line_length=<n>"   ,"use only first <n> characters of each line");
   manout(" ","default=0: take whole lines");
   manout("-L<n>g, --input_line_length=<n>g" ,"same as above, but use gfortran convention");
   manout(" ","for counting the characters with tabbed lines");
   manout(" "," example: --input_line_length=72g");
   manout("-M<n>, --max_indent=<n>"          ,"maximum output indent, default 100, 0: no limit");
   manout("-ofixed, --output_format=fixed"   ,"force fixed format output");
   manout("-ofree, --output_format=free"     ,"force free format output");
   manout("-osame, --output_format=same"     ,"output format same is input format");
   manout("--openmp=<n>"                     ," 0: do not indent openmp conditionals");
   manout(" "," 1: indent openmp conditionals (default)");
   manout(" "," NOTE: for free format, the omp sentinel must be '!$ '");
   manout("-Rr, --refactor_procedures"       ,"refactor procedures and modules: the END line");
   manout(" "," of a subroutine, program etc. is, if possible, replaced by");
   manout(" "," 'end subroutine <name>' or");
   manout(" "," 'end function <name>' or");
   manout(" "," 'end procedure <name>' or");
   manout(" "," 'end program <name>' or");
   manout(" "," 'end block data <name>' or");
   manout(" "," 'end module <name>' or");
   manout(" "," 'end submodule <name>'");
   manout(" "," where <name> is the name of the appropriate procedure, subroutine etc.");
   manout(" "," NOTE1: if the END line contains a continuation the results are undefined");
   manout(" "," NOTE2: a line like 'end function fun' will be replaced by");
   manout(" ","        'end subroutine sub' if the END line ends 'subroutine sub'");
   manout("-RR, --refactor_procedures=upcase","same as -Rr, but 'END SUBROUTINE <name>'");
   manout(" ","in stead of 'end subroutine <name>' etc.");
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS \"Indenting options:" << std::endl;
   }
   else
   {
      std::cout << std::endl;
      std::cout << "  Indenting options:"                           << std::endl;
      std::cout << std::endl;
   }
   manout("-I<n>, --start_indent=<n>"       ,"starting  indent (default:0)");
   manout("-Ia, --start_indent=a"           ,"determine starting indent from first line");
   Flags f;
   manout("-i<n>, --indent=<n>"             ,"all       indents except I,c,C,e (default: "+number2string(f.default_indent)+")");
   manout("-a<n>, --indent_associate=<n>"   ,"ASSOCIATE    indent");
   manout("-b<n>, --indent_block=<n>"       ,"BLOCK        indent");
   manout("-d<n>, --indent_do=<n>"          ,"DO           indent");
   manout("-f<n>, --indent_if=<n>"          ,"IF           indent");
   manout("-E<n>, --indent_enum=<n>"        ,"ENUM         indent");
   manout("-F<n>, --indent_forall=<n>"      ,"FORALL       indent");
   manout("-j<n>, --indent_interface=<n>"   ,"INTERFACE    indent");
   manout("-m<n>, --indent_module=<n>"      ,"MODULE       indent");
   manout("-r<n>, --indent_procedure=<n>"   ,"FUNCTION,");
   manout(" ",  " SUBROUTINE and PROGRAM indent");
   manout("-s<n>, --indent_select=<n>"      ,"SELECT       indent");
   manout("-t<n>, --indent_type=<n>"        ,"TYPE         indent");
   manout("-w<n>, --indent_where=<n>"       ,"WHERE        indent");
   manout("-x<n>, --indent_critical=<n>"    ,"CRITICAL     indent");
   manout("--indent_changeteam=<n>     "    ,"CHANGE TEAM  indent");
   manout("-C-, --indent_contains=restart, ","restart indent after CONTAINS");
   manout("-k<n>, --indent_continuation=<n>","continuation indent except   " );
   manout(" ","  for lines starting with '&'");
   manout(" ","     free to free only");
   manout("-k-, --indent_continuation=none" ,"continuation lines not preceded");
   manout(" ","  by '&' are untouched");
   manout(" ","     free to free only");
   manout("  ","next defaults are: all - all/2");
   manout("-c<n>, --indent_case=<n>"        ,"CASE      negative indent");
   manout("-C<n>, --indent_contains=<n>"    ,"CONTAINS  negative indent");
   manout("-e<n>, --indent_entry=<n>"       ,"ENTRY     negative indent");
   manout(" "," ");
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS" << std::endl;
   }
   std::cout << "Dependencies:"                << std::endl;
   manout("--deps","output dependency information only, other flags are ignored.");
   manout(" ","This can be used to generate a dependencies file for usage with make(1).");
   manout(" "," The format of this information:");
   manout(" "," Fortran source     ->        findent output");
   manout(" ","  include \"file1\"   ->        inc file1");
   manout(" ","  #include \"file2\"  ->        cpp file2");
   manout(" ","  #include <file3>  ->        std file3");
   manout(" ","  ??inclue 'file4'  ->        coc file4");
   manout(" ","  use module1       ->        use module1");
   manout(" ","  submodule(m) subm ->        use m");
   manout(" ","                              mod m:subm");
   manout(" ","  module module2    ->        mod module2");
   manout("--makefdeps","outputs a bash(1) script that serves as a an example");
   manout(" "," to generate dependencies for use in make(1).");
   manout(" "," ");
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS \"Usage with vim:" << std::endl;
   }
   else
   {
      std::cout << "Usage with vim:" << std::endl;
   }
   manout("--vim_help"     ,"outputs directions to use findent in (g)vim");
   manout("--vim_fortran"  ,"outputs file 'fortran.vim', see --vim_help");
   manout("--vim_findent"  ,"outputs file 'findent.vim', see --vim_help"); 
   manout(" "," ");
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS \"Usage with gedit:" << std::endl;
   }
   else
   {
      std::cout << "Usage with gedit:" << std::endl;
   }
   manout("--gedit_help"      ,"outputs directions to use findent in gedit");
   manout("--gedit_external"  ,"outputs script 'findent-gedit', see --gedit_help");
   manout("--gedit_plugin"    ,"outputs file 'findent.plugin', see --gedit_help");
   manout("--gedit_plugin_py" ,"outputs file 'python.py', see --gedit_help");
   manout(" "," ");
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS \"Usage with emacs:" << std::endl;
   }
   else
   {
      std::cout << "  Usage with emacs:" << std::endl;
   }
   manout("--emacs_help"      ,"outputs directions to use findent in emacs");
   manout("--emacs_findent"   ,"outputs script 'findent.el', see --emacs_help");
   manout(" "," ");
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS" << std::endl;
   }
   std::cout << "Examples:"                    << std::endl;
   manout(" ","indent: findent < in.f > out.f");
   manout(" ","        findent -i2 -r0 < in.f > out.f");
   manout(" ","");
   manout(" ","convert fixed to free form: findent -ofree < prog.f > prog.f90");
   manout(" ","");
   manout(" ","convert free to fixed form: findent -ofixed < prog.f90 > prog.f");
   manout(" ","");
   manout(" ","refactor 'end': findent -Rr < in.f90 > out.f90");
   if(doman)
   {
      std::cout << ".SH COPYRIGHT" << std::endl;
      std::cout << ".br"           << std::endl;
   }
   else
   {
      std::cout << "COPYRIGHT"     << std::endl;
   }
   std::cout << "This is free software; see the source for copying conditions.  There is NO"  <<std::endl;
   std::cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." <<std::endl;
}

void Docs::replaceAll( std::string &s, const std::string &search, const std::string &replace ) 
{
   //
   // https://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c
   //
   for( size_t pos = 0; ; pos += replace.length() ) {
      //
      // Locate the substring to replace
      //
      pos = s.find( search, pos );
      if( pos == std::string::npos ) break;
      //
      // Replace by erasing and inserting
      //
      s.erase( pos, search.length() );
      s.insert( pos, replace );
   }
}

//
// doman == 1: output in man page format
// flag: " ": normal continuation line
//       otherwize : skip to new paragraph and use bold format
// txt: Line to output
//
void Docs::manout(const std::string flag, const std::string txt)
{

   if (doman)
   {
      std::string mantxt  = txt;
      std::string manflag = flag;
      replaceAll(mantxt,"-","\\-");
      replaceAll(manflag,"-","\\-");
      if (manflag == " ")
	 std::cout << mantxt << std::endl;
      else
      {
	 std::cout << ".TP" << std::endl << "\\fB"<<manflag<<"\\fR"<<std::endl;
	 std::cout << mantxt << std::endl;
      }
   }
   else
   {
      if (flag == " ")
	 std::cout << flag << "\t" << "  " << txt << std::endl;
      else
	 std::cout << flag << "\t" << ": " << txt << std::endl;
   }
}

void Docs::vim_help()
{
#include "vim_help.inc"
}

void Docs::vim_findent()
{
#include "vim_findent.inc"
}

void Docs::vim_fortran()
{
#include "vim_fortran.inc"
}

void Docs::gedit_help()
{
#include "gedit_help.inc"
}

void Docs::gedit_external()
{
#include "gedit_external.inc"
}

void Docs::gedit_plugin()
{
#include "gedit_plugin.inc"
}

void Docs::gedit_plugin_py()
{
#include "gedit_plugin_py.inc"
}

void Docs::emacs_help()
{
#include "emacs_help.inc"
}

void Docs::emacs_findent()
{
#include "emacs_findent.inc"
}

void Docs::readme()
{
#include "readme.inc"
}

void Docs::makefdeps()
{
#include "makefdeps.inc"
}
