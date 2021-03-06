  std::cout << "\" to enable the findent Fortran indent program: " << std::endl;
  std::cout << "\" include this file in ~/.vimrc " << std::endl;
  std::cout << "\" or place it in ~/.vim/plugin/ as findent.vim" << std::endl;
  std::cout << "\"Author: Willem Vermin wvermin@gmail.com" << std::endl;
  std::cout << "\"Licence: fair" << std::endl;
  std::cout << "\"Date: nov 2016" << std::endl;
  std::cout << "\"" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "if exists(\"g:use_findent\")" << std::endl;
  std::cout << "   if !g:use_findent" << std::endl;
  std::cout << "      finish" << std::endl;
  std::cout << "   endif" << std::endl;
  std::cout << "endif" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "filetype plugin indent on" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "\" set default indent flag, if not already set" << std::endl;
  std::cout << "if !exists(\"b:findent_flags\")" << std::endl;
  std::cout << "   let b:findent_flags = \"-i\".&shiftwidth" << std::endl;
  std::cout << "endif" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "\" \" the nnoremap commands will define some shortcuts:" << std::endl;
  std::cout << "\" for example:" << std::endl;
  std::cout << "\" \\= will indent whole file" << std::endl;
  std::cout << "\" \\f let you change finden flags" << std::endl;
  std::cout << "\" see the nnoremap commands below" << std::endl;
  std::cout << "\"" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "\" indent whole buffer, can be used with all filetypes" << std::endl;
  std::cout << "function! Indent()" << std::endl;
  std::cout << "   let view=winsaveview()" << std::endl;
  std::cout << "   execute \"normal! gg=G\"" << std::endl;
  std::cout << "   call winrestview(view)" << std::endl;
  std::cout << "endfunction" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "\" indent whole buffer:" << std::endl;
  std::cout << "nnoremap <buffer> <LocalLeader>= :call Indent()<Return>" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "function! Get_fortran_format()" << std::endl;
  std::cout << "   \" b:fortran_format defined in auto/indent/fortran.vim" << std::endl;
  std::cout << "   if exists(\"b:fortran_format\")" << std::endl;
  std::cout << "      return b:fortran_format" << std::endl;
  std::cout << "   endif" << std::endl;
  std::cout << "   return \"unknown\"" << std::endl;
  std::cout << "endfunction" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "function! Get_findent_use_whole_buffer()" << std::endl;
  std::cout << "   \" b:findent_use_whole_buffer defined in auto/indent/fortran.vim" << std::endl;
  std::cout << "   if exists(\"b:findent_use_whole_buffer\")" << std::endl;
  std::cout << "      if b:findent_use_whole_buffer" << std::endl;
  std::cout << "	 if b:use_findent_indentexpr" << std::endl;
  std::cout << "	    return \"wb\"" << std::endl;
  std::cout << "	 endif" << std::endl;
  std::cout << "      endif" << std::endl;
  std::cout << "   endif" << std::endl;
  std::cout << "   return \"\"" << std::endl;
  std::cout << "endfunction" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "augroup fortfiletype" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   autocmd!" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" allow tabs in fortran source" << std::endl;
  std::cout << "   autocmd Filetype fortran let fortran_have_tabs=1" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" fortran_more_precise=1: very slow :syntax on if on end of large file" << std::endl;
  std::cout << "   \"autocmd Filetype fortran let fortran_more_precise=1" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" indent after subroutne etc (not used by findent)" << std::endl;
  std::cout << "   autocmd Filetype fortran let fortran_indent_more=1" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" indent after do (not used by findent)" << std::endl;
  std::cout << "   autocmd Filetype fortran let fortran_do_enddo=1" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" comment line:" << std::endl;
  std::cout << "   autocmd Filetype fortran nnoremap <buffer> <LocalLeader>c I!<esc><Down>" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" Change findent flags" << std::endl;
  std::cout << "   \" Findent_set_flags defined in after/indent/fortran.vim" << std::endl;
  std::cout << "   autocmd Filetype fortran nnoremap <buffer> <LocalLeader>f :call Findent_set_flags()<Return>" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" on input: do not create tabs on input " << std::endl;
  std::cout << "   autocmd Filetype fortran setlocal expandtab" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" no max line length" << std::endl;
  std::cout << "   autocmd Filetype fortran setlocal textwidth=0" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" enable statusline" << std::endl;
  std::cout << "   autocmd Filetype fortran setlocal laststatus=2" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" use indent of previous line" << std::endl;
  std::cout << "   autocmd Filetype fortran setlocal autoindent" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" define statusline" << std::endl;
  std::cout << "   autocmd Filetype fortran setlocal statusline=%<%t\\ %m\\ %r\\ %y\\ %{Get_fortran_format()}\\ %{Get_findent_use_whole_buffer()}%=%l\\ %c\\ %LL\\ %P" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" define toggle: use whole buffer for indenting or not" << std::endl;
  std::cout << "   autocmd Filetype fortran nnoremap <buffer> <LocalLeader>w :call Findent_use_wb_toggle()<Return>" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" define == such that findent is called as if the line has been edited" << std::endl;
  std::cout << "   autocmd Filetype fortran nnoremap <buffer> == i<Esc>l" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   \" make syntax aware of above" << std::endl;
  std::cout << "   \" probably not needed." << std::endl;
  std::cout << "   \" uncommented, because autocmd commands in .vimrc are not executed" << std::endl;
  std::cout << "   \" when a modeline for is presen, as in:" << std::endl;
  std::cout << "   \" !directions for vi vim: filetype=fortran" << std::endl;
  std::cout << "   \" autocmd Filetype fortran syntax on" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "augroup END" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "\" vim filetype=vim" << std::endl;
