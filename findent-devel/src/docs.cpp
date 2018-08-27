#include <iostream>
#include "docs.h"
#include "flags.h"
#include "version.h"
#include "functions.h"

bool Docs::print(int todo)
{
   switch(todo)
   {
      case Flags::DO_VERSION:
	 std::cout << "findent version "<<VERSION<<std::endl;
	 return 1;
      case Flags::DO_USAGE:
	 usage(0);
	 return 1;
      case Flags::DO_MANPAGE:
	 usage(1);
	 return 1;
      case Flags::DO_VIM_HELP:
	 vim_help();
	 return 1;
      case Flags::DO_VIM_FINDENT:
	 vim_findent();
	 return 1;
      case Flags::DO_VIM_FORTRAN:
	 vim_fortran();
	 return 1;
      case Flags::DO_GEDIT_HELP:
	 gedit_help();
	 return 1;
      case Flags::DO_GEDIT_EXTERNAL:
	 gedit_external();
	 return 1;
      case Flags::DO_GEDIT_PLUGIN:
	 gedit_plugin();
	 return 1;
      case Flags::DO_GEDIT_PLUGIN_PY:
	 gedit_plugin_py();
	 return 1;
      case Flags::DO_EMACS_HELP:
	 emacs_help();
	 return 1;
      case Flags::DO_EMACS_FINDENT:
	 emacs_findent();
	 return 1;
      case Flags::DO_README:
	 readme();
	 return 1;
      default:
	 return 0;
   }
}

