#include "src/mbrreader.h"

#ifdef WIN32
#include "src/os/mbrwin.h"
#elif LINUX
#include "src/os/mbrlnx.h"
#endif

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

int readSector(const char* device, const unsigned int sector, char* buffer, const int maxlen) {
	__fdtype fd;
	int read = 0;
	fd = openFd(device);
	if ( isValidFd(fd) ) {
		read = __readSector( fd, sector, buffer, maxlen);
		closeFd( fd );
	}

	return read;
}

