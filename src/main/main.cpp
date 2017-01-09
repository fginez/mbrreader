#include "src/mbrreader.h"
#include "src/main/printbuffer.h"
#include <iostream>
#include <stdio.h>#include <string.h>

using namespace std;

#define MBR_OFFSET_BOOTSTRAP		0	// Bootstrap - Codigo de arranque
#define MBR_OFFSET_PARTITION_TABLE	446 // Partition table - Tabela de particoes
#define MBR_OFFSET_PARTITION_1		446 // Partition entry 1 - Entrada da particao 1
#define MBR_OFFSET_PARTITION_2		462 // Partition entry 2 - Entrada da particao 2
#define MBR_OFFSET_PARTITION_3		478 // Partition entry 3 - Entrada da particao 3
#define MBR_OFFSET_PARTITION_4		494 // Partition entry 4 - Entrada da particao 4
#define MBR_OFFSET_BOOT_SIGNATURE	510	// Boot signature - Assinatura de boot

#define MBR_LEN_BOOTSTRAP			446
#define MBR_LEN_PARTITION_ENTRY		16
#define MBR_LEN_PARTITION_TABLE		4*MBR_LEN_PARTITION_ENTRY
#define MBR_LEN_BOOT_SIGNATURE		2

#define PARTITION_ENTRY_LEN_CHSADDR	3

#pragma pack(1)
typedef struct _MBR {
	char bootstrap[MBR_LEN_BOOTSTRAP];
	char partitionTable[MBR_LEN_PARTITION_TABLE];
	char bootSignature[MBR_LEN_BOOT_SIGNATURE];
} MBR, *LPMBR;

typedef struct _MBR_PARTITION_TABLE {
	char partition1[MBR_LEN_PARTITION_ENTRY];
	char partition2[MBR_LEN_PARTITION_ENTRY];
	char partition3[MBR_LEN_PARTITION_ENTRY];
	char partition4[MBR_LEN_PARTITION_ENTRY];
} MBR_PARTITION_TABLE, * LPMBR_PARTITION_TABLE;

typedef struct _MBR_PARTITION_ENTRY {
	char status;
	char chs_first[PARTITION_ENTRY_LEN_CHSADDR];
	char type;
	char chs_last[PARTITION_ENTRY_LEN_CHSADDR];
	int	lba_first;
	int  sectors;
} MBR_PARTITION_ENTRY, *LPMBR_PARTITION_ENTRY;

typedef struct _MBR_PARTITION_ENTRY_CHSADDR {
	char head;
	unsigned h_cilinder:2, sector : 6, l_cilinder: 8;
} MBR_PARTITION_ENTRY_CHSADDR, *LPMBR_PARTITION_ENTRY_CHSADDR;

#pragma pack()

unsigned int getSectorFromCHS( LPMBR_PARTITION_ENTRY_CHSADDR chs ) {
	return chs->sector;	
}

unsigned int getHeadfromCHS( LPMBR_PARTITION_ENTRY_CHSADDR chs ) {
	return (unsigned int) (chs->head & 0xFF);
}

unsigned int getCilinderFromCHS( LPMBR_PARTITION_ENTRY_CHSADDR chs ) {
	int cilinder = (chs->h_cilinder << 8 | chs->l_cilinder);
	return (unsigned int) cilinder;
}

void setDefaultParam( char* param, const unsigned int maxlen ) {
#ifdef WIN32
	sprintf_s(param, maxlen, "\\\\.\\PhysicalDrive0");
#elif LINUX
	snprintf(param, maxlen, "/dev/sda/");
#endif
}

int main(int argc, char* argv[])
{
	char szDisk[50];
	char *mbr = NULL;
	int bufflen = 512;
	int read = 0;

	mbr = new char[bufflen];
	if ( NULL == mbr ) {
		cout << "Out of memory\n";
		return -1;
	}

	memset( mbr, 0, bufflen );
	memset( szDisk, 0, sizeof(szDisk) );

	if (argc == 1) {
		setDefaultParam(szDisk, sizeof(szDisk));
	} else {
		strcpy(szDisk, argv[1]);
	}

	read = readMBR( szDisk, mbr, bufflen );
	if ( 0 >= read ) {
		cout << "Failed to read MBR!\n";
		delete[] mbr;
		return -1;
	}

	cout << "MBR sector contents:\n";
	print_hex_dump2((const unsigned char*) mbr, bufflen, 16, "\t");

	if ( 1 ) {
		LPMBR lpmbr = (LPMBR) mbr;
		cout << "MBR bootstrap:\n";
		print_hex_dump2((const unsigned char*) lpmbr->bootstrap, sizeof(lpmbr->bootstrap), 16, "\t");

		cout << "MBR partition table:\n";
		print_hex_dump2((const unsigned char*) lpmbr->partitionTable, sizeof(lpmbr->partitionTable), 16, "\t");

		cout << "MBR boot signature:\n";
		print_hex_dump2((const unsigned char*) lpmbr->bootSignature, sizeof(lpmbr->bootSignature), 16, "\t");
	}

	if ( 1 ) {
		LPMBR lpmbr = (LPMBR) mbr;
		LPMBR_PARTITION_TABLE ptable = (LPMBR_PARTITION_TABLE) lpmbr->partitionTable;
		LPMBR_PARTITION_ENTRY entries[4] = {(LPMBR_PARTITION_ENTRY) ptable->partition1, 
											(LPMBR_PARTITION_ENTRY) ptable->partition2, 
											(LPMBR_PARTITION_ENTRY) ptable->partition3, 
											(LPMBR_PARTITION_ENTRY) ptable->partition4 };

		for ( int i=0; i<4; i++ ) {
			cout << "Partition " << i << ":\n";
			print_hex_dump2((const unsigned char*) entries[i], sizeof(MBR_PARTITION_ENTRY), 16, "\t");

			cout << "Status: " << (unsigned int)entries[i]->status << "\n";
			cout << "CHS first: " <<  "h:" << getHeadfromCHS((LPMBR_PARTITION_ENTRY_CHSADDR)entries[i]->chs_first)
				 << " s:" << getSectorFromCHS((LPMBR_PARTITION_ENTRY_CHSADDR)entries[i]->chs_first)
				 << " c:" << getCilinderFromCHS((LPMBR_PARTITION_ENTRY_CHSADDR)entries[i]->chs_first) << "\n";
			cout << "Type: " <<  (unsigned int) entries[i]->type << "\n";
			cout << "CHS last: " <<  "h:" << getHeadfromCHS((LPMBR_PARTITION_ENTRY_CHSADDR)entries[i]->chs_last)
				 << " s:" << getSectorFromCHS((LPMBR_PARTITION_ENTRY_CHSADDR)entries[i]->chs_last)
				 << " c:" << getCilinderFromCHS((LPMBR_PARTITION_ENTRY_CHSADDR)entries[i]->chs_last) << "\n";
			cout << "LBA first: " <<  entries[i]->lba_first << "\n";
			cout << "Sectors: " <<  entries[i]->sectors << "\n";
		}
	}

	getchar();

	delete[] mbr;
	return 0;
}
