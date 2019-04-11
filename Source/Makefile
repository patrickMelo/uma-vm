# Common Variables

CURRENT_DIRECTORY	= $(shell pwd)
SOURCE_DIRECTORY	= $(CURRENT_DIRECTORY)
BINARY_PATH			= $(shell dirname $(SOURCE_DIRECTORY))/Binaries/UmaVM
CXX					= clang++
CXX_FLAGS			= -std=c++0x -fno-rtti -fno-exceptions -Wno-sign-compare -Wno-format-security -Wno-narrowing -D_FILE_OFFSET_BITS=64 -fPIC
RELEASE_FLAGS		= -O3
DEBUG_FLAGS			= -g3 -DUMAVM_DEBUG=1
INCLUDES			= -I$(SOURCE_DIRECTORY)/
LIBS				=
STRIP				= @true
STRIP_EXE			= strip

# Common Objects

OBJECTS	=	$(SOURCE_DIRECTORY)/Kernel.o \
			$(SOURCE_DIRECTORY)/Main.o \
			$(SOURCE_DIRECTORY)/Program.o \
			$(SOURCE_DIRECTORY)/Runtime.o

# Linux Variables

LINUX_CXX		= clang++
LINUX_CXX_FLAGS	=
LINUX_INCLUDES	=
LINUX_LIBS		= -lpthread
LINUX_OBJECTS	=

# Windows Variables

WINDOWS_CXX_32		= i686-w64-mingw32-g++
WINDOWS_CXX_64		= x86_64-w64-mingw32-g++
WINDOWS_CXX_FLAGS	= -static-libgcc -static-libstdc++
WINDOWS_INCLUDES	=
WINDOWS_LIBS		= -Wl,-Bstatic -lpthread
WINDOWS_STRIP_32	= i686-w64-mingw32-strip
WINDOWS_STRIP_64	= x86_64-w64-mingw32-strip
WINDOWS_OBJECTS		=

# "Final" Variables

ifndef TARGET
	TARGET = linux
endif

ifndef TYPE
	TYPE = debug
endif

ifndef BITS
	BITS = 64
endif

ifeq ($(BITS), 32)
	ARCH	= x86
else
	ARCH	= x86_64
endif

ifeq ($(TARGET), linux)
	CXX			= $(LINUX_CXX)
	CXX_FLAGS	+= $(LINUX_CXX_FLAGS)
	INCLUDES	+= $(LINUX_INCLUDES)
	LIBS		+= $(LINUX_LIBS)
	OBJECTS		+= $(LINUX_OBJECTS)
endif

ifeq ($(TARGET), windows)
	ARCH		:= $(ARCH).exe
	CXX_FLAGS	+= $(WINDOWS_CXX_FLAGS)
	INCLUDES	+= $(WINDOWS_INCLUDES)
	LIBS		+= $(WINDOWS_LIBS)
	OBJECTS		+= $(WINDOWS_OBJECTS)

	ifeq ($(BITS), 32)
		CXX			= $(WINDOWS_CXX_32)
		STRIP_EXE	= $(WINDOWS_STRIP_32)
	else
		CXX			= $(WINDOWS_CXX_64)
		STRIP_EXE	= $(WINDOWS_STRIP_64)
	endif
endif

ifeq ($(TYPE), debug)
	CXX_FLAGS	+= $(DEBUG_FLAGS)
	ARCH		:= debug.$(ARCH)
else
	CXX_FLAGS	+= $(RELEASE_FLAGS)
endif

ifeq ($(TYPE), release)
	STRIP = $(STRIP_EXE) -s
endif

# Targets

%.o: %.cxx
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $< -o $@

all: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(BINARY_PATH).$(ARCH)
	$(STRIP) $(BINARY_PATH).$(ARCH)

clean:
	find $(SOURCE_DIRECTORY)/ -type f -iname "*.o" -exec rm -v {} \;

help:
	@echo ""
	@echo "Usage: make TARGET=<target name> TYPE=<debug|release> BITS=<32|64>"
	@echo ""
	@echo "Available targets:"
	@echo " - linux"
	@echo " - windows"
	@echo ""
	@echo "Defaults to: linux, debug, 64"
