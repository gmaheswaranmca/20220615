#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<iostream>
#include<cwchar>
#include<string>
#include<cstring>
#define EX_FATAL 1
#define BUFSIZE 140
using namespace std;
namespace comm_01
{
	int mainTransmitter();
	int mainReceiver();
	int main();
}namespace comm_01
{
	int mainTransmitter() {
		wchar_t COMPORT[256] = L"COM6";						// COM port used for Rx (use L"COM6" for transmit program)
		cout << "(Sending)Enter comm port name:"; 
		wscanf(L"%ls", COMPORT);
		HANDLE hCom;										// Pointer to the selected COM port (Transmitter)

		int nComRate = 9600;								// Baud (Bit) rate in bits/second 
		int nComBits = 8;									// Number of bits per frame
		COMMTIMEOUTS timeout;								// A commtimeout struct variable




		//1 createPortFile(HANDLE* hCom, wchar_t* COMPORT)
		// Set the hCom HANDLE to point to a COM port, initialize for reading and writing, open the port and set securities
		// Call the CreateFile() function 
		hCom = CreateFile(
			COMPORT,									// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
			GENERIC_READ | GENERIC_WRITE,				// Open for read and write
			NULL,										// No sharing allowed
			NULL,										// No security
			OPEN_EXISTING,								// Opens the existing com port
			FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
			NULL										// No template
		);

		if (hCom == INVALID_HANDLE_VALUE) {
			cout << endl << "\nFatal Error 0x%x: Unable to open" << GetLastError() << endl;
		}
		else {
			cout << endl << "COM is now open" << endl;
		}

		//2 purgePort(HANDLE* hCom)
		// Purge any outstanding requests on the serial port (initialize)
		PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

		//3 int SetComParms(HANDLE* hCom, int nComRate, int nComBits, COMMTIMEOUTS timeout)
		DCB dcb;										// Windows device control block
		// Clear DCB to start out clean, then get current settings
		memset(&dcb, 0, sizeof(dcb));
		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(hCom, &dcb))
			return(0);

		// Set our own parameters from Globals
		dcb.BaudRate = nComRate;						// Baud (bit) rate
		dcb.ByteSize = (BYTE)nComBits;					// Number of bits(8)
		dcb.Parity = 0;									// No parity	
		dcb.StopBits = ONESTOPBIT;						// One stop bit
		if (!SetCommState(hCom, &dcb))
			return(0);

		// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
		memset((void*)&timeout, 0, sizeof(timeout));
		timeout.ReadIntervalTimeout = 2000;				// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
		timeout.ReadTotalTimeoutMultiplier = 1;			// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
		timeout.ReadTotalTimeoutConstant = 5000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
		SetCommTimeouts(hCom, &timeout);

		//2 purgePort(HANDLE* hCom)
		// Purge any outstanding requests on the serial port (initialize)
		PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

		// Transmit side 
		char msgOut[] = "Hi there person";							// Sent message	
		string text;
		cout << "Enter text to transmit/send:";
		cin.ignore();getline(cin, text);
		strcpy(msgOut, text.c_str());
		//

		//START void outputToPort(HANDLE * hCom, LPCVOID buf, DWORD szBuf)
		// Output/Input messages to/from ports 
		int i = 0;
		DWORD NumberofBytesTransmitted;
		LPDWORD lpErrors = 0;
		LPCOMSTAT lpStat = 0;
		LPCVOID buf = msgOut;
		DWORD szBuf = strlen(msgOut) + 1;
		i = WriteFile(
			hCom,										// Write handle pointing to COM port
			buf,										// Buffer size
			szBuf,										// Size of buffer
			&NumberofBytesTransmitted,					// Written number of bytes
			NULL
		);
		// Handle the timeout error
		if (i == 0) {
			printf("\nWrite Error: 0x%x\n", GetLastError());
			ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.	
		}
		else
			printf("\nSuccessful transmission, there were %ld bytes transmitted\n", NumberofBytesTransmitted);
		//
		//END void outputToPort(HANDLE * hCom, LPCVOID buf, DWORD szBuf)
		// Output/Input messages to/from ports 

		Sleep(500);													// Allow time for signal propagation on cable 


		// Tear down both sides of the comm link
		//2 purgePort(HANDLE* hCom)
		// Purge any outstanding requests on the serial port (initialize)
		PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);


		//
		CloseHandle(hCom);										// Close the handle to Tx port 

		//system("pause");

		return 0;
	}

	int mainReceiver() {
		wchar_t COMPORT[50] = L"COM7";						// COM port used for Rx (use L"COM7" for receive program)
		cout << "(Sending)Enter comm port name:";
		wscanf(L"%ls", COMPORT);
		HANDLE hCom;										// Pointer to the selected COM port (Receiver)

		int nComRate = 9600;								// Baud (Bit) rate in bits/second 
		int nComBits = 8;									// Number of bits per frame
		COMMTIMEOUTS timeout;								// A commtimeout struct variable




		//1 createPortFile(HANDLE* hCom, wchar_t* COMPORT)
		// Set the hCom HANDLE to point to a COM port, initialize for reading and writing, open the port and set securities
		// Call the CreateFile() function 
		hCom = CreateFile(
			COMPORT,									// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
			GENERIC_READ | GENERIC_WRITE,				// Open for read and write
			NULL,										// No sharing allowed
			NULL,										// No security
			OPEN_EXISTING,								// Opens the existing com port
			FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
			NULL										// No template
		);

		if (hCom == INVALID_HANDLE_VALUE) {
			cout << endl << "\nFatal Error 0x%x: Unable to open" << GetLastError() << endl;
		}
		else {
			cout << endl << "COM is now open" << endl;
		}

		//2 purgePort(HANDLE* hCom)
		// Purge any outstanding requests on the serial port (initialize)
		PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

		//3 int SetComParms(HANDLE* hCom, int nComRate, int nComBits, COMMTIMEOUTS timeout)
		DCB dcb;										// Windows device control block
		// Clear DCB to start out clean, then get current settings
		memset(&dcb, 0, sizeof(dcb));
		dcb.DCBlength = sizeof(dcb);
		if (!GetCommState(hCom, &dcb))
			return(0);

		// Set our own parameters from Globals
		dcb.BaudRate = nComRate;						// Baud (bit) rate
		dcb.ByteSize = (BYTE)nComBits;					// Number of bits(8)
		dcb.Parity = 0;									// No parity	
		dcb.StopBits = ONESTOPBIT;						// One stop bit
		if (!SetCommState(hCom, &dcb))
			return(0);

		// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
		memset((void*)&timeout, 0, sizeof(timeout));
		timeout.ReadIntervalTimeout = 500;				// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
		timeout.ReadTotalTimeoutMultiplier = 1;			// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
		timeout.ReadTotalTimeoutConstant = 5000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
		SetCommTimeouts(hCom, &timeout);

		//2 purgePort(HANDLE* hCom)
		// Purge any outstanding requests on the serial port (initialize)
		PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);

		// Receive side  
		char msgIn[BUFSIZE];
		DWORD bytesRead;
		//

		//START DWORD inputFromPort(HANDLE* hCom, LPVOID buf, DWORD szBuf)
		int i = 0;
		DWORD NumberofBytesRead;
		LPDWORD lpErrors = 0;
		LPCOMSTAT lpStat = 0;
		LPVOID buf = msgIn;
		DWORD szBuf = BUFSIZE;

		i = ReadFile(
			hCom,										// Read handle pointing to COM port
			buf,										// Buffer size
			szBuf,  									// Size of buffer - Maximum number of bytes to read
			&NumberofBytesRead,
			NULL
		);
		// Handle the timeout error
		if (i == 0) {
			printf("\nRead Error: 0x%x\n", GetLastError());
			ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.
		}
		else
			printf("\nSuccessful reception!, There were %ld bytes read\n", NumberofBytesRead);
		bytesRead = NumberofBytesRead;
		//END DWORD inputFromPort(HANDLE* hCom, LPVOID buf, DWORD szBuf)

														// Allow time for signal propagation on cable 
		msgIn[bytesRead] = '\0';
		printf("\nMessage Received: %s\n\n", msgIn);				// Display message from port

		// Tear down both sides of the comm link
		//2 purgePort(HANDLE* hCom)
		// Purge any outstanding requests on the serial port (initialize)
		PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);


		//
		CloseHandle(hCom);										// Close the handle to Rx port 

		//system("pause");

		return 0;
	}

	//*********************Driver Code***********************************
	int main() {
		int exitCode = EXIT_SUCCESS;
		int menu;
		cout << "Enter option(1-Transmitter,2-Receiver):"; cin >> menu;
		if (1 == menu) {
			exitCode = mainTransmitter();
		}
		else if (2 == menu) {
			exitCode = mainReceiver();
		}

		return exitCode;
	}
}

int main() {
	return comm_01::main();
}