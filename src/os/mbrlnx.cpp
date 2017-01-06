#include "src/os/mbrlnx.h"

bool isValidFd(__fdtype fd) {
	if ( -1 != fd ) {
		return true;
	}

#ifdef _DEBUG
	printf("%s\n", strerror(errno));
#endif

	return false;
}	

__fdtype openFd(const char* dev) {
	__fdtype fd = open(dev, O_RDWR);
	return fd;
}

void closeFd(__fdtype fd){
	close( fd );
}

int __readSector(__fdtype fd, const unsigned int sector, char* buffer, const unsigned int maxlen){
    int bread = 0;
    lseek(fd, sector*512, SEEK_SET);
    if ( maxlen >= 512 ) {
    	bread = read(fd, buffer, 512);
    }
    
    return bread;
}
