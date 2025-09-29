set nocompatible              " be iMproved, required
filetype off                  " required

set expandtab
set smarttab
set tabstop=2
set softtabstop=1
set shiftwidth=2
set foldcolumn=2

set number

syntax on

set mouse=a

set noerrorbells
set novisualbell

set encoding=utf8

" set clipboard^=unnamed,unnamedplus
set clipboard=unnamedplus

" Keep Plugin commands between vundle#begin/end.

" Set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
" Alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')
call vundle#begin()

" Let Vundle manage Vundle, required
Plugin 'VundleVim/Vundle.vim'
  Plugin 'vim-airline/vim-airline'
  Plugin 'vim-airline/vim-airline-themes'
"  Plugin 'chilledheart/vim-clangd'
"  Plugin 'hukeyue/vim-clangd'
  Plugin 'preservim/nerdtree'
    Plugin 'ryanoasis/vim-devicons'
    Plugin 'tiagofumo/vim-nerdtree-syntax-highlight'
    Plugin 'tpope/vim-fugitive'
  Plugin 'vim-syntastic/syntastic'
  Plugin 'Valloric/YouCompleteMe'
    Plugin 'jiangmiao/auto-pairs'
  Plugin 'google/vim-maktaba'
  Plugin 'google/vim-codefmt'
  Plugin 'google/vim-glaive'
  Plugin 'doums/darcula'

" All of your Plugins must be added before the following line
call vundle#end()            " required

call glaive#Install()

" NERDTree "
map <C-n> :NERDTreeToggle<CR>

" Syntactic "
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list=1
let g:syntastic_auto_loc_list=1
let g:syntastic_check_on_open=1
let g:syntastic_check_on_wq=0

" YouCompleteMe "
let g:ycm_enable_semantic_highlighting=1
let g:ycm_auto_trigger = 1

let g:ycm_clangd_binary_path="/usr/bin/clangd"
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/third_party/ycmd/.ycm_extra_conf.py'
" let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/simple_ycm_extra_conf.py'
set runtimepath+=~/.vim/bundle/YouCompleteMe/
" let g:ycm_confirm_extra_conf=0

let g:ycm_complete_in_comments=1
let g:ycm_show_diagnostics_ui=0
let g:ycm_min_num_of_chars_for_completion=1
let g:ycm_seed_identifiers_with_syntax=1

" set completeopt=menu,menuone
" let g:ycm_add_preview_to_completeopt=0

let g:ycm_use_clangd=1

let g:ycm_server_python_interpreter='/usr/bin/python3'
let g:ycm_python_binary_path = '/usr/bin/python3'

" let g:ycm_filetype_whitelist = {
"  \ "c":1,
"  \ "cpp":1,
"  \ "objc":1,
"  \ "sh":1,
"  \ "zsh":1,
"  \ "zimbu":1,
"  \ "python":1,
"  \ }

" ============================================================ "

let MY_YCM_HIGHLIGHT_GROUP = {
      \   'typeParameter': 'PreProc',
      \   'parameter': 'Normal',
      \   'variable': 'Normal',
      \   'property': 'Normal',
      \   'enumMember': 'Normal',
      \   'event': 'Special',
      \   'member': 'Normal',
      \   'method': 'Normal',
      \   'class': 'Special',
      \   'namespace': 'Special',
      \ }

for tokenType in keys( MY_YCM_HIGHLIGHT_GROUP )
  call prop_type_add( 'YCM_HL_' . tokenType,
                    \ { 'highlight': MY_YCM_HIGHLIGHT_GROUP[ tokenType ] } )
endfor

" ============================================================ "

colorscheme darcula
let g:airline_theme='apprentice'

filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginUpdate     - update plugins
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line
