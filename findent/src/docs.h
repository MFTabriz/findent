#ifndef DOCS_H
#define DOCS_H

#include <string>

class Docs
{
   public:
   bool print(int todo);
   private:
   void version();
   void usage(bool i);
   void vim_help();
   void vim_findent();
   void vim_fortran();
   void gedit_help();
   void gedit_external();
   void gedit_plugin();
   void gedit_plugin_py();
   void emacs_help();
   void emacs_findent();
   void readme();

   void manout(const std::string flag, const std::string txt, const bool doman);
   void replaceAll( std::string &s, const std::string &search, const std::string &replace );
};

#endif
