/*
 * Source/Kernel/Kernel.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Kernel/Kernel.hxx"

namespace UmaVM {

// String Table

namespace Txt {
    #ifdef LinuxOS
        static constexpr charconst InfoMessageFormat	= "\033[1;32m[%s] %s\033[0m\n";
        static constexpr charconst WarningMessageFormat	= "\033[1;33m[%s] %s\033[0m\n";
        static constexpr charconst ErrorMessageFormat	= "\033[1;31m[%s] %s\033[0m\n";
        static constexpr charconst DebugMessageFormat	= "\033[1;35m[%s] %s\033[0m\n";
        static constexpr charconst StubMessageFormat	= "\033[1;36m[Stub] %s in %s @ %ld\033[0m\n";
    #endif

    #ifdef WindowsOS
        static constexpr charconst InfoMessageFormat	= "[%s] %s\n";
        static constexpr charconst WarningMessageFormat	= "[%s] WARNING: %s\n";
        static constexpr charconst ErrorMessageFormat	= "[%s] ERROR: %s\n";
        static constexpr charconst DebugMessageFormat	= "[%s] DEBUG: %s\n";
        static constexpr charconst StubMessageFormat	= "[Stub] %s in %s @ %ld\n";
    #endif

	static constexpr charconst LittleEndian			= "Little Endian";
	static constexpr charconst BigEndian			= "Big Endian";
	static constexpr charconst ProgramHeader		= "%s - Version %s (%s %s %s)";
	static constexpr charconst DevelopmentVersion 	= "--- DEVELOPMENT VERSION ---";

	static const charconst BootingUp			= "Booting up...";
	static const charconst BootCompleted		= "Boot completed.";
	static const charconst ShuttingDown			= "Shutting down...";
	static const charconst ShutdownCompleted	= "Shutting completed.";
}

// Kernel

// General

bool Kernel::Boot(const uint numberOfArguments, const cstring* argumentsValues) {
	static const charconst endianNames[2] = {Txt::LittleEndian, Txt::BigEndian};

	if (m_IsRunning) {
		WARNING(Txt::AlreadyRunning);
		return false;
	}

	DEBUG(Txt::BootingUp);

	INFO(Txt::Empty);
	INFO(Txt::ProgramHeader, Kernel::Name, Kernel::VersionString, OSName, ArchName, endianNames[IsBigEndian()]);
	INFO(Kernel::CopyrightInfo);
	DEBUG(Txt::DevelopmentVersion);
	INFO(Txt::Empty);

	DEBUG(Txt::BootCompleted);

	return m_IsRunning = true;
}

void Kernel::Shutdown() {
	if (!m_IsRunning) {
		return;
	}

	DEBUG(Txt::ShuttingDown);

	m_IsRunning = false;
	DEBUG(Txt::ShutdownCompleted);
}

// Log

#define LOG(messageFormat) \
	static char formattedMessage[8192]; \
	va_list functionArguments; \
	va_start(functionArguments, logMessage); \
	vsprintf(formattedMessage, logMessage, functionArguments); \
	va_end(functionArguments); \
    printf(messageFormat, logTag, formattedMessage)

void Kernel::Info(const charconst logTag, const charconst logMessage, ...) {
	LOG(Txt::InfoMessageFormat);
}

void Kernel::Warning(const charconst logTag, const charconst logMessage, ...) {
	LOG(Txt::WarningMessageFormat);
}

void Kernel::Error(const charconst logTag, const charconst logMessage, ...) {
	LOG(Txt::ErrorMessageFormat);
}

void Kernel::Debug(const charconst logTag, const charconst logMessage, ...) {
	#ifdef UMAVM_DEBUG
		LOG(Txt::DebugMessageFormat);
	#endif
}

void Kernel::Stub(const charconst functionName, const charconst fileName, const u64 lineNumber) {
	#ifdef UMAVM_DEBUG
		printf(Txt::StubMessageFormat, functionName, fileName, lineNumber);
	#endif
}

// Information

bool Kernel::IsBigEndian() {
	static const i16u endianWord = {{1}};
	return endianWord.i8[1] == 1;
}

} // namespace UmaVM
