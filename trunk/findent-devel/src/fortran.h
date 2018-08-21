#ifndef FORTRAN_H
#define FORTRAN_H

#include "nfindent_types.h"
#include "findentclass.h"
#include "nfortranline.h"
#include "readlines.h"
#include "simpleostream.h"
#include "pre_analyzer.h"
#include "ndebug.h"

class Fortran
{
   public:
      virtual ~Fortran(){}

      Fortran(Findent *f)
      {
	 fi = f;
      }

      virtual void build_statement(Fortranline &line, bool &f_more, bool &pushback) = 0;
      // replaces handle_free, handle_fixed
      //
      virtual void output(lines_t &lines,lines_t *freelines = 0) = 0;
      // replaces fixed2fixed/free2free
      //
      virtual void output_converted(lines_t &lines) = 0;
      // replaces fixed2free and free2fixed
      //
      void          handle_last_usable_only();
      int get() { return fi->testint; }

      int get_num()
      {
	 return fi->get_num_lines();
      }
   protected:

      lines_t          curlines;
      dolabels_store_t dolabels_store;
      dolabels_t       dolabels;        // to store labels, necessary for labelled do
      Findent*         fi;
      fs_store_t       fs_store;
      std::string      full_statement;
      indent_store_t   indent_store;    // to store indent store
      int              labellength;
      nbseen_store_t   nbseen_store;    // to store nbseen
      pre_analyzer     prea;
      Readlines        readlines;
      rprops_store_t   rprops_store;
      rprops_t         rprops;          // to store routines (module, subroutine ...)

      int M(const int k)
      {
	 //
	 // used to delimit indentation
	 //
	 if (fi->get_flags()->max_indent <= 0)
	    return k;
	 else
	    return std::min(fi->get_flags()->max_indent,k);
      }
      std::string statement() 
      { 
	 return full_statement; 
      }

      lines_t lines()
      {
	 return curlines;
      }
      void push_all()
      {
	 dolabels_store.push_back(dolabels);
	 indent_store.push_back(fi->get_indent());
	 nbseen_store.push_back(fi->get_nbseen());
	 rprops_store.push_back(rprops);

      }         // end of push_all

      void top_all()
      {
	 if (!dolabels_store.empty())
	    dolabels = dolabels_store.back();
	 if (!indent_store.empty())
	    //indent = indent_store.back();
	    fi->set_indent(indent_store.back());
	 if (!nbseen_store.empty())
	    //nbseen = nbseen_store.back();
	    fi->set_nbseen(nbseen_store.back());
	 if (!rprops_store.empty())
	    rprops = rprops_store.back();
      }         // end of top_all

      void pop_all()
      {
	 if (!dolabels_store.empty())
	    dolabels_store.pop_back();
	 if (!indent_store.empty())
	    indent_store.pop_back();
	 if (!nbseen_store.empty())
	    nbseen_store.pop_back();
	 if (!rprops_store.empty())
	    rprops_store.pop_back();

      }        // end of pop_all

      void        get_full_statement();
      void        handle_pre(Fortranline &line, const bool f_more, bool &p_more);
      void        handle_pre_light(Fortranline &line, bool &p_more);
      bool        is_findentfix(Fortranline &line);
      bool        output_pre(lines_t &lines, lines_t *outlines);

};

#endif
