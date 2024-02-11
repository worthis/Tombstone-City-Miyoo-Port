# run `TARGET=miyoo make` to build for MIYOO MINI

TARGET_EXEC = tombstone
TOMBSTONE_VERSION = 1.0

MIYOO_CXX := arm-linux-gnueabihf-g++
MIYOO_PREFIX := /opt/miyoomini-toolchain/arm-linux-gnueabihf/libc
MIYOO_CXXFLAGS := -Wall -I$(MIYOO_PREFIX)/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -DMIYOO_MINI
MIYOO_LDFLAGS := -L$(MIYOO_PREFIX)/usr/lib -lSDL -lSDL_mixer

LINUX_CXX := g++
LINUX_PREFIX := /
LINUX_CXXFLAGS := -Wall -I$(LINUX_PREFIX)/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -DLINUX_MODE
LINUX_LDFLAGS := -L$(LINUX_PREFIX)/usr/lib -lSDL -lSDL_mixer

ifeq ($(TARGET),miyoo)
	CXX=$(MIYOO_CXX)
	CXXFLAGS=$(MIYOO_CXXFLAGS)
	LDFLAGS=$(MIYOO_LDFLAGS)
else
	CXX=$(LINUX_CXX)
	CXXFLAGS=$(LINUX_CXXFLAGS)
	LDFLAGS=$(LINUX_LDFLAGS)
endif

BUILD_DIR := ./build/$(TARGET)
SRC_DIRS := ./src
BIN_DIR := ./bin
ASSETS_DIR := ./assets

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

bin/$(TARGET_EXEC): $(OBJS)
	mkdir -p $(dir $@)
	mkdir -p $(BIN_DIR)/assets/images
	$(CXX) $(OBJS) -o bin/$(TARGET_EXEC) $(LDFLAGS)
	cp -r $(ASSETS_DIR)/images/bmp/* $(BIN_DIR)/assets/images
	cp -r $(ASSETS_DIR)/sfx $(BIN_DIR)/assets/

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)/*
	rm -r $(BIN_DIR)/*
