#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2
echo "Arg3: "$3
echo "Arg4: "$4

#OUTPUTDIR=`cygpath $1`
OUTPUTDIR=$1
#APP_RELEASES=`cygpath $2`
APP_RELEASES=$2
OUTPUTFILENAME=$3
BDSCOMMONDIR=$4

echo "OUTPUTDIR: "$OUTPUTDIR
echo "AppReleases: "$APP_RELEASES
echo "Outputfilename: "$OUTPUTFILENAME
echo "BDSCOMMONDIR: "$BDSCOMMONDIR

#Extract version
VERSION=`cat ./../../VERSION.txt | tr -d '\r'`
APPNAME=MiniBot

echo "Copy stuff"
mkdir $APP_RELEASES/$APPNAME

dest=$APP_RELEASES/$APPNAME
SRC_DIR="./../../source"

#Borland Packages and dll's
#CG_REDIST="/cygdrive/c/CodeGear/Tokyo/bin"
CG_REDIST="/c/CodeGear/Tokyo/bin"
suffix="250.bpl"

#Other 3rd Party binaries
#miscRedist="/cygdrive/p/redist"
miscRedist="/p/redist"

files=(
$SRC_DIR/../*.txt                                
$SRC_DIR/../resources/*.ico                      
$OUTPUTDIR/$OUTPUTFILENAME                       

#DS Binaries
$OUTPUTDIR/dslCommon.dll                         
$OUTPUTDIR/dslIPC.dll                            
$OUTPUTDIR/dslMath.dll                           
$OUTPUTDIR/dslPlugins.dll                        
$OUTPUTDIR/dslVCLCommon.dll                      

$OUTPUTDIR/atFoundation.dll                      
$OUTPUTDIR/atResources.dll                       
$OUTPUTDIR/atBarcodeReader.dll                   
$OUTPUTDIR/atArrayBotCore.dll                    
$OUTPUTDIR/atVCLCommon.dll                       
$OUTPUTDIR/atSSI.dll                             

$BDSCOMMONDIR/BPL/dslVCLComponents.bpl          
$BDSCOMMONDIR/BPL/dslVCLVisualComponents.bpl    
$BDSCOMMONDIR/BPL/atVCLComponents.bpl               
$BDSCOMMONDIR/BPL/atVCLVisualComponents.bpl         
$BDSCOMMONDIR/BPL/atVCLAPTVisualComponents.bpl      
$BDSCOMMONDIR/BPL/atVCLDataModules.bpl              

$CG_REDIST/borlndmm.dll                         
$CG_REDIST/cc32250mt.dll                        
$CG_REDIST/midas.dll                            
$CG_REDIST/bcbsmp$suffix                        
$CG_REDIST/dbexpress$suffix                     
$CG_REDIST/dbrtl$suffix                         
$CG_REDIST/dbxcds$suffix                        
$CG_REDIST/DBXCommonDriver$suffix               
$CG_REDIST/DBXDevartPostgreSQLDriver$suffix     
$CG_REDIST/DBXMySQLDriver$suffix                
$CG_REDIST/dsnap$suffix                         
$CG_REDIST/rtl$suffix                           
$CG_REDIST/vcl$suffix                           
$CG_REDIST/vclactnband$suffix                   
$CG_REDIST/vclimg$suffix                        
$CG_REDIST/vclx$suffix                          
$CG_REDIST/tee9$suffix                          
$CG_REDIST/vcldb$suffix                         

$miscRedist/navusbapi.dll                                        
$miscRedist/Thorlabs.MotionControl.TCube.StepperMotor.dll        
$miscRedist/Thorlabs.MotionControl.TDIEngine.dll                 
$miscRedist/Thorlabs.MotionControl.IntegratedStepperMotors.dll   
$miscRedist/Thorlabs.MotionControl.TCube.DCServo.dll             
$miscRedist/Thorlabs.MotionControl.Benchtop.StepperMotor.dll     
$miscRedist/Thorlabs.MotionControl.DeviceManager.dll             
$miscRedist/dbexppgsql40.dll                                     
)

for file in "${files[@]}"
do 
    echo "Copying file: $file to $dest" 
    cp $file $dest
done

#instead of using local bin folder
cp $miscRedist/navusbapi.dll                                        $OUTPUTDIR
cp $miscRedist/Thorlabs.MotionControl.TCube.StepperMotor.dll        $OUTPUTDIR
cp $miscRedist/Thorlabs.MotionControl.TDIEngine.dll                 $OUTPUTDIR
cp $miscRedist/Thorlabs.MotionControl.IntegratedStepperMotors.dll   $OUTPUTDIR
cp $miscRedist/Thorlabs.MotionControl.TCube.DCServo.dll             $OUTPUTDIR
cp $miscRedist/Thorlabs.MotionControl.Benchtop.StepperMotor.dll     $OUTPUTDIR
cp $miscRedist/Thorlabs.MotionControl.DeviceManager.dll             $OUTPUTDIR
cp $SRC_DIR/../*.txt                                                $OUTPUTDIR
cp $SRC_DIR/../resources/*.ico                                      $OUTPUTDIR

