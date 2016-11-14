" to enable the findent Fortran indent program: 
" include this file in ~/.vimrc 
" or place it in ~/.vim/plugin/
"Author: Willem Vermin wvermin@gmail.com
"Licence: fair
"Date: nov 2016

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

   " no max line length
   autocmd Filetype fortran setlocal textwidth=0

   " enable statusline
   autocmd Filetype fortran setlocal laststatus=2

   " use indent of previous line
   "autocmd Filetype fortran setlocal autoindent

   " make syntax aware of above
   autocmd Filetype fortran syntax on

augroup END


" vim filetype=vim