void Docs::usage(const bool doman)
{

   if (doman)
   {
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
      std::cout << "findent [options]"                                                        << std::endl;
      std::cout << "   Format fortran source."                                                << std::endl;
      std::cout << "   Findent eads from STDIN, writes to STDOUT."                            << std::endl;
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

   manout(" ","Below: <n> denotes an unsigned decimal number."                                             ,doman);
   manout(" ","       <c> denotes a character."                                                            ,doman);
   manout(" "," ",doman);
   manout(" ","In the long options, you can replace '_' with '-'."                                         ,doman);
   if (!doman)
      std::cout << std::endl;
   manout("-h, --help"                       ,"print this text"                                            ,doman);
   manout("-H, --manpage"                    ,"print man page"                                             ,doman);
   manout("--readme"                         ,"print some background information"                          ,doman);
   manout("-v, --version"                    ,"prints findent version"                                     ,doman);
   manout("-q, --query_fix_free"             ,"guess free or fixed, prints 'fixed' or 'free' and exits"    ,doman);
   //manout("-Q","returncode=2 for free, 4 for fixed",                      doman);
   //manout(" ","      (for usage with vim)",                               doman);
   manout("--continuation=<c>"               ," ' ': (default) do not change continuation characters"       ,doman);
   manout(" "," '0': create numbered continuation characters"                                              ,doman);
   manout(" "," other: use that continuation character"                                                    ,doman);
   manout(" "," default for conversion from free to fixed is '&'"                                          ,doman);
   manout("-l<n>, --label_left=<n>"          ,"(0/1) 1: move statement labels to start of line (default:1)",doman);
   manout(" ","      (only for free format)"                                                               ,doman);
   manout("-lastindent, --last_indent"       ,"prints computed indentation of last line"                   ,doman);
   manout(" ","      (for usage with vim)"                                                                 ,doman);
   manout("-lastusable, --last_usable"       ,"prints line number of last line usable"                     ,doman);
   manout(" ","      as start for indenting(for usage with vim)"                                           ,doman);
   manout("-iauto, --input_format=auto"      ,"determine automatically input format (free or fixed)"       ,doman);
   manout("-ifixed, --input_format=fixed"    ,"force input format fixed"                                   ,doman);
   manout(" ","(default: auto)"                                                                            ,doman);
   manout("-ifree, --input_format=free"      ,"force input format free"                                    ,doman);
   manout(" ","(default: auto)"                                                                            ,doman);
   manout("-i-, --indent=none"               ,"do not change indent (useful in combination with -R)"       ,doman);
   manout("-L<n>, --input_line_length=<n>"   ,"use only first <n> characters of each line"                 ,doman);
   manout(" ","default=0: take whole lines"                                                                ,doman);
   manout("-L<n>g, --input_line_length=<n>g" ,"same as above, but use gfortran convention"                 ,doman);
   manout(" ","for counting the characters with tabbed lines"                                              ,doman);
   manout(" "," example: --input_line_length=72g"                                                          ,doman);
   manout("-M<n>, --max_indent=<n>"          ,"maximum output indent, default 100, 0: no limit"            ,doman);
   manout("-ofixed, --output_format=fixed"   ,"force fixed format output"                                  ,doman);
   manout("-ofree, --output_format=free"     ,"force free format output"                                   ,doman);
   manout("-osame, --output_format=same"     ,"output format same is input format"                         ,doman);
   manout("-Rr, --refactor_procedures"       ,"refactor procedures and modules: the END line"              ,doman);
   manout(" "," of a subroutine, program etc. is, if possible, replaced by"                                ,doman);
   manout(" "," 'end subroutine <name>' or"                                                                ,doman);
   manout(" "," 'end function <name>' or"                                                                  ,doman);
   manout(" "," 'end procedure <name>' or"                                                                 ,doman);
   manout(" "," 'end program <name>' or"                                                                   ,doman);
   manout(" "," 'end block data <name>' or"                                                                ,doman);
   manout(" "," 'end module <name>' or"                                                                    ,doman);
   manout(" "," 'end submodule <name>'"                                                                    ,doman);
   manout(" "," where <name> is the name of the appropriate procedure, subroutine etc."                    ,doman);
   manout(" "," NOTE1: if the END line contains a continuation the results are undefined"                  ,doman);
   manout(" "," NOTE2: a line like 'end function fun' will be replaced by"                                 ,doman);
   manout(" ","        'end subroutine sub' if the END line ends 'subroutine sub'"                         ,doman);
   manout("-RR, --refactor_procedures=upcase","same as -Rr, but 'END SUBROUTINE <name>'"                   ,doman);
   manout(" ","in stead of 'end subroutine <name>' etc."                                                   ,doman);
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
   manout("-I<n>, --start_indent=<n>"       ,"starting  indent (default:0)"                                                 ,doman);
   manout("-Ia, --start_indent=a"           ,"determine starting indent from first line"                                    ,doman);
   Flags f;
   manout("-i<n>, --indent=<n>"             ,"all       indents except I,c,C,e (default: "+number2string(f.default_indent)+")",doman);
   manout("-a<n>, --indent_associate=<n>"   ,"ASSOCIATE    indent"                                                          ,doman);
   manout("-b<n>, --indent_block=<n>"       ,"BLOCK        indent"                                                          ,doman);
   manout("-d<n>, --indent_do=<n>"           ,"DO           indent"                                                          ,doman);
   manout("-f<n>, --indent_if=<n>"          ,"IF           indent"                                                          ,doman);
   manout("-E<n>, --indent_enum=<n>"        ,"ENUM         indent"                                                          ,doman);
   manout("-F<n>, --indent_forall=<n>"      ,"FORALL       indent"                                                          ,doman);
   manout("-j<n>, --indent_interface=<n>"   ,"INTERFACE    indent"                                                          ,doman);
   manout("-m<n>, --indent_module=<n>"      ,"MODULE       indent"                                                          ,doman);
   manout("-r<n>, --indent_procedure=<n>"   ,"FUNCTION and"                                                                 ,doman);
   manout(" ",  " SUBROUTINE  indent"                                                                                       ,doman);
   manout("-s<n>, --indent_select=<n>"      ,"SELECT       indent"                                                          ,doman);
   manout("-t<n>, --indent_type=<n>"        ,"TYPE         indent"                                                          ,doman);
   manout("-w<n>, --indent_where=<n>"       ,"WHERE        indent"                                                          ,doman);
   manout("-x<n>, --indent_critical=<n>"    ,"CRITICAL     indent"                                                          ,doman);
   manout("-C-, --indent_contains=restart, ","restart indent after CONTAINS"                                                ,doman);
   manout("-k<n>, --indent_continuation=<n>","continuation indent except   "                                                ,doman);
   manout(" ","  for lines starting with '&'"                                                                               ,doman);
   manout(" ","     free to free only"                                                                                      ,doman);
   manout("-k-, --indent_continuation=none" ,"continuation lines not preceded"                                              ,doman);
   manout(" ","  by '&' are untouched"                                                                                      ,doman);
   manout(" ","     free to free only"                                                                                      ,doman);
   manout("  ","next defaults are: all - all/2"                                                                             ,doman);
   manout("-c<n>, --indent_case=<n>"        ,"CASE      negative indent"                                                    ,doman);
   manout("-C<n>, --indent_contains=<n>"    ,"CONTAINS  negative indent"                                                    ,doman);
   manout("-e<n>, --indent_entry=<n>"       ,"ENTRY     negative indent"                                                    ,doman);
   manout(" "," "                                                                                                           ,doman);
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS \"Usage with vim:" << std::endl;
   }
   else
   {
      std::cout << "  Usage with vim:" << std::endl;
   }
   manout("--vim_help"     ,"outputs directions to use findent in (g)vim" ,doman);
   manout("--vim_fortran"  ,"outputs file 'fortran.vim', see --vim_help"  ,doman);
   manout("--vim_findent"  ,"outputs file 'findent.vim', see --vim_help"  ,doman); 
   manout(" "," "                                                         ,doman);
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS \"Usage with gedit:" << std::endl;
   }
   else
   {
      std::cout << "  Usage with gedit:" << std::endl;
   }
   manout("--gedit_help"      ,"outputs directions to use findent in gedit"       ,doman);
   manout("--gedit_external"  ,"outputs script 'findent-gedit', see --gedit_help" ,doman);
   manout("--gedit_plugin"    ,"outputs file 'findent.plugin', see --gedit_help"  ,doman);
   manout("--gedit_plugin_py" ,"outputs file 'python.py', see --gedit_help"       ,doman);
   manout(" "," "                                                                 ,doman);
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS \"Usage with emacs:" << std::endl;
   }
   else
   {
      std::cout << "  Usage with emacs:" << std::endl;
   }
   manout("--emacs_help"      ,"outputs directions to use findent in emacs"       ,doman);
   manout("--emacs_findent"   ,"outputs script 'findent.el', see --emacs_help"    ,doman);
   manout(" "," "                                                                 ,doman);
   if(doman)
   {
      std::cout << ".PP" << std::endl << ".SS" << std::endl;
   }
   std::cout << "Examples:"                    << std::endl;
   manout(" ","indent: findent < in.f > out.f"                                  ,doman);
   manout(" ","        findent -i2 -r0 < in.f > out.f"                          ,doman);
   manout(" ",""                                                                ,doman);
   manout(" ","convert fixed to free form: findent -ofree < prog.f > prog.f90"  ,doman);
   manout(" ",""                                                                ,doman);
   manout(" ","convert free to fixed form: findent -ofixed < prog.f90 > prog.f" ,doman);
   manout(" ",""                                                                ,doman);
   manout(" ","refactor 'end': findent -Rr < in.f90 > out.f90"                  ,doman);
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
void Docs::manout(const std::string flag, const std::string txt, const bool doman)
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
