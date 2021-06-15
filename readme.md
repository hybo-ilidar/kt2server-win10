# Version of KT2SERVER which runs on Windows 10

Open using Visual Studio file `opencvTest.sln`



## Notes from Dr. Son 15 Jun 2021 (CRC update)

The change is mainly done to eliminate the wrongly-received rows, which
are shown as noticeable lines on the display.

1. A checksum data is appended after each row.

2. It is read by the VS project program. If the checksum is not matched,
   the program will not update corresponding row in the display memory.

3. Therefore, the corresponding region of the previous image will be
   kept if something is wrong with the received row.

4. Noticeable defective lines (such as all-black) will be removed.
   (there will be still some artifacts in dynamic scenes)

Please update the serial to socket converter program for KT.
In your case you will not send a Ethernet packet if the checksum 
matching is failed.



