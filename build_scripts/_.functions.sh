#!/usr/bin/env bash

#functions
fn_echobold() {
	echo -e "\e[1m$1\e[0m"
}



fn_stoponerror () {
if [ $1 -ne 0 ]; then
        lNo=$(expr $2 - 1)
        echo "  [Error at line No $lNo. $2]"
        exit
else
   echo "    [Success]"
fi
}

fn_dirEnsure () {
if [ ! -d "$1" ]; then
  mkdir -p "$1"
fi
}

fn_dirEnsureClear () {
	if [ -d "$1" ]; then
	  rm -rf "$1"
	fi
	mkdir -p "$1"
}

fn_stoponfilenotexist () {
if [ ! -f "$1" ]; then
        echo "  [Error. File \"$1\" not exist]"
        exit
fi
}

fn_run() {
	app=$1
	fn_echobold "    Running executable."
    set -x #echo on
	$app
	set +x #echo off
}

fn_rundetached() {
	app=$1
	fn_echobold "    Running executable detached from terminal."
    set -x #echo on
	nohup $app > /dev/null &
	set +x #echo off
}

fn_usagehelp () {
printf "\n"
printf "Build instructions


Build common object files:

    ./build.sh linux objs

Build application executable:

    ./build.sh linux exe test2.c
    or ./build.sh linux exe test.c
    or ./build.sh linux exe YourFilenameLocatedInSrcDir.c

Build app and run

    ./build.sh linux exe test-canvas.c run

Build app and run detached from terminal

    /build.sh linux exe test-canvas.c rund

Clean build directory

    ./build.sh clean

"
}
#source config functions
fn_configwrite() {
   errors=""
   fn_echobold "Writng library config file: \"$libconfigfile\""
   #libversion=$(head --lines 1 $libversionfile)
	if [ ! -f "$libversionfile" ]; then
			errors="$errors \n  - file \"$libversionfile\" not exist;"
	fi
	libversion=$(head --lines 1 $libversionfile)
	if [ -f "$libversionfile" ] && [ "$libversion" = "" ]; then
			errors="$errors \n  - file \"$libversionfile\" contains empty 1st line (must be version string);"
	fi
	if [ "$libconfigfile" = "" ]; then
			errors="$errors \n  - libconfigfile variable not set;"
	fi		
	if [ "$libplatform" = "notset" ]; then
			errors="$errors \n  - libplatform variable not set;"
	fi	
	#final steps
	if [ !  "$errors" = "" ]; then
			printf " [\n"
			printf "  Function failed failed due to errors: $errors"
			printf "\n ]\n"
			exit
	else
	    echo "    libversion $libversion"
		echo "#define GKIT_VERSION        \"$libversion\"" > $libconfigfile
		fn_stoponerror "$?" $LINENO
		echo "    libplatform $libplatform"
		echo "#define GKIT_PLATFORM     \"$libplatform\"" >> $libconfigfile
		fn_stoponerror "$?" $LINENO
		
	fi	
}

#gcc functions

fn_buildobjs() {
    fn_dirEnsure "$dirbuildobjs"
    buildobjs_Parameters="-c -g -I$dirsrc/lib -pedantic -Wall"
	for file in "${libFiles[@]}"
	do :
	   printf "\n"
	   fn_echobold "creating object from \"$file\""
	   cmd="gcc -c $dirsrclib/$file -c -g -I$dirsrclib -pedantic -Wall -o $dirbuildobjs/$file.o"
	   echo "    $cmd"
	   $cmd 
	   fn_stoponerror "$?" $LINENO
	   printf "\n"
	done
}

fn_buildexe() {
    fn_dirEnsureClear "$dirbuildexe"
    file=$1
	printf "\n"
	fn_echobold "    Creating object from \"$file\""
    buildobjs_Parameters=""	
	cmd="gcc -c $dirsrc/$file -c -g -I$dirsrclib -pedantic -Wall -o $dirbuildexe/$file.o"
	echo $cmd
	$cmd	
	fn_stoponerror "$?" $LINENO
	printf "\n"
	fn_echobold "    Linking \"$file\""
	cmd="gcc $dirbuildobjs/*.o $dirbuildexe/*.o -o $dirbuildexe/$file.run -lX11"
	echo "$cmd"
	$cmd
	fn_stoponerror "$?" $LINENO
	printf "\n"s
	rm "$dirbuildexe/$file.o"
}



#end functions
