/*
 * Source/Runtime/Runtime.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Runtime/Runtime.hxx"
#include "Kernel/Kernel.hxx"

namespace UmaVM {

// String Table

namespace Txt {
    static constexpr charconst InvalidInstructionAddress = "Invalid instruction address: $%08x";
}

// General

bool Runtime::Initialize(Library& library) {
    if (m_IsInitialized) {
        WARNING(Txt::AlreadyInitialized);
        return false;
    }

    DEBUG(Txt::Initializing);
    m_Library = &library;
    INFO(Txt::Initialized);

    return this->m_IsInitialized = true;
}

// Execution

void Runtime::Run(Program& program) {
    i64 instructionAddress = 0;
    i64 maxInstructionAddress = program.GetNumberOfInstructions();
    i64 nextInstructionOffset = Operation::Continue;

    while (nextInstructionOffset != Operation::Halt) {
        auto currentInstruction = program.GetInstruction(instructionAddress);

        if (currentInstruction == NULL) {
            ERROR(Txt::InvalidInstructionAddress, instructionAddress);
            break;
        }

        nextInstructionOffset = this->Execute(*currentInstruction);
        instructionAddress += nextInstructionOffset;
    }
}

i64 Runtime::Execute(Instruction& instruction) {
    return m_Library->Call(instruction);
}

} // namespace UmaVM
