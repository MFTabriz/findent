#ifndef NLINE_PREP_H
#define NLINE_PREP_H

#include <iostream>
#include <string>
#include <vector>

#include "functions.h"

class Line_prep
{
   private:
      std::string line,sl,sv,sc,rest;
      char place_holder;


      struct whats
      {
	 int         type;
	 std::string value;
	 char        stringtype;
      };

      std::vector <whats> wv;

   public:

      enum { is_invalid, is_none, is_string, is_stlabel, is_dotop };

      Line_prep(const std::string s);

      Line_prep()                           {}

      void set_place_holder(const char c)   { place_holder = c; }

      char get_place_holder()               { return place_holder; }
      
      std::string get_line()                { return line; }

      std::string get_line_spaces_removed() { return sl; }

      std::string get_line_compressed()     { return sv; }

      std::string get_line_encoded()        { return sc; }

      std::string get_line_rest()           { return rest; }

      int get_type(const unsigned int i)
      {
	 if (i < wv.size())
	    return wv[i].type;
	 else
	    return is_invalid;
      }

      int get_type(const std::string &s) { return get_type(string2number<unsigned int>(s)); }

      std::string get_type_as_string(const unsigned int i)
      {
	 int k = get_type(i);

	 switch(k)
	 {
	    case is_invalid:
	       return ("invalid");
	    case is_none:
	       return ("none");
	    case is_string:
	       return ("string");
	    case is_stlabel:
	       return ("label");
	    case is_dotop:
	       return ("dotop");
	    default:
	       return ("impossible");
	 }
      }

      std::string get_type_as_string(const std::string &s)
      {
	 return get_type_as_string(string2number<unsigned int>(s));
      }

      std::string get_value(const unsigned i)
      {
	 if (i < wv.size())
	    return wv[i].value;
	 else
	    return "";
      }

      std::string get_value(const std::string &s)
      {
	 return get_value(string2number<unsigned int>(s));
      }

      char get_stringtype(const unsigned i)
      {
	 if (i < wv.size())
	    return wv[i].stringtype;
	 else
	    return ' ';
      }

      char get_stringtype(const std::string &s)
      {
	 return get_stringtype(string2number<unsigned int>(s));
      }

};
#endif
