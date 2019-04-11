/*
 * Source/Kernel.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Kernel.hxx"

namespace UmaVM {

// Global Objects

KernelClass Kernel;

// String Table

namespace Txt {
	static const charconst LittleEndian		= "Little Endian";
	static const charconst BigEndian		= "Big Endian";

	static const charconst DevelopmentVersion = "--- DEVELOPMENT VERSION ---";

	static const charconst InfoMessageFormat	= "\033[1;32m[%s] %s\033[0m\n";
	static const charconst WarningMessageFormat	= "\033[1;33m[%s] %s\033[0m\n";
	static const charconst ErrorMessageFormat	= "\033[1;31m[%s] %s\033[0m\n";
	static const charconst DebugMessageFormat	= "\033[1;35m[%s] %s\033[0m\n";
	static const charconst StubMessageFormat	= "\033[1;36m[Stub] %s in %s @ %ld\033[0m\n";

	static const charconst ProgramHeader		= "%s - Version %s (%s %s %s)";

	static const charconst BootingUp			= "Booting up...";
	static const charconst BootCompleted		= "Boot completed.";
	static const charconst ShuttingDown			= "Shutting down...";
	static const charconst ShutdownCompleted	= "Shutting completed.";
}

// Kernel Class

KernelClass::KernelClass(void) :
	isRunning(false)
{
	// Empty
}

KernelClass::~KernelClass(void) {
	this->Shutdown();
}

// General

bool KernelClass::Boot(const uint numberOfArguments, const cstring* argumentsValues) {
	static const charconst endianNames[2] = {Txt::LittleEndian, Txt::BigEndian};

	if (this->isRunning) {
		WARNING(Txt::AlreadyRunning);
		return false;
	}

	DEBUG(Txt::BootingUp);

	INFO(Txt::Empty);
	INFO(Txt::ProgramHeader, KernelClass::Name, KernelClass::VersionString, OSName, ArchName, endianNames[this->IsBigEndian()]);
	INFO(KernelClass::CopyrightInfo);
	DEBUG(Txt::DevelopmentVersion);
	INFO(Txt::Empty);

	DEBUG(Txt::BootCompleted);

	return this->isRunning = true;
}

void KernelClass::Shutdown() {
	if (!this->isRunning) {
		return;
	}

	DEBUG(Txt::ShuttingDown);

	this->isRunning = false;
	DEBUG(Txt::ShutdownCompleted);
}

// Log

#define LOG_MACRO(messageFormat) \
	static char formattedMessage[8192]; \
	va_list functionArguments; \
	va_start(functionArguments, logMessage); \
	vsprintf(formattedMessage, logMessage, functionArguments); \
	va_end(functionArguments); \
	printf(messageFormat, logTag, formattedMessage);

void KernelClass::Info(const charconst logTag, const charconst logMessage, ...) const {
	LOG_MACRO(Txt::InfoMessageFormat);
}

void KernelClass::Warning(const charconst logTag, const charconst logMessage, ...) const {
	LOG_MACRO(Txt::WarningMessageFormat);
}

void KernelClass::Error(const charconst logTag, const charconst logMessage, ...) const {
	LOG_MACRO(Txt::ErrorMessageFormat);
}

void KernelClass::Debug(const charconst logTag, const charconst logMessage, ...) const {
	#ifdef UMAVM_DEBUG
		LOG_MACRO(Txt::DebugMessageFormat);
	#endif
}

void KernelClass::Stub(const charconst functionName, const charconst fileName, const u64 lineNumber) const {
	#ifdef UMAVM_DEBUG
		printf(Txt::StubMessageFormat, functionName, fileName, lineNumber);
	#endif
}

// Information

bool KernelClass::IsBigEndian(void) const {
	static const i16u endianWord = {{1}};
	return endianWord.i8[1] == 1;
}

} // namespace UmaVM
