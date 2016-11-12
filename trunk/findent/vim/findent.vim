" to enable the findent Fortran indent program: 
" include this file in ~/.vimrc 
" or place it in ~/.vim/plugin/
"Author: Willem Vermin wvermin@gmail.com
"Licence: fair
"Date: nov 2016

" use findent for indenting,  unless use_findent == 0
if !exists("g:use_findent")
   let b:use_findent = 1
else
   let b:use_findent = g:use_findent
endif

" use findent for indenting using indentexpr (see :help indentexpr)
"     unless use_findent_indentexpr == 0
if !exists("g:use_findent_indentexpr")
   let b:use_findent_indentexpr = 1
else
   let b:use_findent_indentexpr = g:use_findent_indentexpr
endif

" The location of findent:
if !exists("g:findent")
   let g:findent = "/usr/bin/findent"
endif

filetype plugin indent on

" set default indent flag, if not already set
if !exists("b:findent_flags")
   let b:findent_flags = "-i".&shiftwidth
endif

" " the nnoremap commands will define some shortcuts:
" for example:
" \= will indent whole file
" \f let you change finden flags
" see the nnoremap commands below
"

" indent whole buffer, can be used with all filetypes
function! Indent()
   let view=winsaveview()
   execute "normal! gg=G"
   call winrestview(view)
endfunction

" indent whole buffer:
nnoremap <buffer> <LocalLeader>= :call Indent()<Return>

augroup fortfiletype

   autocmd!

   " allow tabs in fortran source
   autocmd Filetype fortran let fortran_have_tabs=1

   " fortran_more_precise=1: very slow :syntax on if on end of large file
   "autocmd Filetype fortran let fortran_more_precise=1

   " indent after subroutne etc (not used by findent)
   autocmd Filetype fortran let fortran_indent_more=1

   " indent after do (not used by findent)
   autocmd Filetype fortran let fortran_do_enddo=1

   " comment line:
   autocmd Filetype fortran nnoremap <buffer> <LocalLeader>c I!<esc><Down>

   " Change findent flags
   " Findent_set_flags defined in after/indent/fortran.vim
   autocmd Filetype fortran nnoremap <buffer> <LocalLeader>f :call Findent_set_flags()<Return>

   " on input: do not create tabs on input 
   autocmd Filetype fortran setlocal expandtab

   if exists("b:use_findent")
      if b:use_findent
	 " adapted status line
	 " b:fortran_format and b:findent_use_whole_buffer are determined in
	 " after/indent/fortran.vim
	 autocmd Filetype fortran setlocal statusline=%<%t\ %m\ %r\ %y\ %{b:fortran_format}\ %{b:findent_use_whole_buffer}%=%l\ %c\ %LL\ %P
	 " toggle b:findent_use_whole_buffer:
	 " 1: use whole buffer up to cursor to determine indent at cursor
	 " 0: use just enough lines from buffer
	 " Findent_use_wb_toggle defined in after/indent/fortran.vim
	 autocmd Filetype fortran nnoremap <buffer> <LocalLeader>w :call Findent_use_wb_toggle()<Return>
      endif
   endif

   " no max line length
   autocmd Filetype fortran setlocal textwidth=0

   " enable statusline
   autocmd Filetype fortran setlocal laststatus=2

   " use indent of previous line
   autocmd Filetype fortran setlocal autoindent

   " make syntax aware of above
   autocmd Filetype fortran syntax on

augroup END


" vim filetype=vim
