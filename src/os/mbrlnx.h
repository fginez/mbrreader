#ifndef __MBRLNX_H_
#define __MBRLNX_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef int __fdtype;

bool isValidFd(__fdtype fd);
__fdtype openFd(const char* dev);
void closeFd(__fdtype fd);
int __readSector(__fdtype fd, const unsigned int sector, char* buffer, const unsigned int maxlen);

#endif
