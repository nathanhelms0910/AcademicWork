function! InsertText()
  execute "normal! gg"
  let line = search("Computer Science", "W")
  while line > 0 
  execute "normal! i Longwood University "
  execute "normal! 4w"
  let line = search("Computer Science", "W")
  endwhile
endfunction
map <F2> :call InsertText()<Cr>
