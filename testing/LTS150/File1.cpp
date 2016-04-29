#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Thorlabs.MotionControl.IntegratedStepperMotors.h"

namespace ISC_Console
{
	int main(int argc, char* argv[])
	{
		if(argc < 1)
		{
			printf("Usage = Example_ISC [serial_no] [position: optional (0 - 1715200)] [velocity: optional (0 - 3838091)]\r\n");
			char c = _getch();
			return 1;
		}

		int serialNo = 45000001;
		if(argc > 1)
		{
			serialNo = atoi(argv[1]);
		}

		// get parameters from command line
		int position = 0;
        if(argc > 2)
		{
			position = atoi(argv[2]);
        }
        int velocity = 0;
        if(argc > 3)
        {
			velocity = atoi(argv[3]);
		}
		// identify and access device
        char testSerialNo[16];
		//sprintf_s(testSerialNo, "%d", serialNo);

        try
		{
			// Build list of connected device
			if (TLI_BuildDeviceList() == 0)
			{
				// get device list size
				short n = TLI_GetDeviceListSize();
				// get LTS serial numbers
				char serialNos[100];
				TLI_GetDeviceListByTypeExt(serialNos, 100, 45);

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
                if(ISC_Open(testSerialNo) == 0)
                {
                    // start the device polling at 200ms intervals
                    ISC_StartPolling(testSerialNo, 200);
                    // NOTE The following uses Sleep functions to simulate timing
                    // In reality, the program should read the status to check that commands have been completed
                    Sleep(3000);
                    // Home device
                    ISC_Home(testSerialNo);
                    printf("Device %s homing\r\n", testSerialNo);
                    Sleep(3000);
                    // set velocity if desired
                    if(velocity > 0)
                    {
                        int currentVelocity, currentAcceleration;
                        ISC_GetVelParams(testSerialNo, &currentVelocity, &currentAcceleration);
                        ISC_SetVelParams(testSerialNo, velocity, currentAcceleration);
                    }
                    // move to position (channel 1)
                    ISC_MoveToPosition(testSerialNo, position);
                    printf("Device %s moving\r\n", testSerialNo);
                    Sleep(2000);
                    int pos = ISC_GetPosition(testSerialNo);
                    printf("Device %s moved to %d\r\n", testSerialNo, pos);
                    // stop polling
					ISC_StopPolling(testSerialNo);
					// close device
					ISC_Close(testSerialNo);
				}
			}
		}
		catch (char * e)
		{
			printf("Error %s\r\n", e);
		}
//		char c = _getch();
		return 0;
	}
}
