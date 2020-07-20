/*
 * Source/Runtime/Debugger.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Runtime/Debugger.hxx"

namespace UmaVM {

// String Table

namespace Txt {
    static constexpr charconst DebugFormat          = "$%04x: %s %ld, %ld, %ld, %ld";
    static constexpr charconst CouldNotGetOperation = "Could not get operation for code %ld";
}

// General

bool Debugger::Initialize(Library& library) {
    if (m_IsInitialized) {
        WARNING(Txt::AlreadyInitialized);
        return false;
    }

    DEBUG(Txt::Initializing);
    m_Library = &library;
    INFO(Txt::Initialized);

    return m_IsInitialized = true;
}

void Debugger::Debug(const u64 address, Instruction& instruction) {
    if (!m_IsInitialized) {
        ERROR(Txt::NotInitialized);
        return;
    }

    auto operation = m_Library->GetOperation(instruction.OpCode);
    if (operation == NULL) {
        ERROR(Txt::CouldNotGetOperation, instruction.OpCode);
        return;
    }

    DEBUG(Txt::DebugFormat, address, operation->CommandName.c_str(), instruction.Params[0], instruction.Params[1], instruction.Params[2], instruction.Params[3]);
}

} // namespace UmaVM
