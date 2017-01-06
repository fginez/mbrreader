#include "src/mbrreader.h"

int readMBR(const char* device, char* buffer, const int maxlen) {
	__fdtype fd;
	int read = 0;
	fd = openFd(device);
	if ( isValidFd(fd) ) {
		read = __readSector( fd, 0, buffer, maxlen);
		closeFd( fd );
	}

	return read;
}
