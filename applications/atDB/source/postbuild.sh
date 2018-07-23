#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2
echo "Arg3: "$3
echo "Arg4: "$4

OUTPUTDIR=$1
APP_RELEASES=$2
OUTPUTFILENAME=$3
BDSCOMMONDIR=$4

echo "OUTPUTDIR: "$OUTPUTDIR
echo "AppReleases: "$APP_RELEASES
echo "Outputfilename: "$OUTPUTFILENAME
echo "BDSCOMMONDIR: "$BDSCOMMONDIR

#Extract version
VERSION=`cat ../VERSION.txt | tr -d '\r'`
APPNAME=atDB
echo "Copy stuff"
mkdir $APP_RELEASES/$APPNAME

dest=$APP_RELEASES/$APPNAME
SRC_DIR="."

#Borland Packages and dll's
#CG_REDIST="/cygdrive/c/CodeGear/Tokyo/bin"
CG_REDIST="/c/CodeGear/Tokyo/bin"
suffix="250.bpl"

#Other 3rd Party binaries
#miscRedist="/cygdrive/p/redist"
miscRedist="/p/redist"

files=(
$SRC_DIR/../*.txt 
$SRC_DIR/Resources/*.ico 
$OUTPUTDIR/$OUTPUTFILENAME 

#DS Binaries
$OUTPUTDIR/dslCommon.dll               
$OUTPUTDIR/dslVCLCommon.dll                
$BDSCOMMONDIR/BPL/dslVCLComponents.bpl     
$BDSCOMMONDIR/BPL/dslVCLVisualComponents.bpl           

$OUTPUTDIR/atCore.dll                      
$OUTPUTDIR/atDataBase.dll                  
$OUTPUTDIR/atBarcodeReader.dll             
$BDSCOMMONDIR/BPL/atVCLComponents.bpl           

$CG_REDIST/bindcomp$suffix                 
$CG_REDIST/bindcompvcl$suffix              
$CG_REDIST/bindengine$suffix               
$CG_REDIST/dbexpress$suffix                
$CG_REDIST/dbrtl$suffix                    
$CG_REDIST/dbxcds$suffix                   
$CG_REDIST/DbxCommonDriver$suffix		  
$CG_REDIST/DbxDevartPostgreSQLDriver$suffix
$CG_REDIST/dsnap$suffix                    
$CG_REDIST/rtl$suffix                      
$CG_REDIST/vcl$suffix                      
$CG_REDIST/vclactnband$suffix              
$CG_REDIST/vcldb$suffix                    
$CG_REDIST/vclimg$suffix                   
$CG_REDIST/vclx$suffix                     
$CG_REDIST/borlndmm.dll                    
$CG_REDIST/cc32250mt.dll                   
$CG_REDIST/midas.dll                       

$miscRedist/dbexppgsql40.dll             
$miscRedist/tsclib.dll                   
$miscRedist/navusbapi.dll                
)

for file in "${files[@]}"
do 
    echo "Copying file: $file to $dest" 
    cp $file $dest
done



