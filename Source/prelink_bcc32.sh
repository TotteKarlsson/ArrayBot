#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2

BDSCOMMONDIR=$1
AT_ROOT=`cygpath $2`
LINK_FOLDER=`cygpath $BDSCOMMONDIR`/lib
echo "BDSCOMMONDIR: "$BDSCOMMONDIR

echo "Copy .lib files required for linking"

TP=$AT_ROOT"/thirdparty"
cp $TP/Thorlabs/*.lib                           $LINK_FOLDER
cp $TP/navitar/*.lib                           $LINK_FOLDER

