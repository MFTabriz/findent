#ifndef FORTRAN_H
#define FORTRAN_H

#include "findent_types.h"
#include "findentclass.h"
#include "fortranline.h"
#include "simpleostream.h"
#include "pre_analyzer.h"
#include "debug.h"

class Fortran
{
   public:
      virtual ~Fortran(){}

      Fortran(Findent *f)
      {
	 fi = f;
	 gl = f->gl;
	 cur_rprop          = empty_rprop;
	 curline            = new Fortranline(gl);
	 prev_props         = empty_rprop;
	 refactor_end_found = 0;
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
      void          get_full_statement();

      int get_num() { return fi->num_lines; }


      std::string      full_statement;
      void        indent_and_output();

   protected:

      lines_t          curlines;
      struct propstruct prev_props;
      dolabels_store_t dolabels_store;
      dolabels_t       dolabels;        // to store labels, necessary for labelled do
      Findent*         fi;
      fs_store_t       fs_store;
      Globals*         gl;
      indent_store_t   indent_store;    // to store indent store
      nbseen_store_t   nbseen_store;    // to store nbseen
      pre_analyzer     prea;
      rprops_store_t   rprops_store;
      rprops_t         rprops;          // to store routines (module, subroutine ...)
      bool              refactor_end_found;
      struct propstruct cur_rprop;
      Fortranline      *curline;

      int M(const int k)
      {
	 //
	 // used to delimit indentation
	 //
	 if (fi->flags.max_indent <= 0)
	    return k;
	 else
	    return std::min(fi->flags.max_indent,k);
      }

      Fortranline F(const std::string &s) { return Fortranline(gl,s); }

      std::string statement() { return full_statement; }

      lines_t lines() { return curlines; }

      int pop_indent() { if (fi->indent.empty()) return 0; fi->indent.pop_back(); return top_indent(); }

      int top_indent() { if (fi->indent.empty()) return 0; return fi->indent.back(); }

      int top_dolabel() { if (dolabels.empty()) return -1; return dolabels.back(); } 

      int pop_dolabel() { if (dolabels.empty()) return -1; dolabels.pop_back(); return top_dolabel(); }

      void push_indent(int p) { fi->indent.push_back(p); } 

      void empty_dolabels() { while(!dolabels.empty()) dolabels.pop_back(); }

      void push_rprops(struct propstruct p) { rprops.push_back(p); }

      void push_dolabel(int p) { dolabels.push_back(p); }

      struct propstruct top_rprops() { if (rprops.empty()) return empty_rprop; return rprops.back(); }
      struct propstruct pop_rprops() { if (rprops.empty()) return empty_rprop; rprops.pop_back(); return top_rprops(); }



      void push_all()
      {
	 dolabels_store.push_back(dolabels);
	 indent_store.push_back(fi->indent);
	 nbseen_store.push_back(fi->nbseen);
	 rprops_store.push_back(rprops);

      }         // end of push_all

      void top_all()
      {
	 if (!dolabels_store.empty())
	    dolabels = dolabels_store.back();
	 if (!indent_store.empty())
	    //indent = indent_store.back();
	    fi->indent=indent_store.back();
	 if (!nbseen_store.empty())
	    //nbseen = nbseen_store.back();
	    fi->nbseen=nbseen_store.back();
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

      void        handle_pre(Fortranline &line, const bool f_more, bool &p_more);
      bool        is_findentfix(Fortranline &line);
      bool        output_pre(lines_t &lines, lines_t *outlines);
      void        output_line();
      void handle_refactor();

};

#endif
