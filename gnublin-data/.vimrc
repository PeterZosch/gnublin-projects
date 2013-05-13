set nocompatible
set tabstop=4
set titleold="Terminal"
syn on

color desert

" zeigt ausschnittgroesse der angezeigten Datei an rechts unten
set showcmd

"Zeilennummer und Cursorposition rechts unten einblenden
set ruler


"Titel der geöffneten Datei im Terminalfenseter anzeigen
let &titlestring =  expand("%:t")
if &term == "screen"
  set t_ts=^[k
  set t_fs=^[\
endif
if &term == "screen" || &term == "xterm"
  set title
endif
