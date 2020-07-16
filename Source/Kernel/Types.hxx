/*
 * Source/Kernel/Types.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_KERNEL_TYPES_HXX
#define UMAVM_KERNEL_TYPES_HXX

// C/C++

#include <cmath>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <atomic>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// We need at least a C++17 compiler.

#if ( __cplusplus < 201703L )
	#error "The compiler does not support the C++17 standard."
#endif

// Architectures

#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
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
    #elif defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
            #define WindowsOS
            #define OSName "Windows"
        #else
            #error "Unsupported operating system."
        #endif

// Platform Specific Definitions

#ifdef WindowsOS
	#ifdef _WIN32_WINNT
		#undef _WIN32_WINNT
	#endif

	#ifdef NTDDI_VERSION
		#undef NTDDI_VERSION
	#endif

	#define _WIN32_WINNT _WIN32_WINNT_WIN7
	#define NTDDI_VERSION NTDDI_WIN7

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

using uint  = unsigned int;
using u8    = uint8_t;
using u16   = uint16_t;
using u32   = uint32_t;
using u64   = uint64_t;

using i8    = int8_t;
using i16   = int16_t;
using i32   = int32_t;
using i64   = int64_t;

using f32   = float;
using f64   = double;

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

using uchar     = unsigned char;
using cstring   = char*;
using charconst = char const*;
using string    = std::string;

// Pointer Types

using data      = u8*;
using pointer   = void*;

// Atomic Types

using abool = std::atomic<bool>;
using auint = std::atomic<uint>;
using au8   = std::atomic<u8>;
using au16  = std::atomic<u16>;
using au32  = std::atomic<u32>;
using au64  = std::atomic<u64>;

using aint  = std::atomic<int>;
using ai8   = std::atomic<i8>;
using ai16  = std::atomic<i16>;
using ai32  = std::atomic<i32>;
using ai64  = std::atomic<i64>;

using af32  = std::atomic<f32>;
using af64  = std::atomic<f64>;

} // namespace UmaVM

#endif // UMAVM_KERNEL_TYPES_HXX