#ifndef __MBRREADER_H_
#define __MBRREADER_H_

int readMBR(const char* device, char* buffer, const int maxlen);
int readSector(const char* device, const unsigned int sector, char* buffer, const int maxlen);

#endif
