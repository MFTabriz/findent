class Fixed
{
   public:
      std::string statement()
      {
	 return full_statement;
      }
      void statement(std::string & s)
      {
	 full_statement = s;
      }
      lines_t lines()
      {
	 return curlines;
      }
      void handle_fixed(fortranline &line, bool &f_more, bool &pushback);
      static void tofixed(lines_t &lines, int cur_indent, lines_t *freelines = 0); // fixed2fixed
      static void init(Flags &f)
      {
	 flags = f;
      }

   private:
      bool wizard(lines_t lines);
      std::string add_amp(const std::string s,const char prevquote);
      Flags flags;
      lines_t          curlines;        // current line, one continuation line per item
      std::string full_statement;
      lines_t curlines;
};
