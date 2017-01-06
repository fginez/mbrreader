#ifndef __MBRREADER_H_
#define __MBRREADER_H_

#ifdef WIN32
#include "src/os/mbrwin.h"
#elif LINUX
#include "src/os/mbrlnx.h"
#endif

int readMBR(const char* device, char* buffer, const int maxlen);

#endif
