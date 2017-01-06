CC=g++
INC_DIR=../
LIB_DIR=../output
OUT_DIR=../output
SRC_DIR=../src
RUN_DIR=obj

CFLAGS=-I$(INC_DIR) -c -Wall -fPIC -DLINUX

LIBS=-static $(LIB_DIR)/libmbrreader.a

MBRREADER_SOURCES=$(SRC_DIR)/main/main.cpp $(SRC_DIR)/main/printbuffer.cpp

LIBMBRREADER_SOURCES = $(SRC_DIR)/mbrreader.cpp $(SRC_DIR)/os/mbrlnx.cpp

all: libmbrreader.a mbrreader

libmbrreader.a: $(LIBMBRREADER_SOURCES:.cpp=.o)
	ar rcvs $(OUT_DIR)/$@ $(LIBMBRREADER_SOURCES:.cpp=.o)

mbrreader:  $(MBRREADER_SOURCES:.cpp=.o)
	$(CC) $(LDFLAGS) $(MBRREADER_SOURCES:.cpp=.o) $(LIBS) -o $(OUT_DIR)/$@

clean:
	(cd ../; find . -name "*.o" -type f -print0 | xargs -0 /bin/rm -f)
	rm $(OUT_DIR)/mbrreader
	rm $(OUT_DIR)/libmbrreader.a

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@


