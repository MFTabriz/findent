#ifndef DOCS_H
#define DOCS_H

#include <string>

class Docs
{
   public:
   bool print(int todo);

   private:
   void emacs_findent();
   void emacs_help();
   void gedit_external();
   void gedit_help();
   void gedit_plugin();
   void gedit_plugin_py();
   void makefdeps();
   void readme();
   void usage(bool man);
   void version();
   void vim_findent();
   void vim_fortran();
   void vim_help();

   void manout(const std::string flag, const std::string txt);
   void replaceAll( std::string &s, const std::string &search, const std::string &replace );

   bool doman;
};

#endif
