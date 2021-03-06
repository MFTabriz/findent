%{
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <iomanip>
#include <unistd.h>
#include <algorithm>
#include <string.h>
using namespace std;
#include "findent.h"
#include "version.h"
extern "C" FILE *yyin;
string mygetline();
void get_full_statement();
bool handle_free(string s);
int remove_trailing_comment(string &s);
bool handle_fixed(string s);
void output_line();
int pop_indent();
int top_indent();
void push_indent(int p);
void init_indent();
string whatprop(struct rstruct p);
string stoupper(const string s);

void push_rprops(struct rstruct p);
void init_rprops();
struct rstruct pop_rprops();
struct rstruct top_rprops();
const  struct rstruct empty_rprop={0,""};

void handle_pre(const string s);

void shorten_full_statement();

void handle_reading_from_tty();

int pop_dolabel();
int top_dolabel();
void push_dolabel(int l);
void empty_dolabels();

void set_default_indents();
void usage();
string trim(const string& str);
string rtrim(const string& str);
string ltab2sp(const string& s);
string handle_dos(const string s);

int input_format, output_format;
int guess_indent(const string str);
bool reading_from_tty = 0;
int lines_read        = 0;
int input_line_length = 0;
bool input_format_gnu = 0;
int determine_fix_or_free(const bool store);
bool isfixedcmt(const string s);
char fixedmissingquote(const string s);

stack<int> indent;                 // to store indents
stack<stack <int> > indent_stack;  // to store indent stack
stack<bool> pre_stack;             // to note if there is an #else after #if for indenting
stack<bool> prep_stack;            // to note if there is an #else after #if for routines

stack<struct rstruct> rprops;     // to store routines (module, subroutine ...)
stack<stack <struct rstruct> > rprops_stack;
struct rstruct cur_rprop = empty_rprop;

int cur_indent, start_indent;
bool auto_firstindent;
int num_lines;                    // number of lines read sofar
bool non_blank_line_seen;
bool indent_handled;

stack<int> dolabels;          // to sotre labels, necessary for labelled do
int stlabel;
int labelleng;

string full_statement;        // current statement, including continuation lines, &'s removed
deque <string> lines;         // current line, one continuation line per item
queue <string> linebuffer;    // used when determining fixed or free
stack <string> linestack;     // used for fixed format
bool full_statement_has_been_output;
bool stlabel_found;
bool end_of_file;

string endline   = "\n";
bool endline_set = 0;
const int default_indent = 3;
int all_indent;
int routine_indent, module_indent;
int do_indent;
int entry_indent;
int select_indent, case_indent;
int contains_indent;
int if_indent;
int where_indent;
int associate_indent;
int type_indent;
int forall_indent;
int interface_indent;
int block_indent;
int critical_indent;
int enum_indent;

bool label_left;            // 1: put statement labels on the start of the line
const bool label_left_default = 1;

bool refactor_routines = 0; // 1: refactor routine-end statements
bool upcase_routine_type = 0; // 1: use 'SUBROUTINE' etc in stead of 'subroutine'

bool simple_end_found  = 0;

bool cur_semi_eol;

%}

%code requires {
    struct lablen {
        int ival;      // name of label
        int ilen;      // length of label name
    };
}

%union {
  struct lablen val;
  bool semi_eol;
  }

%token ROUTINESTART DOSTART MODULESTART SELECTSTART ENDSELECT CASE
%token CONTAINS IFCONSTRUCT WHERECONSTRUCT FORALLCONSTRUCT
%token ELSE ELSEIF ENTRY ELSEWHERE INTERFACE BLOCK CRITICAL
%token ENUM TYPECONSTRUCT ASSOCIATECONSTRUCT
%token FREE FIXED PROBFREE PROBFIXED UNSURE FINDFORMAT
%token CMT SCANSTRCMT DQUOTE SQUOTE UNTERMSTR

%token GENERIC_END SPECIFIC_END ROUTINE_END UNKNOWN_END

%token KIND_SUBROUTINE KIND_FUNCTION KIND_PROGRAM KIND_BLOCKDATA KIND_MODULE 

%token <val> STLABEL
%token <val> DOLABEL

%token <semi_eol> EOL

%%
program:   program line
         | line
	 ;

line:    STLABEL
			 {  // STATEMENT LABEL
			    D(O("STLABEL line ");O($1.ival); O(top_dolabel());)
			    stlabel_found = 1;
			    stlabel       = $1.ival;
			    labelleng     = $1.ilen;

			    if (stlabel >=0)
			    {
			       while ( top_dolabel() == stlabel )
			       {
				  pop_indent();
				  pop_dolabel();
			          cur_indent = top_indent();
				  indent_handled = 1;
			       }
			       shorten_full_statement();
			     }
			 }
	   nolabelline
         | nolabelline    {
	                     D(O("nolabelline"));
			  }
         | error          {
	                     output_line();
			     cout << "! findent error in previous line, maybe misformatted"<<endline;
			     yyclearin;
	                     yyerrok;
			  }

