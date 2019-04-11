/*
 * Source/Kernel.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_KERNEL_H
#define UMAVM_KERNEL_H

// C/C++

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <cerrno>
#include <cinttypes>
#include <csignal>
#include <limits>
#include <new>
#include <vector>
#include <map>
#include <algorithm>

// We need at least a C++11 compiler.

#if (__cplusplus < 201103L)
	#error "The compiler does not support the C++11 standard."
#endif

// Architectures

#if defined(i386) || defined(__i386) || defined(__i386__)
		#define ArchX86
		#define ArchName "x86"
	#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
			#define ArchX64
			#define ArchName "x86_64"
		#elif defined(__arm__)
				#define ArchARM
				#define ArchName "ARM"
			#else
				#error "Unsupported architecture."
			#endif

// Operating Systems

#if defined(__linux__) || defined(__linux) || defined(linux)
		#define LinuxOS
		#define OSName "Linux"
	#elif defined(__APPLE__) || defined(__MACH__)
			#define macOS
			#define OSName "OSX"
		#elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
				#define WindowsOS
				#define OSName "Windows"
			#else
				#error "Unsupported operating system."
			#endif

#if defined(LinuxOS) || defined(macOS)
	#define UnixOS
#endif

// Platform Specific Definitions

#ifdef WindowsOS
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT _WIN32_WINNT_WIN7
		#define NTDDI_VERSION NTDDI_WIN7
	#endif

	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif

	extern "C" {
		#include <windows.h>
		#include <windowsx.h>
	}

	#undef INFO
	#undef WARNING
	#undef ERROR
	#undef DEBUG
	#undef TEXT
#endif

// Macros

#define TEXT(untranslatedText) untranslatedText

#define INFO(message, ...) Kernel.Info(Tag, TEXT(message), ##__VA_ARGS__)
#define WARNING(message, ...) Kernel.Warning(Tag, TEXT(message), ##__VA_ARGS__)
#define ERROR(message, ...) Kernel.Error(Tag, TEXT(message), ##__VA_ARGS__)
#define DEBUG(message, ...) Kernel.Debug(Tag, TEXT(message), ##__VA_ARGS__)
#define STUB() Kernel.Stub(__PRETTY_FUNCTION__, __FILE__, __LINE__)

#define SWAP16(value) (((value & 0x00FF) << 8) | ((value & 0xFF00) >> 8))
#define SWAP32(value) (((value & 0x000000FF) << 24) | ((value & 0x0000FF00) << 8) | ((value & 0x00FF0000) >> 8) | ((value & 0xFF000000) >> 24))
#define SWAP64(value) (((value & 0x00000000000000FF) << 56) | ((value & 0x000000000000FF00) << 40) | ((value & 0x0000000000FF0000) << 24) | ((value & 0x00000000FF000000) << 8) | \
				  	   ((value & 0x000000FF00000000) >> 8) | ((value & 0x0000FF0000000000 ) >> 24) | ((value & 0x00FF000000000000) >> 40) | ((value & 0xFF00000000000000) >> 56))

// Casts

#define UINT(value) static_cast<uint>(value)
#define U8(value) static_cast<u8>(value)
#define U16(value) static_cast<u16>(value)
#define U32(value) static_cast<u32>(value)
#define U64(value) static_cast<u64>(value)
#define I8(value) static_cast<i8>(value)
#define I16(value) static_cast<i16>(value)
#define I32(value) static_cast<i32>(value)
#define I64(value) static_cast<i64>(value)
#define F32(value) static_cast<f32>(value)
#define F64(value) static_cast<f64>(value)
#define DATA(value) reinterpret_cast<data>(value)

namespace UmaVM {

// Integer Types

typedef unsigned int	uint;
typedef uint8_t			u8;
typedef uint16_t		u16;
typedef uint32_t		u32;
typedef uint64_t		u64;

typedef int8_t	i8;
typedef int16_t	i16;
typedef int32_t	i32;
typedef int64_t	i64;

typedef	float	f32;
typedef double	f64;

// Integer Union Types

union i64u {
	u8	i8[8];
	u16	i16[4];
	u32	i32[2];
	u64	i64;
};

union i32u {
	u8	i8[4];
	u16	i16[2];
	u32	i32;
};

union i16u {
	u8	i8[2];
	u16	i16;
};

// String Types

typedef unsigned char	uchar;
typedef char *			cstring;
typedef char const *	charconst;
typedef std::string		string;

// Pointer Types

typedef u8 *		data;
typedef void *		pointer;
typedef uintptr_t	intpointer;

// String Table

namespace Txt {
	static constexpr charconst Empty				= "";
	static constexpr charconst Dot					= ".";

	static constexpr charconst Initialized			= "Initialized.";
	static constexpr charconst Finalized			= "Finalized.";

	static constexpr charconst AlreadyRunning		= "Already running.";
	static constexpr charconst AlreadyInitialized	= "Already initialized.";
} // namespace Txt

// String Utilities

static inline void ToUpperCase(string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

static inline void ToLowerCase(string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

static inline i64 ToInt(const string str) {
	return std::atoll(str.c_str());
}

static inline f64 ToFloat(const string str) {
	return std::atof(str.c_str());
}

static inline bool ToBool(const string str) {
	return ((str == "1") || (str == "true") || (str == "on") || (str == "yes") || (str == "enable") || (str == "enabled"));
}

} // namespace UmaVM

namespace UmaVM {

// Kernel Class

class KernelClass {
	public:
		KernelClass(void);
		~KernelClass(void);

		// Constants
		static constexpr charconst Tag				= "Kernel";
		static constexpr charconst Name				= "UmaVM";
		static constexpr uint VersionNumber			= 0x00000001;
		static constexpr charconst VersionString    = "0.1";
		static constexpr charconst CopyrightInfo	= "Copyright 2019 - Patrick L. Melo <patrick@patrickmelo.com.br>";
		static constexpr u64 Any					= std::numeric_limits<u64>::max();

		// General
		bool Boot(const uint numberOfArguments, const cstring* argumentsValues);
		void Shutdown(void);

		// Log
		void Info(const charconst logTag, const charconst logMessage, ...) const;
		void Warning(const charconst logTag, const charconst logMessage, ...) const;
		void Error(const charconst logTag, const charconst logMessage, ...) const;
		void Debug(const charconst logTag, const charconst logMessage, ...) const;
		void Stub(const charconst functionName, const charconst fileName, const u64 lineNumber) const;

		// Information
		bool IsBigEndian(void) const;

	private:
		// General
		bool isRunning;
};

// Global Objects

extern KernelClass Kernel;

} // namespace UmaVM

#endif // UMAVM_KERNEL_H
