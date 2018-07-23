#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2

BDSCOMMONDIR=$1
AT_ROOT=`cygpath $2`
BIN_FOLDER=`cygpath $BDSCOMMONDIR`/bin

echo "Bin Folder: "$BIN_FOLDER
echo "Copy .dll files required for runtime"

TP=$AT_ROOT"/thirdparty"
#cp $TP/Thorlabs/*.dll                          $BIN_FOLDER

#Thorlabs
for f in $TP/Thorlabs/*.dll_0; do 
    cp "$f" $BIN_FOLDER/"$(basename "$f" .dll_0).dll"
done

#Navitar
for f in $TP/navitar/*.dll_redist; do 
    cp "$f" $BIN_FOLDER/"$(basename "$f" .dll_redist).dll"
done

#uc480 Camera..
for f in $TP/uc480/*.dll_0; do 
    cp "$f" $BIN_FOLDER/"$(basename "$f" .dll_0).dll"
done

#TSC
for f in $TP/*.dll_0; do 
    cp "$f" $BIN_FOLDER/"$(basename "$f" .dll_0).dll"
done
