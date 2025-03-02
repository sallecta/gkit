#!/usr/bin/env bash

#configs
appname="x11gui"
dirbuild="$PWD/buildout"
dirbuildobjs="$dirbuild/objs"
dirbuildexe="$dirbuild/exe"
dirsrc="$PWD/src"
dirsrclib="$dirsrc/lib"
libversionfile="$dirsrclib/version"
libconfigfile="$dirsrclib/gkit_config.h"
libplatform="notset"
libversion="notset"
#end configs

source "$PWD/build_scripts/_.functions.sh"

libFiles=( "gkit_window.c" "stk_text.c" "stk_menu.c" "stk_button.c"  \
"gkit_widget.c" "gkit_widget_canvas.c" "stk_progress_bar.c" \
)

if [ "$1" = "--linux" ] || [ "$1" = "linux" ]; then
	if [ "$2" = "--objs" ] || [ "$2" = "objs" ]; then
	    libplatform="linux"
		fn_configwrite	
		fn_buildobjs	
	elif [ "$2" = "--exe" ] || [ "$2" = "exe" ]; then
	    fn_stoponfilenotexist "$dirsrc/$3"
		fn_buildexe $3
		if [ "$4" = "--run" ] || [ "$4" = "run" ]; then
			fn_run "$dirbuild/exe/$3.run"
		elif [ "$4" = "--rund" ] || [ "$4" = "rund" ]; then
		    fn_rundetached "$dirbuild/exe/$3.run"
		fi
	else
		fn_echobold "Wrong or emty argument #2 = $2"
		fn_usagehelp
	fi

	
	
elif [ "$1" = "--mingw" ] || [ "$1" = "mingw" ]; then 
    echo "Not implemented."
elif [ "$1" = "--test" ] || [ "$1" = "test" ]; then 
    echo "Not implemented."
elif [ "$1" = "--clean" ] || [ "$1" = "clean" ]; then 
    rm -rf $dirbuild
    mkdir -p $dirbuild
elif [ "$1" = "--help" ] || [ "$1" = "help" ]; then 
    fn_usagehelp	
else
    fn_echobold "Wrong argument."
	fn_usagehelp
fi
