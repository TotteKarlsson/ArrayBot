#define STRICT
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "Serial.h"

int ShowError (LONG lError, LPCTSTR lptszMessage)
{
	// Generate a message text
	TCHAR tszMessage[256];
	wsprintf(tszMessage,_T("%s\n(error code %d)"), lptszMessage, lError);

	// Display message-box and return with an error-code
	::MessageBox(0,tszMessage,_T("Listener"), MB_ICONSTOP|MB_OK);
	return 1;
}

int __cdecl _tmain (int /*argc*/, char** /*argv*/)
{
    CSerial serial;
	LONG    lLastError = ERROR_SUCCESS;

    // Attempt to open the serial port (COM1)
    lLastError = serial.Open(_T("COM4"),0,0,true);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to open COM-port"));

    // Setup the serial port (9600,8N1, which is the default setting)
    lLastError = serial.Setup(CSerial::EBaud115200,CSerial::EData8,CSerial::EParNone,CSerial::EStop1);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port setting"));

	// Setup handshaking (default is no handshaking)
    lLastError = serial.SetupHandshaking(CSerial::EHandshakeHardware);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port handshaking"));

    // Register only for the receive event
    lLastError = serial.SetMask(CSerial::EEventBreak |
								CSerial::EEventCTS   |
								CSerial::EEventDSR   |
								CSerial::EEventError |
								CSerial::EEventRing  |
								CSerial::EEventRLSD  |
								CSerial::EEventRecv);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port event mask"));

	// Use 'non-blocking' reads, because we don't know how many bytes
	// will be received. This is normally the most convenient mode
	// (and also the default mode for reading data).
    lLastError = serial.SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);
	if (lLastError != ERROR_SUCCESS)
		return ::ShowError(serial.GetLastError(), _T("Unable to set COM-port read timeout."));

	// Create a handle for the overlapped operations
	HANDLE hevtOverlapped = ::CreateEvent(0,TRUE,FALSE,0);;
	if (hevtOverlapped == 0)
		return ::ShowError(serial.GetLastError(), _T("Unable to create manual-reset event for overlapped I/O."));

	// Setup the overlapped structure
	OVERLAPPED ov = {0};
	ov.hEvent = hevtOverlapped;

	// Open the "STOP" handle
	HANDLE hevtStop = ::CreateEvent(0,TRUE,FALSE,_T("Overlapped_Stop_Event"));
	if (hevtStop == 0)
		return ::ShowError(serial.GetLastError(), _T("Unable to create manual-reset event for stop event."));

    // Keep reading data, until an EOF (CTRL-Z) has been received
	bool fContinue = true;
	do
	{
		// Wait for an event
		lLastError = serial.WaitEvent(&ov);
		if (lLastError != ERROR_SUCCESS)
			return ::ShowError(serial.GetLastError(), _T("Unable to wait for a COM-port event."));

		// Setup array of handles in which we are interested
		HANDLE ahWait[2];
		ahWait[0] = hevtOverlapped;
		ahWait[1] = hevtStop;

		serial.Write("t");
		// Wait until something happens
		switch (::WaitForMultipleObjects(sizeof(ahWait)/sizeof(*ahWait),ahWait,FALSE,INFINITE))
		{
		case WAIT_OBJECT_0:
			{
				// Save event
				const CSerial::EEvent eEvent = serial.GetEventType();

				// Handle break event
				if (eEvent & CSerial::EEventBreak)
				{
					printf("\n### BREAK received ###\n");
				}

				// Handle CTS event
				if (eEvent & CSerial::EEventCTS)
				{
					printf("\n### Clear to send %s ###\n", serial.GetCTS()?"on":"off");
				}

				// Handle DSR event
				if (eEvent & CSerial::EEventDSR)
				{
					printf("\n### Data set ready %s ###\n", serial.GetDSR()?"on":"off");
				}

				// Handle error event
				if (eEvent & CSerial::EEventError)
				{
					printf("\n### ERROR: ");
					switch (serial.GetError())
					{
					case CSerial::EErrorBreak:		printf("Break condition");			break;
					case CSerial::EErrorFrame:		printf("Framing error");			break;
					case CSerial::EErrorIOE:		printf("IO device error");			break;
					case CSerial::EErrorMode:		printf("Unsupported mode");			break;
					case CSerial::EErrorOverrun:	printf("Buffer overrun");			break;
					case CSerial::EErrorRxOver:		printf("Input buffer overflow");	break;
					case CSerial::EErrorParity:		printf("Input parity error");		break;
					case CSerial::EErrorTxFull:		printf("Output buffer full");		break;
					default:						printf("Unknown");					break;
					}
					printf(" ###\n");
				}

				// Handle ring event
				if (eEvent & CSerial::EEventRing)
				{
					printf("\n### RING ###\n");
				}

				// Handle RLSD/CD event
				if (eEvent & CSerial::EEventRLSD)
				{
					printf("\n### RLSD/CD %s ###\n", serial.GetRLSD()?"on":"off");
				}

				// Handle data receive event
				if (eEvent & CSerial::EEventRecv)
				{
					// Read data, until there is nothing left
					DWORD dwBytesRead = 0;
					do
					{
						char szBuffer[101];

						// Read data from the COM-port
						lLastError = serial.Read(szBuffer,sizeof(szBuffer)-1,&dwBytesRead);
						if (lLastError != ERROR_SUCCESS)
							return ::ShowError(serial.GetLastError(), _T("Unable to read from COM-port."));

						if (dwBytesRead > 0)
						{
							// Finalize the data, so it is a valid string
							szBuffer[dwBytesRead] = '\0';

							// Display the data
							printf("%s\n", szBuffer);
						}
					}
					while (dwBytesRead > 0);
				}
			}
			break;

		case WAIT_OBJECT_0+1:
			{
				// Set the continue bit to false, so we'll exit
				fContinue = false;
			}
			break;

		default:
			{
				// Something went wrong
				return ::ShowError(serial.GetLastError(), _T("Error while calling WaitForMultipleObjects."));
			}
			break;
		}
	}
	while (fContinue);

    // Close the port again
    serial.Close();
    return 0;
}
