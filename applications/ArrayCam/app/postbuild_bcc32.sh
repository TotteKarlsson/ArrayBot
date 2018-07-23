#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2
echo "Arg3: "$3
echo "Arg4: "$4

OUTPUTDIR=`cygpath $1`
APP_RELEASES=`cygpath $2`
OUTPUTFILENAME=$3
BDSCOMMONDIR=$4

echo "OUTPUTDIR: "$OUTPUTDIR
echo "AppReleases: "$APP_RELEASES
echo "Outputfilename: "$OUTPUTFILENAME
echo "BDSCOMMONDIR: "$BDSCOMMONDIR

#Extract version
VERSION=`cat ../VERSION.txt | tr -d '\r'`
APPNAME=ArrayCam
echo "Copy stuff"
mkdir $APP_RELEASES/$APPNAME

dest=$APP_RELEASES/$APPNAME

cp ./../*.txt $dest
cp $OUTPUTDIR/$OUTPUTFILENAME $dest

#DS Binaries
cp $OUTPUTDIR/dslFoundation.dll                 $dest
cp $OUTPUTDIR/dslVCLCommon.dll                  $dest

cp $OUTPUTDIR/atFoundation.dll                  $dest
#cp $OUTPUTDIR/atResources.dll                   $dest
cp $OUTPUTDIR/atVCLCommon.dll                   $dest
cp $OUTPUTDIR/atSSI.dll                         $dest
cp $OUTPUTDIR/bm.exe                            $dest

cp $BDSCOMMONDIR/BPL/dslVCLComponents.bpl       $dest
cp $BDSCOMMONDIR/BPL/dslVCLVisualComponents.bpl $dest

cp $BDSCOMMONDIR/BPL/atComponents.bpl           $dest    
cp $BDSCOMMONDIR/BPL/ArrayCamPackage.bpl        $dest

#Borland Packages and dll's
CG_REDIST="/cygdrive/c/CodeGear/Tokyo/bin"

cp $CG_REDIST/borlndmm.dll                      $dest
cp $CG_REDIST/cc32250mt.dll                     $dest

suffix="250.bpl"
cp $CG_REDIST/bindcomp$suffix                   $dest
cp $CG_REDIST/bindcompvcl$suffix                $dest
cp $CG_REDIST/bindengine$suffix                 $dest
cp $CG_REDIST/dbexpress$suffix                  $dest
cp $CG_REDIST/dbrtl$suffix                      $dest
cp $CG_REDIST/dbxcds$suffix                     $dest
cp $CG_REDIST/DbxCommonDriver$suffix		    $dest
cp $CG_REDIST/DbxDevartPostgreSQLDriver$suffix	$dest
cp $CG_REDIST/DBXMySQLDriver$suffix		        $dest
cp $CG_REDIST/dsnap$suffix                      $dest
cp $CG_REDIST/rtl$suffix                        $dest
cp $CG_REDIST/vcl$suffix                        $dest
cp $CG_REDIST/vclactnband$suffix                $dest
cp $CG_REDIST/vcldb$suffix                      $dest
cp $CG_REDIST/vclimg$suffix                     $dest
cp $CG_REDIST/vclx$suffix                       $dest
cp $CG_REDIST/Tee9$suffix                       $dest

miscRedist="/cygdrive/p/redist"
cp $miscRedist/dbexppgsql40.dll                 $dest
cp $miscRedist/wiping.ell                       $dest
cp $miscRedist/navusbapi.dll                    $dest
cp $miscRedist/uc480.dll                        $dest
cp $miscRedist/uc480_tools.dll                  $dest

#ELLiptec motor stage
elliptec="/cygdrive/p/libs/elliptec/Source Code/ELLO/bin/Release"
cp "$elliptec"/Thorlabs.Elliptec.ELLO.exe         $dest
cp "$elliptec"/*.dll                              $dest
cp "$elliptec"/*.chm                              $dest
cp "$elliptec"/*.config                           $dest

#for LOCAL bin folder
cp $miscRedist/dbexppgsql40.dll                 $OUTPUTDIR
cp $miscRedist/navusbapi.dll                    $OUTPUTDIR
cp $miscRedist/uc480.dll                        $OUTPUTDIR
cp $miscRedist/uc480_tools.dll                  $OUTPUTDIR

