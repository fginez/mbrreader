#include "src/os/mbrwin.h"

bool isValidFd(__fdtype fd){
	if ( INVALID_HANDLE_VALUE != fd ) {
		return true;
	}

#ifdef _DEBUG
	char* messageBuffer;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, 
				  GetLastError(), 
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				  (LPSTR)&messageBuffer, 
				  0, 
				  NULL);

	printf("%s\n", messageBuffer);

	LocalFree(messageBuffer);
#endif

	return false;
}

__fdtype openFd(const char* dev) {
	return CreateFile((LPCSTR) dev, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
}

void closeFd(__fdtype fd) {
	CloseHandle( fd );
}

int __readSector(__fdtype fd, const unsigned int sector, char* buffer, const unsigned int maxlen) {
	int read = 0;

	SetFilePointer( fd , sector*512 , 0, FILE_BEGIN);
	if ( maxlen >= 512 ) {
		DWORD dwRead;
		if ( ReadFile( fd, buffer, 512, &dwRead, 0) ) {
			read = (int) dwRead;
		}
	}

	return read;
}