nolabelline:
           EOL            {  // EOL END OF LINE or ;
	                     D(O("EOL");O($1);O("lexer_position 1");O(lexer_position))
			     cur_semi_eol = $1;
			     output_line();
	                     D(O("EOL");O($1);O("lexer_position 2");O(lexer_position))
			     if(cur_semi_eol)
			        shorten_full_statement();
			     labelleng  = 0;
			     cur_indent = top_indent();
			     D(O("top_indent:");O(top_indent());O("cur_indent:");O(cur_indent););
			  }
         | ROUTINESTART   {  // ROUTINE
	                     D(O("ROUTINESTART");O(whatprop(rprop));O(rprop.name);)
	                     cur_indent = top_indent();
			     D(O("cur_indent:");O(cur_indent);)
			     push_indent(cur_indent + routine_indent);
			     empty_dolabels();
			     push_rprops(rprop);
			  }
         | MODULESTART    {  // MODULE
	                     D(O("MODULESTART");O(whatprop(rprop));O(rprop.name);)
	                     cur_indent = top_indent();
			     D(O("cur_indent:");O(cur_indent);)
			     push_indent(cur_indent + module_indent);
			     empty_dolabels();
			     push_rprops(rprop);
			  }
         | BLOCK          {  // BLOCK
	                     D(O("BLOCK");)
	                     cur_indent = top_indent();
			     push_indent(cur_indent + block_indent);
			  }
         | CRITICAL       {  // CRITICAL
	                     D(O("CRITICAL");)
	                     cur_indent = top_indent();
			     push_indent(cur_indent + critical_indent);
			  }
         | ENUM           {  // ENUM
	                     D(O("ENUM");)
			     cur_indent = top_indent();
			     push_indent(cur_indent + enum_indent);
			     empty_dolabels();
			  }
         | INTERFACE      {  //INTERFACE
	                     D(O("INTERFACE");)
	                     cur_indent = top_indent();
			     push_indent(cur_indent + interface_indent);
			     empty_dolabels();
			  }
	 | DOSTART DOLABEL  { // LABELLED DO
			     D(O("DOSTART LABEL");O($2.ival);)
			     push_dolabel($2.ival);
	                     cur_indent = top_indent();
			     push_indent(cur_indent + do_indent);
	                  }
         | DOSTART        {  // labeled or unlabeled do
			     D(O("DOSTART");)
	                     cur_indent = top_indent();
			     push_indent(cur_indent + do_indent);
			  }
         | SELECTSTART    {  // SELECT CASE
			     D(O("SELECTSTART");)
	                     cur_indent = top_indent();
			     push_indent(cur_indent + select_indent);
			  }
	 | CASE           {  // CASE
	                     D(O("CASE");)
			     cur_indent -= case_indent;
	                  }
	 | GENERIC_END    {  // GENERIC END:  simple 'end' found
	                     D(O("GENERIC_END");)
			     if (!indent_handled)
				cur_indent = pop_indent();
			     cur_rprop = top_rprops();
			     simple_end_found = 1;
			     D(O(whatprop(cur_rprop));O(cur_rprop.name);)
			     pop_rprops();
			  }
	 | SPECIFIC_END   {  // SPECIFIC END
	                     D(O("SPECIFIC_END");)
			     if (!indent_handled)
				cur_indent = pop_indent();
			  }
	 | ROUTINE_END    {  // SPECIFIC END
	                     D(O("SPECIFIC_END");)
			     if (!indent_handled)
				cur_indent = pop_indent();
			     D(O(whatprop(cur_rprop));O(cur_rprop.name);)
			     pop_rprops();
			  }
	 | UNKNOWN_END    {
	                     D(O("UNKNOWN_END");)
			     if (!indent_handled)
				cur_indent = pop_indent();
	                  }


	 | ENDSELECT      {  // ENDSELECT
	                     D(O("ENDSELECT");)
	                     cur_indent = pop_indent();
			  }
         | CONTAINS       {  // CONTAINS
	                     D(O("CONTAINS");)
			     cur_indent -= contains_indent;
			  }
         | IFCONSTRUCT    {  // IFCONSTRUCT
	                     D(O("IFCONSTRUCT");)
			     cur_indent = top_indent();
			     push_indent(cur_indent + if_indent);
	                  }
         | ELSE           {  // ELSE
	                     D(O("ELSECONSTRUCT");)
			     cur_indent -= if_indent;
	                  }
         | ELSEIF         {  // ELSIF
	                     D(O("ELSEIF");)
			     cur_indent -= if_indent;
	                  }
         | ENTRY          {  // ENTRY
	                     D(O("ENTRY");)
			     cur_indent -= entry_indent;
	                  }
         | WHERECONSTRUCT {  // WHERE CONSTRUCT
	                     D(O("WHERECONSTRUCT");)
			     cur_indent = top_indent();
			     push_indent(cur_indent + where_indent);
	                  }
         | ASSOCIATECONSTRUCT {  // ASSOCIATE CONSTRUCT
	                     D(O("ASSOCIATECONSTRUCT");)
			     cur_indent = top_indent();
			     push_indent(cur_indent + associate_indent);
	                  }
         | TYPECONSTRUCT  {  // TYPE CONSTRUCT
	                     D(O("TYPECONSTRUCT");)
			     cur_indent = top_indent();
			     push_indent(cur_indent + type_indent);
	                  }
         | ELSEWHERE      {  // ELSEWHERE
	                     D(O("ELSEWHERECONSTRUCT");)
			     cur_indent -= where_indent;
	                  }
         | FORALLCONSTRUCT { // FORALL CONSTRUCT
	                     D(O("FORALLCONSTRUCT");)
			     cur_indent = top_indent();
			     push_indent(cur_indent + forall_indent);
	                  }

	 ;
%%

