OBJS = Gfx.o Font.o Help.o Tombstone.o

PROG1 = TombstoneSDL.exe
PROGRAMS = $(PROG1)

# Use -DGIF_SUPPORT to enable Gif format
LIBGIF_DIR = /usr/lib
INCGIF_DIR = /usr/include

# -DUSE_ALL_FONT  : to enable all fonts 
# -DGIF_SUPPORT : to enable GIF library usage

# Linux build options
#CXXFLAGS += -O2 -DLINUX -DGIF_SUPPORT -Wall `sdl-config --cflags` -Iicons -I$(INCGIF_DIR)
#LDFLAGS =`sdl-config --libs` $(LIBGIF_DIR)/libungif.a 

CXXFLAGS += -g -O0 -Wall -DGIF_SUPPORT `sdl-config --cflags` -Iicons -I$(INCGIF_DIR)
LDFLAGS =`sdl-config --libs`  -L$(LIBGIF_DIR) -lungif -lSDL_mixer

CC = g++
LD = g++

all: $(PROGRAMS)

clean:
	rm -f $(OBJS) $(POBJS) $(PROGRAMS) *~ core

$(PROG1): $(OBJS) 
	$(LD) $(OBJS) $(LDFLAGS) -o $(PROG1) 

.cc.o:
	$(CC) $(CXXFLAGS) -c $<

.cpp.o:
	$(CC) $(CXXFLAGS) -c $<

.c.o:
	$(CC) $(CXXFLAGS) -c $<
