/* <c-s> normal mapped key 
 * execute make, then execute the binary wordfreq in the bin directory
 */
/* setlocal foldmethod=syntax
 *     Vim folding commands
 *---------------------------------
 *zf#j fold from the cursor down # lines.
 *zf/ string creates a fold from the cursor to string .
 *zj moves the cursor to the next fold.
 *zk moves the cursor to the previous fold.
 *za toggle a fold at the cursor.
 *zo opens a fold at the cursor.
 *zO opens all folds at the cursor.
 *zc closes a fold under cursor. 
 *zm increases the foldlevel by one.
 *zM closes all open folds.
 *zr decreases the foldlevel by one.
 *zR decreases the foldlevel to zero -- all folds will be open.
 *zd deletes the fold at the cursor.
 *zE deletes all folds.
 *[z move to start of open fold.
 *]z move to end of open fold.
 */
/* hi Folded cterm=bold ctermfg=239
 */
/* In MAKEFILE print var in window vim
 * w !make print-_TF
 */
/* Resize windows <c-j> and <c-k>
 * nmap <c-j> :res -1<cr>
 * nmap <c-k> :res +1<cr>
 * nmap <c-h> :vertical resize -1<cr>
 * nmap <c-l> :vertical resize +1<cr>
 */
/* NERDTree toggle <c-n>
 * :nmap <c-n> :NERDTreeToggle<cr>
 */
/* todo and tasks pages <space>
 *   to move completed bottom
 *   repopulate todo's
 *   nmap <buffer> <space> :wa<cr>:silent !cd ..; grep -h TODO astr/astr.c > data/todo.java; gsed -i 's/    //g' data/todo.java;<cr>:redraw!<cr>
 *   nmap <buffer> <space> :g/\[x\]/m $<cr>:nohl<cr>
 */
/* <X> x'd, <N> new task keys
 */
/* folds <za> toggle
 */
/* loc go back <c-o> <c-i>
 * Go back to previous location
 * or go forward
 */