int main(int argc, char*argv[])
{
   all_indent          = default_indent;
   start_indent        = 0;                       // -I
   auto_firstindent    = 0;
   set_default_indents();
   num_lines           = 0;
   label_left          = label_left_default;
   non_blank_line_seen = 0;
   input_format        = 0;
   output_format       = 0;

   lexer_init();

   int c,rc;
   opterr = 0;
   while((c=getopt(argc,argv,"a:b:c:C:d:e:E:f:F:hi:I:j:l:L:m:o:qr:R:s:t:vw:x:"))!=-1)
      switch(c)
         {
	   case 'a' :
	      associate_indent  = atoi(optarg);
	      break;
	   case 'b' :
	      block_indent      = atoi(optarg);
	      break;
	   case 'c' :
	      case_indent       = atoi(optarg);
	      break;
	   case 'C' :
	      contains_indent   = atoi(optarg);
	      break;
	   case 'd' :
	      do_indent         = atoi(optarg);
	      break;
	   case 'e' :
	      entry_indent      = atoi(optarg);
	      break;
	   case 'E' :
	      enum_indent       = atoi(optarg);
	      break;
	   case 'f' :
	      if_indent         = atoi(optarg);
	      break;
	   case 'F' :   
	      forall_indent     = atoi(optarg);
	      break;
	   case 'h' :
	      usage();
	      return 0;
	      break;
	   case 'i' :
	      if      (string(optarg) == "fixed")
	         input_format = FIXED;
	      else if (string(optarg) == "free")
	         input_format = FREE;
	      else if (string(optarg) == "auto")
	         input_format = determine_fix_or_free(1);
	      else
	      {
		 all_indent        = atoi(optarg);
		 set_default_indents();
	      }
	      D(O("i flag:");O(optarg);O(" format:") 
	        if (input_format == FIXED) O("fixed")
		if (input_format == FREE)  O("free")
		)
	      break;
	   case 'I' :
	      if (optarg[0] == 'a')
	         auto_firstindent = 1;
	      else
		 start_indent   = atoi(optarg);
	      break;
	   case 'j' :
	      interface_indent  = atoi(optarg);
	      break;
	   case 'l' :
	      label_left        = (atoi(optarg) != 0);
	      break;
	   case 'L' :
	      input_line_length = atoi(optarg);
	      input_format_gnu  = (optarg[strlen(optarg)-1] == 'g');
	   case 'm' :
	      module_indent     = atoi(optarg);
	      break;
	   case 'o' :
	      if(string(optarg) == "free")
	         output_format = FREE;
	      break;
	   case 'q' :
	      handle_reading_from_tty();
	      rc = determine_fix_or_free(0);
	      switch(rc)
	      {
	         case FIXED : cout << "fixed" << endl;
		 break;
		 case FREE : cout << "free" << endl;
		 break;
	      }
	      return 0;
	      break;
	   case 'r' :
	      routine_indent    = atoi(optarg);
	      break;
	   case 'R':
	      switch(optarg[0])
	      {
	         case 'R' :
		    upcase_routine_type = 1;
		 case 'r' :
		    refactor_routines = 1;
		    break;
	      }
	      break;
	   case 's' :
	      select_indent     = atoi(optarg);
	      break;
	   case 't' :
	      type_indent       = atoi(optarg);
	      break;
	   case 'v' :
	      cout << "findent version "<<VERSION<<endl;
	      return 0;
	      break;
	   case 'w' :
	      where_indent      = atoi(optarg);
	      break;
	   case 'x' :
	      critical_indent   = atoi(optarg);
	      break;
	 }

   handle_reading_from_tty();

   if (input_format == 0)
      input_format = determine_fix_or_free(1);

   if(output_format == 0)
      output_format = input_format;

   labelleng        = 0;
   end_of_file      = 0;
   simple_end_found = 0;
   cur_rprop        = empty_rprop;
   get_full_statement();
   lexer_push(full_statement+'\n',FREE);
   cur_semi_eol  = 0;
   cur_indent    = start_indent;
   init_indent();
   yyparse();
   return 0;
}

void yyerror(const char *s)
{
}

void handle_reading_from_tty()
{
   reading_from_tty = isatty(fileno(stdin));
   if (reading_from_tty)
   {
      cerr << "! Warning: reading from terminal"                << endl;
      cerr << "! End this session by typing a single dot ('.')" << endl;
      cerr << "!     on a new line"                             << endl;
      cerr << "! "                                              << endl;
      cerr << "! Examples of typical usage:"                    << endl;
      cerr << "!   help:    findent -h"                         << endl;
      cerr << "!   indent:  findent < in.f > out.f"             << endl;
      cerr << "!   convert: findent -ofree < prog.f > prog.f90" << endl;
   }
}

void init_indent()
// fills the indent-stack until indent 0
{
   D(O("init_indent");O(indent.size());)
   while(!indent.empty())
      indent.pop();
   int l=0;
   for (int i=0; l<start_indent; i++)
   {
      indent.push(l);
      l = i*default_indent;
   }
   indent.push(start_indent);
}

