#ifndef __MBRWIN_H_
#define __MBRWIN_H_

#include <windows.h>
#include <stdio.h>

typedef HANDLE __fdtype;

bool isValidFd(__fdtype fd);
__fdtype openFd(const char* dev);
void closeFd(__fdtype fd);
int __readSector(__fdtype fd, const unsigned int sector, char* buffer, const unsigned int maxlen);

#endif