

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include "serial.h"
#include <stdio.h>

static HANDLE hCom1;

#define _CRT_SECURE_NO_WARNINGS 1

void c2wc( const char* pstrSrc, wchar_t pwstrDest[])
{
  int nLen = (int)strlen(pstrSrc) + 1;
  mbstowcs( pwstrDest, pstrSrc, nLen );
}

int serialOpen(char port[], int baud){

	DCB dcb;
	HANDLE hCom;
	DWORD dwError;
	BOOL fSucess;

	wchar_t port_wchar[10];
	c2wc(port, port_wchar);

	hCom = CreateFile(port_wchar,
				GENERIC_READ | GENERIC_WRITE,
				0, // comm devices must be opened w/exclusive access
				NULL, // no security attrs 
				OPEN_EXISTING, 
				0, // not overlapped I/O
				NULL
				);

 

	if(hCom == INVALID_HANDLE_VALUE){
				dwError = GetLastError();                       
				return (-1);
	}

     
// Omit the call to SetupComm to use the default queue sizes.
// Get the current configuration.

 
	fSucess = GetCommState(hCom, &dcb);

	if(!fSucess) return(-2);
	
// Fill in the DCB: baud=whatever, 8 data bits, no parity, 1 stop bit.  

	dcb.BaudRate = baud; 
	dcb.fBinary = TRUE;
	dcb.fParity = FALSE; 
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT; 
	fSucess = SetCommState(hCom, &dcb); 

 
	if (!fSucess) return (-3);

	hCom1 = hCom;
	return (0);
} 

int serialClose(void)
{
	CloseHandle(hCom1);
	return 0;
}

int setreadtimeout(int initialTimeout)
{ 
	COMMTIMEOUTS timeouts; 

	timeouts.ReadIntervalTimeout = 0;         
	timeouts.ReadTotalTimeoutMultiplier = initialTimeout;         
	timeouts.ReadTotalTimeoutConstant = 0; 

	if (!SetCommTimeouts(hCom1, &timeouts)) return -1; 

	return 0;
} 



// read byte from serial port.
// returns 0x00xx on success
// returns 0x01xx on failure
unsigned short serialReadByte(void)
{
	unsigned char tmp;
	unsigned long numread=0; 

	ReadFile(hCom1, (void *)&tmp, 1, &numread, NULL); 

    if (numread != 1){
		//printf("!"); 
		return 0x100;
	}

	return tmp;
}

int serialReadBlock(unsigned char * dst, int size)
{
	unsigned long count;
	ReadFile(hCom1, (void*)dst, size, &count, NULL);

	return count;
}

float serialReadFloat(void)
{
	float dst;
	serialReadBlock((unsigned char*)&dst, 4);
	return dst;
}

int serialReadInt(void)
{
	int dst;
	serialReadBlock((unsigned char*)&dst, 4);
	return dst;
}

short serialReadShort(void)
{
	short dst;
	serialReadBlock((unsigned char*)&dst, 2);
	return dst;
}



// sends a byte to the serial port.  returns 0 on success and -1 on failure. 
int serialWriteByte(unsigned char c)
{
	unsigned long numBytes;

	if (!WriteFile(hCom1, (void *)&c, 1, &numBytes, NULL) || numBytes != 1)
		return -1;

	return 0;
}

// sends a byte to the serial port.  returns 0 on success and -1 on failure. 
int serialWriteBlock(unsigned char * src, int size)
{
	unsigned long numBytes;

	if (!WriteFile(hCom1, (void *)src, size, &numBytes, NULL) || numBytes != size)
		return -1;

	return 0;
}

int serialWriteFloat(float src)
{
	unsigned long numBytes;

	if (!WriteFile(hCom1, (void *)&src, 4, &numBytes, NULL) || numBytes != 4)
		return -1;

	return 0;
}

int serialWriteInt(int src)
{
	unsigned long numBytes;

	if (!WriteFile(hCom1, (void *)&src, 4, &numBytes, NULL) || numBytes != 4)
		return -1;

	return 0;
}

int serialWriteShort(short src)
{
	unsigned long numBytes;

	if (!WriteFile(hCom1, (void *)&src, 2, &numBytes, NULL) || numBytes != 2)
		return -1;

	return 0;
}





