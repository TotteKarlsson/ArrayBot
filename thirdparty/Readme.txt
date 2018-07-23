ArrayTomography libs thirdparties


DLL's are saved in here with extension DLL_0 so they can be part of the repository
When an API is built an installed, a post build script should copy and rename appropriate DLLs into 
the builds bin folder. The same goes for .lib files

*** ssidll ***
The SSI DLL implements Motorolas, Zebra's Simple Serial Interface that enable communication with the Zebra DS457 scanner.

*** uc480 ***
The uc480 DLL implement communication with Thorlab's Cameras

*** Thorlabs ***
The Thorlab folder contain DLL's required for control of Thorlab stepper and DC motors

*** TSC ***
The TSCLIB.dll contain function to control a TSC Barcode printer
