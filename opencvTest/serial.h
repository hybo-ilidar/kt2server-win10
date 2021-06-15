

#define _CRT_SECURE_NO_WARNINGS

#ifndef SERIAL_H
#define SERIAL_H

int serialOpen(char port[], int baud);
int serialClose(void);

int setreadtimeout(int initialtimeout);

unsigned short serialReadByte(void);
int   serialReadBlock(unsigned char * dst, int size);
float serialReadFloat(void);
int	  serialReadInt(void);
short serialReadShort(void);

int serialWriteByte(unsigned char c);
int serialWriteBlock(unsigned char * src, int size);
int serialWriteFloat(float src);
int serialWriteInt(int src);
int serialWriteShort(short src);

#endif