string trim(const string& str)
{
    const string whitespace = " \t";
    const size_t strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return ""; // no content

    const size_t strEnd = str.find_last_not_of(whitespace);
    const size_t strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

string rtrim(const string& str)
{
    const string whitespace = " \t";

    const size_t strEnd = str.find_last_not_of(whitespace);
    if (strEnd == string::npos)
        return ""; // no content
    return str.substr(0,strEnd+1);
}

string ltab2sp(const string& s)
{  // converts leading white space and white space after a statement label
   //   to spaces and removes trailing white space
   // if line starts with 0-5 spaces or digits followed by a tab, followed
   //   by 1-9, this is counted as 5 spaces, it appears that many compilers
   //   assume that 
   //   <tab>1  <some code>
   //   is a continuation statement, if the continuation character is 1-9
   //   If the character is not within 1-9, it is assumed that 
   //   this character is the first of a statement, so in this case
   //   this is counted as 6 spaces

   int si         = 0;
   bool ready     = 0;
   const int tabl = 6;
   bool firsttab  = 1;
   string leader  = "";
   int removed    = 0;

   for (unsigned int j=0; j<s.length(); j++)
   {
      switch (s[j])
      {
	 case ' ' :
	    si ++;
	    removed++;
	    leader = leader + " ";
	    break;
	 case '\t' :
	    if (firsttab)
	    {
	       firsttab = 0;
	       if (si < 6)
	          // investigate next char: if 1-9, count this tab as 5 spaces
	          if (s.length() > j+1)
		     if (s[j+1] >= '1' && s[j+1] <= '9')
		     {
		        si = 5;
			removed++;
			leader = string(5,' ');
			break;
		     }
	    }
	    si = (si/tabl)*tabl + tabl;
	    leader = leader + string(si - leader.length(),' ');
	    break;
	    case '0': case '1': case '2': case '3': case '4':
	    case '5': case '6': case '7': case '8': case '9':
	    si++;
	    removed++;
	    leader += s[j];
	    firsttab = 0;
	    break;
	 default:
	    ready = 1;
	    break;
      }
      if(ready)
	 break;
   }
   return leader + trim(s.substr(removed));
}

string mygetline()
{
   // reads next line from cin.
   // side effects:
   //   end_of_file is set if endoffile condition is met
   //   endline is set to \n or \r\n
   //   lines_read is incremented

   string s;

   getline(cin,s);
   D(O("getline:");O(s);O("eofbit");O(cin.eofbit);O(cin.eof());)

   // sometimes, files do not end with (cr)lf, hence the test for s=="":
   end_of_file = (cin.eof() && s == "");

   lines_read ++;

   if (!end_of_file && reading_from_tty)
      end_of_file = (s == ".");

   return handle_dos(s);

}

void get_full_statement()
{
   string s;
   full_statement_has_been_output = 0;
   stlabel_found                  = 0;
   full_statement                 = "";
   indent_handled                 = 0;

   while(1)
   {
      if (!linestack.empty())
      {
         s = linestack.top();
	 linestack.pop();
      }
      else if (linebuffer.empty())
      {
         s = mygetline();
      }
      else
      {
         s = linebuffer.front();
	 linebuffer.pop();
	 if (reading_from_tty && s == ".")
	    end_of_file = 1;
      }

      num_lines++;

      D(O(s);)

      if (!non_blank_line_seen)
      {
         if (input_format == FREE)
	    non_blank_line_seen = (trim(s) != "");
	 else
	    {
	       string s1;
	       s1 = ltab2sp(s);
	       if (s1.length() > 6)
	          non_blank_line_seen = (s[0] != 'c' && s[0] != 'C' && s[0] != '!' && s[0] != '*' && s[0] != '#');
	    }
	 if (auto_firstindent && non_blank_line_seen)
	 {
	    start_indent = guess_indent(s);
	    cur_indent   = start_indent;
	    init_indent();
	 }
      }

      D(O("get_full_statement s leng:");O(s);O(s.length());O("endline:");O(endline.length());)

      if (input_format == FREE)
      {
	 if (handle_free(s))
	    continue;
	 else
	    break;
      }
      else
      {
	 if (handle_fixed(s))
	    continue;
	 else
	    break;
      }
   }
   D(O("full_statement:");O(num_lines);O(full_statement);)
}

bool handle_free(string s)
// adds input line s to full_statement
// return 1: more lines are to expected
//        0: this line is complete

{
   if(end_of_file)
   {
      D(O("end of file");)
      return 0;
   }

   if (input_line_length !=0)
      s = s.substr(0,input_line_length);

   string sl     = trim(s);

   if (sl != "" && sl[0] == '&')
   {
      sl.erase(0,1);
      sl = trim(sl);
   }

   //  if this line is pure comment or empty or preprocessor statement:
   //     add it to lines

   if (sl == "" || sl[0] == '!' || sl[0] == '#')
   {
      lines.push_back(trim(s));
      // if there is now only one line in lines,
      // we are not in a continuation:
      if(lines.size() ==1)
	 return 0;
      // we are in a continuation, read more
      return 1;
   }

   // Investigate if this line wants a continuation.
   // We append the line to full_statement, and look for
   // an unterminated string. 
   // If there is an unterminated
   // string, and the line ends with '&', a continuation
   // line is expected.
   // If there is no unterminated string, we strip of
   // a possible trailing comment, and trim.
   // If the last character = '&', a continuation is expected.

   bool expect_continuation = 0;
   string cs = full_statement + sl;

   remove_trailing_comment(cs);

   expect_continuation = ( cs[cs.length()-1] == '&');
   if (expect_continuation)            // chop off '&' :
      cs = cs.substr(0,cs.length()-1);

   full_statement = cs;
   lines.push_back(trim(s));
   D(O("full_statement");O(full_statement);O(expect_continuation);)

   return expect_continuation;
}

bool handle_fixed(string s)
{
   if(end_of_file)
      return 0;

   string s0 = s;

   D(O("fixed s");O(s);)

   if (input_line_length != 0)
   {
      // with tabbed input there is a difference between
      // gfortran and other compilers
      // other compilers simply count the number of characters.
      // gfortran always assumes that the
      // continuation character is in column 6
      // so this needs extra attention:
      if (input_format_gnu) // convert leading tabs to spaces
         s = ltab2sp(s);
      s = s.substr(0,input_line_length);
   }

   if (isfixedcmt(s))
   {  // this is a blank or comment or preprocessor line
      lines.push_back(trim(s));
      if (lines.size() ==1)
         return 0;   // do not expect continuation lines
      return 1;      // but here we do
   }

   // replace leading tabs by spaces
   s = ltab2sp(s);
   D(O("fixed:");O("s");O(s);)

   string sl;
   sl = s.substr(0,5);
   if (s.length() >6)
      sl = sl+' '+s.substr(6);

   D(O("sl:");O(sl);O(lines.size());)

   // this is a line with code
   if (lines.empty())
   {  // this is the first line
      lines.push_back(s);
      full_statement += trim(sl);
      remove_trailing_comment(full_statement);
      D(O("sl:");O(sl);O(full_statement);O(lines.size());)
      return 1;      // maybe there are continuation lines
   }

   // this is possibly a continuation line
   if (s.length() < 6 || s[5] == ' ' || s[5] == '0')
   {  // this is not a continuation line
      // push it back, we will see it later
      // we push back the line in it's original state
      // to prevent double line truncation
      linestack.push(s0);
      return 0;          // do not look for further continuation lines
   }
   // this is a continuation line
   lines.push_back(s);
   full_statement += rtrim((rtrim(sl)+"      ").substr(6));
   remove_trailing_comment(full_statement);
   D(O(full_statement);O(rtrim(sl));O(sl););
   return 1;   // look for more continuation lines
}

int remove_trailing_comment(string &s)
{
   // the lexer will tell if 
   // there is an terminated string followed by !comment.  rc == CMT
   //   the position of '!' is in lexer_position 
   // or the line ends in a unterminated string          rc == EOL

   lexer_push(s + '\n', SCANSTRCMT);
   int rc = yylex();
   int p = lexer_position;  // have to save lexer_position because of lexer_pop
   D(O("p:");O(p);)
   lexer_pop();

   if (rc == CMT)
      s = rtrim(s.substr(0, max(p-1,0)));
   return rc;
}

int guess_indent(const string s)
{ // count spaces at start of line, correct for tabs and & and label
   int si         = 0;
   bool ready     = 0;
   const int tabl = 8;

   D(O("guess_indent entered");)

   if (input_format == FIXED)
   {
      string s1 = ltab2sp(s);
      si        = s1.find_first_not_of(' ') -6;
      if (si <0)
         si = 0;
      return si;
   }

   for (unsigned int j=0; j<s.length(); j++)
   {
      switch (s[j])
      {
	 case ' ' : case '0' : case '1' : case '2' : case '3' : case '4' : case '5' : case '6' : case '7' : case '8' : case '9' :
	    si ++;
	    break;
	 case '&' :
	    si++;
	    ready = 1;
	    break;
	 case '\t' :
	    si = (si/tabl)*tabl + tabl;
	    break;
	 default:
	    ready = 1;
	    break;
      }
      if(ready)
	 break;
   }
   return si;
}

string stoupper(const string s)
{
   string sl = s;
   int l     = sl.size();
   for (int i=0; i<l; i++)
      sl[i] = toupper(sl[i]);
   return sl;
}

void output_line()
{
   D(O("output, nr of lines:");O(lines.size());O("cur_indent");O(cur_indent);O("already done:");O(full_statement_has_been_output);)
   if (lines.empty())
      return;
   if (full_statement_has_been_output)
      return;
   full_statement_has_been_output = 1;
   int lineno                     = 0;
   string needamp                 = "";
   char prevquote                 = ' ';
   char preprevquote              = ' ';
   string outputline;

   D(O("refactor");O(refactor_routines);O(simple_end_found);O(lines.size());O(cur_rprop.kind);)
   if (refactor_routines && simple_end_found)
   {
      if (cur_rprop.kind != 0)
      {
	// modify first line to match the corrsponding module, subroutine ... line  
	// find the location of 'end'
	string s = stoupper(lines[0]);
	size_t p = s.find("END");
	D(O("p");O(p);)
	if ( p != string::npos)
	{
	   string routinetype = whatprop(cur_rprop);
	   if (upcase_routine_type)
	      routinetype = stoupper(routinetype);
	   lines[0] = lines[0].substr(0,p+3)+
	   " "+routinetype+" "+cur_rprop.name + lines[0].substr(p+3);
	   D(O(s);O(lines[0]););
	}
      }
   }

   if (input_format == FREE)
   {
      string firstline = lines.front();
      handle_pre(firstline);
      lines.pop_front();
      D(O("firstline");O(firstline);)
      int l;
      if (firstline != "" || lines.size() > 1)
      {
	 if (label_left && labelleng > 0)
	 {  // put label at start of line
	    string label = firstline.substr(0,labelleng);
	    firstline    = trim(firstline.substr(labelleng));
	    cout << label;
	    l = cur_indent - labelleng;
	    if ( l <= 0 )
	       l=1;
	 }
	 else
	    l = cur_indent;

	 if (l<0)
	   l=0;
	 if (firstline[0] != '#')
	 {
	    cout << string(l,' '); 
	    D(O("output indent before firstline");O(string(l,' '));)
	 }
      }
      cout << firstline << endline;
      D(O("output firstline");O(firstline);)
      while (!lines.empty())
      {
      // sometimes, there are preprocessor statements within a continuation ...
         handle_pre(lines.front());
	 if (lines.front()[0] != '#')
	    cout << string(max(cur_indent,0),' ');
	 cout << lines.front()<<endline;
	 lines.pop_front();
      }
   }
   else   // input_format = FIXED, output can be FREE or FIXED
   {
      unsigned int old_indent = 0;
      unsigned int first_indent = 0;
      while(!lines.empty())
      {
         lineno++;
         string s = lines.front();
	 handle_pre(s);
	 lines.pop_front();
	 if(isfixedcmt(s))
	 {  // this is an empty line or comment line or a preprocessing line
	    if (output_format == FIXED)
	       cout << trim(s) << endline;
	    else  // output_format = FREE
	    {
	       if (trim(s) == "")
	          cout << endline;
	       else
	       {
	          switch (s[0])
		  {
	             // special hack for lines starting with 'd' or 'D'
	             case 'd' :
		     case 'D' :
		        cout << "!" + trim(s) << endline;
			break;
	             case '#' :
			cout << trim(s) << endline;
			break;
	             default:
			cout << string(max(cur_indent,0),' ') << "!" << trim(s.substr(1)) << endline;
		  }
	       }
	    }
	 }
	 else
	 {
	    if (output_format == FIXED)
	    {
	       cout << s.substr(0,6);
	       
	       if(s.length() > 6)
	       {
	          // try to honor current indentation
		  // if this is a continuation line, count the number
		  // of spaces after column 6.
		  if (s[5] != ' ' && s[5] != '0')
		  {
		     string s6 = ltab2sp(s.substr(6))+'x';
		     old_indent = s6.find_first_not_of(' ');
		  }
		  else
		  {  // count the number of spaces after column 6 of the first line
		     string s6 = ltab2sp(s.substr(6))+'x';
		     first_indent = s6.find_first_not_of(' ');
		  }
		  int adjust_indent = old_indent - first_indent;
		  if (adjust_indent < 0)
		     adjust_indent = 0;

		  switch(prevquote)
		  {
		     case ' ' :   // no dangling strings, output with indent
			cout << string(max(adjust_indent+cur_indent,0),' ') << trim(s.substr(6));
			break;
		     default:  // dangling string, output asis
			cout << s.substr(6);
			break;
		  }
		  // investigate if this line terminates a string

                  prevquote = fixedmissingquote(prevquote + s);
	       }
		        
	       cout << endline;
	    }
	    else  // output_format == FREE
	    {
	       outputline = needamp;
	       if (lineno == 1)
	       {
		  D(O("s");O(s);O(labelleng);)
		  int l;
		  if (s.length()>6)
		  {
		     string s6 = ltab2sp(s.substr(6))+'x';
		     first_indent = s6.find_first_not_of(' ');
		  }
		  if (s != "" || lines.size() > 1)
		  {
		     if (label_left && labelleng > 0)
		     {  // put label at start of line
		        s = trim(s);
			string label = s.substr(0,labelleng);
			s    = trim(s.substr(labelleng));
			cout << label;
			l = cur_indent - labelleng;
			if ( l <= 0 )
			   l=1;
		     }
		     else
			l = cur_indent;

		     cout <<string(max(l,0),' '); 
		  }
		  outputline += trim(s);
		  // we need the value of prevquote later on:
		  preprevquote = prevquote;
		  prevquote    = fixedmissingquote(prevquote + s);
	       }
	       else
	       {
	          if (s.length() >6)
		  {
		     cout << string(max(cur_indent,0),' ');
		     // try to honor current indentation
		     // if this is a continuation line, count the number
		     // of spaces after column 6.
		     if (s[5] != ' ' && s[5] != '0')
		     {
			string s6 = ltab2sp(s.substr(6))+'x';
			old_indent = s6.find_first_not_of(' ');
			D(O(s6);O(old_indent);)
		     }
		     D(O(old_indent);O(first_indent);)
		     int adjust_indent = old_indent - first_indent;
		     if (adjust_indent < 0 || prevquote!=' ')
			adjust_indent = 0;

		     string s1 = s.substr(6);
		     if (prevquote == ' ')
			s1 = trim(s1);
		     if (s1 != "")
			outputline += string(adjust_indent,' ');
		     outputline += s1;
		     // we need the value of prevquote later on:
		     preprevquote = prevquote;
		     prevquote = fixedmissingquote(prevquote + s1);
		  }
	       }
	       // check for continuation lines
	       // there is a continuation line if there is a non-comment in 
	       // the lines deque, in that case a trailing & is needed
	       // and the non-comment line needs a leading &

	       needamp="";
	       deque<string>::iterator it= lines.begin();
	       while(it != lines.end())
	       {
		  if (!isfixedcmt(*it++))
		  {
		     needamp =  '&';
		     // we have to put an '&' at the end of the line,
		     // but what if the line ends in a ! comment, as in
		     //   x = x *  ! comment
		     // Then we have to put the '&' like this:
		     //   x = x * & ! comment
		     // but in this case:
		     //  x = ' a string ! no comment
		     // we have to place the '&' like this:
		     //  x = ' a string ! no comment&

                     // if there is an unterminated string, then:
		     if (prevquote != ' ')
		     {
		        outputline = outputline + '&';
			break;
		     }

                     // the line does not contain an unterminated string,
		     // is there a !commant outside a string?
		     // we ask the lexer to have a look
		     // here we need the value of preprevquote:

		     lexer_push(preprevquote+outputline+'\n',SCANSTRCMT);
		     int rc = yylex();
		     int p = lexer_position;
		     lexer_pop();
		     if (rc == CMT)
		     {
			// there is a comment outside strings,
			// the number of characters before the comment
			// has to be decreased by one, because
			// of the prepending of preprevquote
			p = max(p-2,0);
			outputline = outputline.substr(0, p) + '&' + outputline.substr(p);
			break;
		     }
		     else
		     {
		        // no !comment, simply put '&' at the end
			outputline += '&';
			break;
		     }
		  }
	       }
	       cout << outputline << endline;
	    }
	 }
      }
   }
}

int pop_indent()
{
   if (indent.empty())
      return 0;
   indent.pop();
   return top_indent();
}

int top_indent()
{
   if (indent.empty())
      return 0;
   return indent.top();
}

void push_indent(int p)
{
   indent.push(p);
}

void push_rprops(struct rstruct p)
{
   rprops.push(p);
}

void init_rprops()
// empties the rprops-stack
{
   D(O("rprops");O(rprops.size());)
   while(!rprops.empty())
      rprops.pop();
}

struct rstruct pop_rprops()
{
   if (rprops.empty())
      return empty_rprop;
   rprops.pop();
   return top_rprops();
}

struct rstruct top_rprops()
{
   if (rprops.empty())
      return empty_rprop;
   return rprops.top();
}

string whatprop(struct rstruct p)
{
    switch(p.kind)
    { 
       case(KIND_SUBROUTINE): return("subroutine");
       case(KIND_PROGRAM):    return("program");
       case(KIND_BLOCKDATA):  return("blockdata");
       case(KIND_FUNCTION):   return("function");
       case(KIND_MODULE):     return("module");
       default:               return("UNKNOWN");
    }
 }

int pop_dolabel()
{
   if (dolabels.empty())
      return -1;
   dolabels.pop();
   return top_dolabel();
}

int top_dolabel()
{
   if (dolabels.empty())
      return -1;
   return dolabels.top();
}

void push_dolabel(int p)
{
   dolabels.push(p);
}

void empty_dolabels()
{
   while(!dolabels.empty())
      dolabels.pop();
}

void shorten_full_statement()
{  // strip off scanned part of full_statement
   // and use as new lexer buffer
  D(O("shorten full_statement before:");O(lexer_position);O(full_statement);)
  full_statement.erase(0,lexer_position);
  full_statement = trim(full_statement);
  lexer_set(full_statement+'\n',FREE);
  D(O("shorten full_statement after:");O(lexer_position);O(full_statement);)
}

void set_default_indents()
{
   associate_indent = all_indent;              // -a
   block_indent     = all_indent;              // -b
   do_indent        = all_indent;              // -d
   if_indent        = all_indent;              // -f
   forall_indent    = all_indent;              // -F
   interface_indent = all_indent;              // -j
   module_indent    = all_indent;              // -m
   routine_indent   = all_indent;              // -r
   select_indent    = all_indent;              // -s
   type_indent      = all_indent;              // -w
   where_indent     = all_indent;              // -w
   critical_indent  = all_indent;              // -x
   enum_indent      = all_indent;              // -E
   case_indent      = all_indent-all_indent/2; // -c
   contains_indent  = all_indent;              // -C
   entry_indent     = all_indent-all_indent/2; // -e
}

void usage()
{
   cout << "findent [options]"                       << endl;
   cout << "   format fortran program"               << endl;
   cout << "   reads from STDIN, writes to STDOUT"   << endl;
   cout << "options: (errors are silently ignored)"  << endl;
   cout << "  general:"                              << endl;
   cout << "-h       : print this text"              << endl;
   cout << "-v       : prints findent version"       << endl;
   cout << "-q       : guess free or fixed, prints fixed or free" << endl;
   cout << "-l 0/1   : 1: statement labels to start of line (default:1)" << endl;
   cout << "-i auto  : determine automatically input format (free or fixed)" << endl;
   cout << "-i fixed : force input format fixed"     << endl;
   cout << "-i free  : force input format free"      << endl;
   cout << "                                     (default: auto)"     << endl;
   cout << "-L nnn   : use only first nnn characters of each line"    << endl;
   cout << "           default=0: take whole lines"                   << endl;
   cout << "-L nnng  : same as above, but use gfortran convention"    << endl;
   cout << "           for counting the characters with tabbed lines" << endl;
   cout << "-o free  : force free format output"         << endl;
   cout << "-Rr      : refactor routines: a single"      << endl;
   cout << "           'end' is if possible replaced by" << endl;
   cout << "           'end subroutine name'"            << endl;
   cout << "           'end function name'"              << endl;
   cout << "           'end program name'"               << endl;
   cout << "           'end blockdata name'"             << endl;
   cout << "           'end module name'"                << endl;
   cout << "-RR      : same as -Rr, but 'SUBROUTINE'"    << endl;
   cout << "           in stead of 'subroutine' etc"     << endl;
   cout << "  indents:"                              << endl;
   cout << "-I n     : starting  indent (default:0)" << endl;
   cout << "-I a     : determine starting indent from first line" << endl;
   cout << "-i n     : all       indents except I,c,C,e (default:" << default_indent << ")" <<endl;
   cout << "-a n     : associate indent"             << endl;
   cout << "-b n     : block     indent"             << endl;
   cout << "-d n     : do        indent"             << endl;
   cout << "-f n     : if        indent"             << endl;
   cout << "-E n     : enum      indent"             << endl;
   cout << "-F n     : forall    indent"             << endl;
   cout << "-j n     : interface indent"             << endl;
   cout << "-m n     : module    indent"             << endl;
   cout << "-r n     : routine   indent"             << endl;
   cout << "-s n     : select    indent"             << endl;
   cout << "-t n     : type      indent"             << endl;
   cout << "-w n     : where     indent"             << endl;
   cout << "-x n     : critical  indent"             << endl;
   cout << "next defaults are: all - all/2"          << endl;
   cout << "-c n     : case      negative indent"    << endl;
   cout << "-C n     : contains  negative indent"    << endl;
   cout << "-e n     : entry     negative indent"    << endl;
   cout << ""                                        << endl;
   cout << "Examples"                                         << endl;
   cout << "  indent:  findent < in.f > out.f"                << endl;
   cout << "           findent -i2 -r0 < in.f > out.f"        << endl;
   cout << "  convert: findent -ofree < prog.f > prog.f90"    << endl;
   cout << "  refactor 'end': findent -Rr < in.f90 > out.f90" << endl;
}

int guess_fixedfree(const string s)
{
   // sometimes, program sources contain carriage control characters
   // such as ^L
   // I cannot get the lexer to respond to [:cntrl:]
   // so I handle that here:
   if (s != "" && s[0] != '\t')
      if(s[0] < 32)
         return UNSURE;

   lexer_push(ltab2sp(s)+'\n',FINDFORMAT);
   int rc = yylex();
   lexer_pop();
   return rc;
}

int determine_fix_or_free(const bool store)
{
   int rc;
   string s;
   int n = 0;
   const int nmax = 4000;
   while ( n < nmax)
   {
      n++;
      s = mygetline();
      if (end_of_file)
      {
         // to avoid to have to type twice a dot to
	 // end input from terminal:

         if(store && reading_from_tty)
	    linebuffer.push(s);       // s == "."
         break;
      }

      if (store)
	 linebuffer.push(s);

      rc = guess_fixedfree(s);
      switch(rc)
      {
         case UNSURE : 
	    D(O("UNSURE");) 
	    break;
	 case PROBFREE : 
	    D(O("PROBFREE");) 
	    break;
	 case FREE : 
	    D(O("FREE");) 
	    return FREE;
	 case FIXED : 
	    D(O("FIXED");) 
	    return FIXED;
      }
      D(O(s);)
   }
   return FIXED;
}

string handle_dos(const string s)
//  determine if the input is dos format:
// side effect: sets endline if not already been set
{
   string sl;
   sl = s;
   if (!endline_set)
   {
      D(O("setting endline");O(sl))
      if (sl != "" && sl[sl.length()-1] == '\r')
      {
	 endline = "\r\n";
         D(O(endline.length()););
      }
      endline_set = 1;
   }
   if (sl != "" && sl[sl.length()-1] =='\r')
      sl.erase(sl.length()-1);
   return sl;
}
 
bool isfixedcmt(const string s)
{
// returns 1 if this is a fixed empty line or fixed comment line or preprocessor line
//                                         or debug line ('d' or 'D' in column 1)
   if (s == "" || trim(s) == "")
      return 1;
   char c = s[0];
   return (c == 'C' || c == 'c' || c == '!' || c == '*' || c == '#' || c == 'd' || c == 'D'); 
}

char fixedmissingquote(const string s)
{
   // investigate if this line terminates a string
   // returns ' ' if there is no unterminated string
   // returns '"' if this is an unterminated string, a '"' is missing
   // returns '\'' if this is an unterminated string, a '\'' is missing
   D(O(lexer_position);)
   lexer_push(s + '\n',UNTERMSTR);
   int rc = yylex();
   lexer_pop();
   D(O(lexer_position);)
   D(O("rc:");O(rc);O(EOL);O(DQUOTE);O(SQUOTE);)
   char result = ' ';
   switch (rc)
   {
      case  EOL :
	 result = ' ';
	 break;
      case  DQUOTE :         // unterminated string
	 result = '"';
	 break;
      case  SQUOTE :
	 result = '\'';
	 break;
   }
   return result;
}

// #if, #ifdef, #ifndef, #else, #elif and #endif

// after an #if{,def,ndef} the indent stack is pushed
// on indent_stack, and the current indent stack is used.
// after an #elif the indent stack is made equal to indent_stack.top()
// after an #else, the indent stack is popped from indent_stack.
// after an #endif:
//     if the index stack was not already popped from index_stack (after
//        #else), it is popped
// the stack pre_stack is used to note if the index stack was already
//      popped by #else
//
// So, after #endif, the indentation is taken from the code after #else
//     or, if there is no #else, from the code before the #if{,def,ndef}

// something like this has been done for the rprops stack

void handle_pre(const string s)
{
   D(O("pre before");O(cur_indent);O(top_indent());O(s);)

   if (s == "" || s[0] != '#')
      return;

   if (s.find("#if") == 0)   // covers #if #ifdef #ifndef
   {
      indent_stack.push(indent);
      pre_stack.push(0);
      rprops_stack.push(rprops);
      prep_stack.push(0);
   }
   else if (s.find("#elif") == 0)
   {
      if (!indent_stack.empty())
	 indent = indent_stack.top();
      if (!rprops_stack.empty())
	 rprops = rprops_stack.top();
   }
   else if (s.find("#else") == 0)
   {
      if (!indent_stack.empty())
      {
	 indent = indent_stack.top();
	 indent_stack.pop();
	 pre_stack.pop();
	 pre_stack.push(1);
      }
      if (!rprops_stack.empty())
      {
	 rprops = rprops_stack.top();
	 rprops_stack.pop();
	 prep_stack.pop();
	 prep_stack.push(1);
      }
   }
   else if (s.find("#endif") == 0)
   {
      if (!indent_stack.empty())
      {
	 if (!pre_stack.top())
	 {
	    indent = indent_stack.top();
	    indent_stack.pop();
	 }
	 pre_stack.pop();
      }
      if (!rprops_stack.empty())
      {
	 if (!prep_stack.top())
	 {
	    rprops = rprops_stack.top();
	    rprops_stack.pop();
	 }
	 prep_stack.pop();
      }
   }
   D(O("pre after");O(cur_indent);O(top_indent());)
}

extern "C" int yywrap()
{
  D(O("yywrap");)
  if (end_of_file)
     return 1;
  get_full_statement();
  simple_end_found = 0;
  cur_rprop      = empty_rprop;
  lexer_set(full_statement+'\n',FREE);
  return 0;
}
