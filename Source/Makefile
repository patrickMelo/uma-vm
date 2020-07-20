# Common Variables

CURRENT_DIRECTORY	= $(shell pwd)
SOURCE_DIRECTORY	= $(CURRENT_DIRECTORY)
BINARY_DIRECTORY	= $(shell dirname $(SOURCE_DIRECTORY))/Binaries
BINARY_PATH			= $(BINARY_DIRECTORY)/UmaVM
CXX					= clang++
CXX_FLAGS			= -O2 -std=gnu++17 -fno-rtti -fno-exceptions -Wno-sign-compare -Wno-format-security -Wno-narrowing -D_FILE_OFFSET_BITS=64
DEBUG_FLAGS			= -g3 -DUMAVM_DEBUG=1
INCLUDES			= -I$(SOURCE_DIRECTORY)/
LIBS				=
STRIP				= @true
STRIP_EXE			= strip
ARCH				= x64

# Common Objects

OBJECTS	=	$(SOURCE_DIRECTORY)/Kernel/Kernel.o \
			$(SOURCE_DIRECTORY)/Runtime/Debugger.o \
			$(SOURCE_DIRECTORY)/Runtime/Library.o \
			$(SOURCE_DIRECTORY)/Runtime/Program.o \
			$(SOURCE_DIRECTORY)/Runtime/Runtime.o \
			$(SOURCE_DIRECTORY)/Runtime/Libraries/Standard.o \
			$(SOURCE_DIRECTORY)/Main.o

# Linux Variables

LINUX_CXX		= clang++
LINUX_CXX_FLAGS	=
LINUX_INCLUDES	=
LINUX_LIBS		= -lpthread
LINUX_OBJECTS	=

# Windows Variables

WINDOWS_CXX			= x86_64-w64-mingw32-g++
WINDOWS_CXX_FLAGS	= -static-libgcc -static-libstdc++
WINDOWS_INCLUDES	=
WINDOWS_LIBS		= -lm
WINDOWS_STRIP		= x86_64-w64-mingw32-strip
WINDOWS_OBJECTS		=

# "Final" Variables

ifndef TARGET
	TARGET = linux
endif

ifndef TYPE
	TYPE = debug
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
	CXX			= $(WINDOWS_CXX)
	STRIP_EXE	= $(WINDOWS_STRIP)
endif

ifeq ($(TYPE), debug)
	CXX_FLAGS	+= $(DEBUG_FLAGS)
	ARCH		:= debug.$(ARCH)
endif

ifeq ($(TYPE), release)
	STRIP = $(STRIP_EXE) -s
endif

# Targets

%.o: %.cxx
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -c $< -o $@

all: $(OBJECTS)
	mkdir -p $(BINARY_DIRECTORY)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(BINARY_PATH).$(ARCH)
	$(STRIP) $(BINARY_PATH).$(ARCH)

clean:
	find $(SOURCE_DIRECTORY)/ -type f -iname "*.o" -exec rm -v {} \;

help:
	@echo ""
	@echo "Usage: make TARGET=<target name> TYPE=<debug|release>"
	@echo ""
	@echo "Available targets:"
	@echo " - linux"
	@echo " - windows"
	@echo ""
	@echo "Defaults to: linux, debug"