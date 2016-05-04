// Example_TST001.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
//#if defined TestCode
//#include "..\..\..\Instruments\Thorlabs.TCube.Stepper\Thorlabs.TCube.Stepper\Thorlabs.MotionControl.TCube.StepperMotor.h"
//#else
#include "C:\\pDisk\\ArrayBot\\third_party\\Kinesis\\Thorlabs.MotionControl.TCube.StepperMotor.h"
//#endif

#pragma comment(lib, "C:\\pDisk\\ArrayBot\\third_party\\Kinesis\\Thorlabs.MotionControl.TCube.StepperMotorB.lib")

namespace TST_Console
{
    int main(int argc, char* argv[])
    {
        if(argc < 1)
        {
            printf("Usage = Example_TST001 [serial_no] [position: optional (0 - 1715200)] [velocity: optional (0 - 3838091)]\r\n");
            char c = _getch();
            return 1;
        }
        int serialNo = 80861696;
        if(argc > 1)
        {
            serialNo = atoi(argv[1]);
        }
        // get parameters from command line
        int position = 1715200 * 9;
        if(argc > 2)
        {
            position = atoi(argv[2]);
        }
        int velocity = 3838091;
        if(argc > 3)
        {
            velocity = atoi(argv[3]);
        }
        // identify and access device
        char testSerialNo[16];
        sprintf(testSerialNo, "%d", serialNo);
        try
        {
            // Build list of connected device
            if (TLI_BuildDeviceList() == 0)
            {
                // get device list size
                short n = TLI_GetDeviceListSize();
                // get BBD serial numbers
                char serialNos[100];
                TLI_GetDeviceListByTypeExt(serialNos, 100, 80);
                // output list of matching devices
                char *p = strtok(serialNos, ",");
                while(p != NULL)
                {
                    TLI_DeviceInfo deviceInfo;
                    // get device info from device
                    TLI_GetDeviceInfo(p, &deviceInfo);
                    // get strings from device info structure
                    char desc[65];
                    strncpy(desc, deviceInfo.description, 64);
                    desc[64] = '\0';
                    char serialNo[9];
                    strncpy(serialNo, deviceInfo.serialNo, 8);
                    serialNo[8] = '\0';
                    // output
                    printf("Found Device %s=%s : %s\r\n", p, serialNo, desc);
                    p = strtok(NULL, ",");
                }
                // open device
                if(SCC_Open(testSerialNo) == 0)
                {
                    // start the device polling at 200ms intervals
                    SCC_StartPolling(testSerialNo, 200);
                    // NOTE The following uses Sleep functions to simulate timing
                    // In reality, the program should read the status to check that commands have been completed
                    Sleep(3000);
                    // Home device
                    //SCC_Home(testSerialNo);
                    //printf("Device %s homing\r\n", testSerialNo);
                    //Sleep(3000);
                    // set velocity if desired
                    if(velocity > 0)
                    {
                        int currentVelocity, currentAcceleration;
                        SCC_GetVelParams(testSerialNo, &currentVelocity,&currentAcceleration);
                        SCC_SetVelParams(testSerialNo, velocity, currentAcceleration);
                    }
                    // move to position (channel 1)
                    SCC_MoveToPosition(testSerialNo, position);
                    printf("Device %s moving\r\n", testSerialNo);
                    Sleep(2000);
                    int pos = SCC_GetPosition(testSerialNo);
                    printf("Device %s moved to %d\r\n", testSerialNo, pos);


                    SCC_MoveAtVelocity(testSerialNo, MOT_Backwards);
                    printf("Device %s moving\r\n", testSerialNo);
                    Sleep(2000);
                    SCC_StopImmediate(testSerialNo);

                    SCC_MoveAtVelocity(testSerialNo, MOT_Forwards);
                    printf("Device %s moving\r\n", testSerialNo);

                    pos = SCC_GetPosition(testSerialNo);
                    printf("Device %s moved to %d\r\n", testSerialNo, pos);
					SCC_StopImmediate(testSerialNo);
                    // stop polling
                    SCC_StopPolling(testSerialNo);
                    // close device
                    SCC_Close(testSerialNo);
                }
            }
        }
        catch (char * e)
        {
            printf("Error %s\r\n", e);
        }
//        char c = _getch();
        return 0;
    }

}
