" to enable the findent Fortran indent program: 
" include this file in ~/.vimrc 
" or place it in ~/.vim/plugin/
"Author: Willem Vermin wvermin@gmail.com
"Licence: fair
"Date: nov 2016
" The location of findent:
let g:findent = "/usr/bin/findent"

filetype plugin indent on

" for example:
" ,= will indent whole file
" ,f let you change finden flags
" see the nnoremap commands below
"
let mapleader=","

" indent whole file, to be used with all filetypes
function! Indent()
   let view=winsaveview()
   execute "normal! gg=G"
   call winrestview(view)
endfunction

" indent whole buffer:
nnoremap <leader>= :call Indent()<Return>

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
   autocmd Filetype fortran nnoremap <buffer> <leader>c I!<esc><Down>

   " set default shiftwidth
   autocmd Filetype fortran setlocal shiftwidth=3

   " Change findent flags
   " Findent_set_flags defined in after/indent/fortran.vim
   autocmd Filetype fortran nnoremap <buffer> <leader>f :call Findent_set_flags()<Return>

   " toggle b:findent_use_whole_buffer:
   " 1: use whole buffer up to cursor to determine indent at cursor
   " 0: use just enough lines from buffer
   " Findent_use_wb_toggle defined in after/indent/fortran.vim
   autocmd Filetype fortran nnoremap <buffer> <leader>w :call Findent_use_wb_toggle()<Return>

   " on input: do not create tabs on input 
   autocmd Filetype fortran setlocal expandtab

   " adapted status line
   " b:fortran_format and b:findent_use_whole_buffer are determined in
   " after/indent/fortran.vim
   autocmd Filetype fortran setlocal statusline=%<%t\ %m\ %r\ %y\ %{b:fortran_format}\ %{b:findent_use_whole_buffer}%=%l\ %c\ %LL\ %P

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
