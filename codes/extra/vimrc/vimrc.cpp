set nu ai si cindent et ts=4 sw=4 so=10 undofile cmdheight=1
syntax on
inoremap {} {}<left><return><up><end><return>
au BufReadPost * if line("'\"")>0 && line("'\"")<=line("$") | exe "normal! g'\"" | endif
nnoremap <leader>r :w<CR>:let f=input('file: ')<Bar>exe 'botright vert term sh -c "g++ -fsanitize=address -g '.@%.' && ./a.out'.(empty(f)?'':' <'.f).'"'<CR>


