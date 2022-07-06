#include<windows.h>
#include<iostream>

#define EX_FATAL 1
#define BUFSIZE 140
using namespace std;

//Declare here the types 
namespace comm_02
{

class Api {
public:
	static void init(HANDLE* hCom, wchar_t* COMPORT, int nComRate, int nComBits, COMMTIMEOUTS& timeout);
	static void purge(HANDLE * hCom);
	static void open(HANDLE * hCom, wchar_t* COMPORT);
	static int setConf(HANDLE * hCom, int nComRate, int nComBits, COMMTIMEOUTS & timeout);
	static void close(HANDLE* hCom);
};
class TransmitterApi : public Api {
public:
	static void print(HANDLE* hCom, LPCVOID buf, DWORD szBuf);
};
class ReceiverApi : public Api {
public:
	static DWORD read(HANDLE* hCom, LPVOID buf, DWORD szBuf);
};
}
	namespace comm_02
	{

		//***********************Api*********************
		// Prototype the functions to be used

		/*
			Initializes the port and sets the communication parameters

		*/
		void Api::init(HANDLE* hCom, wchar_t* COMPORT, int nComRate, int nComBits, COMMTIMEOUTS& timeout) {
			open(hCom, COMPORT);						// Initializes hCom to point to PORT#
			purge(hCom);									// Purges the COM port
			setConf(hCom, nComRate, nComBits, timeout);		// Uses the DCB structure to set up the COM port
			purge(hCom);
		}
		void Api::purge(HANDLE* hCom) {
			PurgeComm(*hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
		}
		// Sub functions
		void Api::open(HANDLE* hCom, wchar_t* COMPORT) {
			// Call the CreateFile() function 
			*hCom = CreateFile(
				COMPORT,									// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
				GENERIC_READ | GENERIC_WRITE,				// Open for read and write
				NULL,										// No sharing allowed
				NULL,										// No security
				OPEN_EXISTING,								// Opens the existing com port
				FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
				NULL										// No template
			);

			if (*hCom == INVALID_HANDLE_VALUE) {
				printf("\nFatal Error 0x%x: Unable to open\n", GetLastError());
			}
			else {
				printf("\nCOM is now open\n");
			}
		}
		int Api::setConf(HANDLE* hCom, int nComRate, int nComBits, COMMTIMEOUTS& timeout) {
			DCB dcb;										// Windows device control block
		// Clear DCB to start out clean, then get current settings
			memset(&dcb, 0, sizeof(dcb));
			dcb.DCBlength = sizeof(dcb);
			if (!GetCommState(*hCom, &dcb))
				return(0);

			// Set our own parameters from Globals
			dcb.BaudRate = nComRate;						// Baud (bit) rate
			dcb.ByteSize = (BYTE)nComBits;					// Number of bits(8)
			dcb.Parity = 0;									// No parity	
			dcb.StopBits = ONESTOPBIT;						// One stop bit
			if (!SetCommState(*hCom, &dcb))
				return(0);

			// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
			memset((void*)&timeout, 0, sizeof(timeout));
			timeout.ReadIntervalTimeout = 500;				// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
			timeout.ReadTotalTimeoutMultiplier = 1;			// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
			timeout.ReadTotalTimeoutConstant = 5000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
			SetCommTimeouts(*hCom, &timeout);
			return(1);
		}

		//***********************TransmitterApi*********************
		void TransmitterApi::print(HANDLE* hCom, LPCVOID buf, DWORD szBuf) {
			int i = 0;
			DWORD NumberofBytesTransmitted;
			LPDWORD lpErrors = 0;
			LPCOMSTAT lpStat = 0;

			i = WriteFile(
				*hCom,										// Write handle pointing to COM port
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
		}
		void Api::close(HANDLE* hCom) {
			CloseHandle(hCom); // Close the handle to Tx/Rx port 
		}
		//***********************ReceiverApi*********************
		DWORD ReceiverApi::read(HANDLE* hCom, LPVOID buf, DWORD szBuf) {
			int i = 0;
			DWORD NumberofBytesRead;
			LPDWORD lpErrors = 0;
			LPCOMSTAT lpStat = 0;

			i = ReadFile(
				*hCom,										// Read handle pointing to COM port
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

			return(NumberofBytesRead);
		}


		int mainTransmitter() {
			wchar_t COMPORT[] = L"COM6";						// COM port used for Rx (use L"COM6" for transmit program)
			HANDLE hCom;										// Pointer to the selected COM port (Transmitter)

			int nComRate = 9600;								// Baud (Bit) rate in bits/second 
			int nComBits = 8;									// Number of bits per frame
			COMMTIMEOUTS timeout;								// A commtimeout struct variable

			Api::init(&hCom, COMPORT, nComRate, nComBits, timeout);	// Initialize the Rx port
			Sleep(500);

			// Transmit side 
			char msgOut[] = "Hi there person";							// Sent message	
			TransmitterApi::print(&hCom, msgOut, strlen(msgOut) + 1);			// Send string to port - include space for '\0' termination
			Sleep(500);													// Allow time for signal propagation on cable 

			// Tear down both sides of the comm link
			Api::purge(&hCom);											// Purge the port
			Api::close(&hCom);											// Close the handle port 

			system("pause");
			return 0;
		}

		int mainReceiver() {
			wchar_t COMPORT[] = L"COM7";						// COM port used for Rx (use L"COM7" for transmit program)
			HANDLE hCom;										// Pointer to the selected COM port (Transmitter)

			int nComRate = 9600;								// Baud (Bit) rate in bits/second 
			int nComBits = 8;									// Number of bits per frame
			COMMTIMEOUTS timeout;								// A commtimeout struct variable

			Api::init(&hCom, COMPORT, nComRate, nComBits, timeout);	// Initialize the Rx port
			Sleep(500);

			// Receive side  
			char msgIn[BUFSIZE];
			DWORD bytesRead;
			bytesRead = ReceiverApi::read(&hCom, msgIn, BUFSIZE);			// Receive string from port
			//printf("Length of received msg = %d", bytesRead);
			msgIn[bytesRead] = '\0';
			printf("\nMessage Received: %s\n\n", msgIn);				// Display message from port												// Allow time for signal propagation on cable 

			// Tear down both sides of the comm link
			Api::purge(&hCom);											// Purge the port
			Api::close(&hCom);											// Close the handle port 

			system("pause");
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
		return comm_02::main();
	}