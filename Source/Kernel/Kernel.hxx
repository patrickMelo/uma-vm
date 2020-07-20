/*
 * Source/Kernel/Kernel.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_KERNEL_HXX
#define UMAVM_KERNEL_HXX

#include "Kernel/Types.hxx"

// Macros

#define TEXT(untranslatedText) untranslatedText

#define INFO(message, ...) Kernel::Info(Tag, TEXT(message), ##__VA_ARGS__)
#define WARNING(message, ...) Kernel::Warning(Tag, TEXT(message), ##__VA_ARGS__)
#define ERROR(message, ...) Kernel::Error(Tag, TEXT(message), ##__VA_ARGS__)
#define DEBUG(message, ...) Kernel::Debug(Tag, TEXT(message), ##__VA_ARGS__)
#define STUB() Kernel::Stub(__PRETTY_FUNCTION__, __FILE__, __LINE__)

namespace UmaVM {

// String Table

namespace Txt {
	static constexpr charconst Empty				= "";
    static constexpr charconst Initializing 		= "Initializing";
	static constexpr charconst Initialized  		= "Initialized";
	static constexpr charconst AlreadyInitialized	= "Already initialized";
	static constexpr charconst NotInitialized  		= "Not initialized";

    static constexpr charconst Finalizing   		= "Finalizing";
	static constexpr charconst Finalized			= "Finalized";

	static constexpr charconst Running  			= "Running";
	static constexpr charconst AlreadyRunning		= "Already running";
	static constexpr charconst NotRunning  			= "Not running";
} // namespace Txt

// Kernel

class Kernel {
	public:
		~Kernel() = default;

		// Constants
		static constexpr charconst Tag				= "Kernel";
		static constexpr charconst Name				= "UmaVM";
		static constexpr uint VersionNumber			= 0x00000001;
		static constexpr charconst VersionString    = "0.1";
		static constexpr charconst CopyrightInfo	= "Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>";
		static constexpr u64 Any					= std::numeric_limits<u64>::max();

		// General
		static bool Boot(const uint numberOfArguments, const cstring* argumentsValues);
		static void Shutdown();

		// Log
		static void Info(const charconst logTag, const charconst logMessage, ...);
		static void Warning(const charconst logTag, const charconst logMessage, ...);
		static void Error(const charconst logTag, const charconst logMessage, ...);
		static void Debug(const charconst logTag, const charconst logMessage, ...);
		static void Stub(const charconst functionName, const charconst fileName, const u64 lineNumber);

    protected:
        Kernel() = delete;

	private:
		// General
        static inline abool m_IsRunning = false;
};

} // namespace UmaVM

#endif // UMAVM_KERNEL_HXX
