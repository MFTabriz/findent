#ifndef FLAGS_H
#define FLAGS_H
class Flags
{
   void set_defaults(void);
   void set_default_indents();

   public:

   Flags()
   {
      set_defaults();
   }

   int get_flags(int argc, char *argv[]);

   enum {
      DO_NOTHING = 1000,
      DO_CHANGETEAM,
      DO_CONCHAR,
      DO_DEPS,
      DO_EMACS_FINDENT,
      DO_EMACS_HELP,
      DO_GEDIT_EXTERNAL,
      DO_GEDIT_HELP,
      DO_GEDIT_PLUGIN,
      DO_GEDIT_PLUGIN_PY,
      DO_INCLUDE_LEFT,
      DO_INDENT,
      DO_INDENT_CONTAINS,
      DO_INPUT_FORMAT,
      DO_LABEL_LEFT,
      DO_LAST_INDENT,
      DO_LAST_USABLE,
      DO_MAKEFDEPS,
      DO_MANPAGE,
      DO_OMP,
      DO_README,
      DO_REFACTOR_PROCEDURE,
      DO_SEGMENT,
      DO_USAGE,
      DO_VERSION,
      DO_VIM_FINDENT,
      DO_VIM_FORTRAN,
      DO_VIM_HELP
   };

   bool apply_indent         ; // 1: output indented line, else output original lines
   bool auto_firstindent     ;
   char conchar              ; // continuation character output by fixed2fixed, see manpage
   bool deps                 ; // output dependencies only
   bool include_left         ; // 1: put include on the start of the line
   bool include_left_default ;
   bool indent_cont          ;
   bool indent_contain       ;
   bool input_format_gnu     ;
   bool label_left           ; // 1: put statement labels on the start of the line
   bool last_indent_only     ;
   bool last_usable_only     ;
   int  max_indent           ; // maximum allowed indent
   bool only_fix_free        ; // 1: determine only if fixed or free (-q)
   bool refactor_routines    ; // 1: refactor routine-end statements
   bool return_format        ; // 1: return 2 if format==free, 4 if format==fixed
   bool upcase_routine_type  ; // 1: use 'SUBROUTINE' etc in stead of 'subroutine'
   bool honour_omp           ; // 1: treat openmp continuation lines as code,
   //                             0: treat them as comment
   int all_indent;
   int associate_indent;
   int block_indent;
   int case_indent;
   int changeteam_indent;
   int cont_indent;
   int contains_indent;
   int critical_indent;
   int default_indent;
   int do_indent;
   int entry_indent;
   int enum_indent;
   int forall_indent;
   int if_indent;
   int input_format;
   int input_line_length;
   int interface_indent;
   int module_indent;
   int output_format;
   int routine_indent;
#ifdef USEESOPE
   int segment_indent;
#endif
   int select_indent; 
   int start_indent;
   int type_indent;
   int where_indent;
};
#endif
