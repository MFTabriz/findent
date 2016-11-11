" Vim indent file
" Installation: Place this script in the $HOME/.vim/after/indent/ directory
"               as fortran.vim   and use it with Vim > 7.1 and findent:
"               findent.sourceforge.net
"Author: Willem Vermin wvermin@gmail.com
"Licence: fair
"Date: nov 2016

autocmd BufEnter * unlet! g:fortran_free_source g:fortran_fixed_source
autocmd BufEnter * unlet! b:fortran_free_source b:fortran_fixed_source

" g:findent is probably set in .vimrc
" if not: skip all
if !exists("g:findent")
   finish
endif

" get fortran format from extension ext
" return "free", "fixed" or "unknown"
function! Get_format_from_extension(ext)
   if a:ext =~? '^f$\|for\|fpp\|ftn'
      let format = "fixed"
   elseif a:ext =~? 'f90\|f95\|f03\|f08'
      let format = "free"
   else
      let format = "unknown"
   endif
   return format
endfunction

" return string that represents external command to determine
" if input is free or fixed format.
" If no suitable command is found, return ""
" The output of this external command will be "free" or "fixed"
function! Findent_get_freefixed()
   let indentparmsq = ' -q'
   let findent_freefixed = g:findent.indentparmsq.' 2>/dev/null'
   if strpart(system(findent_freefixed," continue"),0,4) != "free"
      let findent_freefixed = ""
   endif
   return findent_freefixed
endfunction

" Return external command to get the indent of the last line of the input
" Return "" if no such command can be found
" side effect: s:findent_getindent is the command tried
function! Findent_get_getindent()
   let getindent=g:findent.' -Ia -lastindent -i'.b:fortran_format.' '.b:findent_flags.' 2>/dev/null'
   let s:findent_getindent = getindent
   if system(getindent,'    continue') == 4
      return getindent
   else
      return ""
   endif
endfunction

" Return external command that indents the input
" Return "" if no such command can be found
" side effect: s:fortran_indentprog is the command tried
function! Findent_get_indentprog()
   " first a test:
   let indentparms = ' -Ia -i'.b:fortran_format.' '.b:findent_flags
   let indentprog = g:findent.indentparms.' 2>/dev/null'
   let s:fortran_indentprog = indentprog
   if strpart(system(indentprog,"continue"),0,8) == "continue"
      return indentprog
   else
      return ""
   endif
endfunction

" Returns the indentation of the current line
function! Findent_getindent()

   if b:findent_use_whole_buffer
      let startline = 1
   else
      let startline = system(g:findent." -lastusable -i".b:fortran_format,join(getline(1,v:lnum-1),"\n"))
   endif

   let startline = max([1,startline])

   let b:findent_getindent = Findent_get_getindent()
   let ind = system(b:findent_getindent, join(getline(startline,v:lnum),"\n"))
   return ind
endfunction

function! Findent_set_flags()
   if !b:have_findent && !b:have_findent_getindent
      return
   endif
   let old = b:findent_flags
   let b:findent_flags = input("findent flags:",b:findent_flags)
   if b:have_findent
      if Findent_get_indentprog() != ""
	 call Findent_set_indentprog()
      else
	 let x = input( "Cannot use flags '".b:findent_flags."' Will use '".old."'")
	 let b:findent_flags = old
	 return
      endif
   endif
   if b:have_findent_getindent
      if Findent_get_getindent() != ""
	 call Findent_set_getindent() 
      else
	 let x = input( "Cannot use flags '".b:findent_flags."' Will use '".old."'")
	 let b:findent_flags = old
	 return
      endif
   endif
endfunction

function! Findent_set_indentprog()
   let p = Findent_get_indentprog()
   if p == ""
      echomsg "Warning '".s:fortran_indentprog."' not usable as equalprg"
      echomsg "Using default for equalprg"
      setlocal equalprg=
      let b:have_findent = 0
   else
      execute 'setlocal equalprg='.substitute(p,' ','\\ ','g')
      let b:have_findent = 1
   endif
endfunction

function! Findent_set_getindent()
   if Findent_get_getindent() == ""
      echomsg "Warning '".s:findent_getindent."' not usable as indentexpr"
      echomsg "Using default for indentexpr"
      setlocal indentexpr=
      let b:have_findent_getindent = 0
   else
      setlocal indentexpr=Findent_getindent()
      setlocal indentkeys=*<Return>,*<Up>,*<Down>,*<Esc>,!^F
      let b:have_findent_getindent = 1
   endif
endfunction

function! Findent_use_wb_toggle()
   let b:findent_use_whole_buffer = !b:findent_use_whole_buffer
endfunction

"======================================================================================

if exists("g:findent_flags")
   let b:findent_flags = g:findent_flags
endif

if !exists("b:findent_flags")
   let b:findent_flags = "-i".&shiftwidth
endif

if !exists("b:findent_use_whole_buffer")
   let b:findent_use_whole_buffer = 0
endif

if !exists("g:findent")
   let g:findent = "/usr/bin/findent"
endif

" determine fixed or free or unknown based on suffix

let b:fortran_format = Get_format_from_extension(expand('%:e'))

" if format is unknown, try to get it from the source
if b:fortran_format == "unknown"
   " determine command to determine free or fixed
   let b:findent_freefixed = Findent_get_freefixed()
   if b:findent_freefixed == ""
      let b:fortran_format = "free"
      echomsg "Cannot determine format (free/fixed), will use" b:fortran_format
   else
      let r=system(b:findent_freefixed,join(getline(1,10000),"\n"))
      if r =~ "free"
	 let b:fortran_format = "free"
      else
	 let b:fortran_format = "fixed"
      endif
   endif
endif

if b:fortran_format == "free"
   let g:fortran_free_source = 1
   let b:fortran_free_source = 1
   let b:fortran_fixed_source = 0
else
   let g:fortran_fixed_source = 1
   let b:fortran_fixed_source = 1
   let b:fortran_free_source = 0
endif

call Findent_set_indentprog()

call Findent_set_getindent()

