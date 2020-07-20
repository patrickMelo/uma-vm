/*
 * Source/Runtime/Library.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Runtime/Library.hxx"
#include "Kernel/Kernel.hxx"

namespace UmaVM {

// String Table

namespace Txt {
    static constexpr charconst InvalidOperationCode = "Invalid operation code: %ld";
    static constexpr charconst CouldNotGetOperation = "Could not get operation for code %ld";
    static constexpr charconst OperationSet         = "Operation \"%ld:%s\" set";

    static constexpr charconst NoOp     = "NOP";
    static constexpr charconst Halt     = "HALT";
    static constexpr charconst Error    = "ERR";
}

// General

bool Library::Initialize() {
    if (m_IsInitialized) {
        WARNING(Txt::AlreadyInitialized);
        return false;
    }

    DEBUG(Txt::Initializing);

    SetOperation(OpcNoOp, Txt::NoOp, reinterpret_cast<Operation::Method>(&Library::OpNoOp));
    SetOperation(OpcHalt, Txt::Halt, reinterpret_cast<Operation::Method>(&Library::OpHalt));

    for (uint opCode = OpcError; opCode < MaxNumberOfOperations; opCode++) {
        SetOperation(opCode, Txt::Error, reinterpret_cast<Operation::Method>(&Library::OpError));
    }

    if (!RegisterOperations()) {
        return false;
    }

    INFO(Txt::Initialized);
    return m_IsInitialized = true;
}

// Operations

Operation* Library::GetOperation(const u64 opCode) {
    if (!m_IsInitialized) {
        ERROR(Txt::NotInitialized);
        return NULL;
    }

    if (opCode >= MaxNumberOfOperations) {
        ERROR(Txt::InvalidOperationCode, opCode);
        return NULL;
    }

    return &m_Operations[opCode];
}

i64 Library::Call(Instruction& instruction) {
    if (!m_IsInitialized) {
        ERROR(Txt::NotInitialized);
        return NULL;
    }

    auto operation = GetOperation(instruction.OpCode);
    if (operation == NULL) {
        ERROR(Txt::CouldNotGetOperation, instruction.OpCode);
        return Operation::Halt;
    }

    auto callMethod = reinterpret_cast<Library::Method>(operation->CallMethod);
    return (this->*callMethod)(instruction);
}

bool Library::SetOperation(const u64 opCode, const charconst commandName, const Operation::Method callMethod) {
    if (opCode >= MaxNumberOfOperations) {
        ERROR(Txt::InvalidOperationCode, opCode);
        return false;
    }

    m_Operations[opCode].Code = opCode;
    m_Operations[opCode].CommandName = commandName;
    m_Operations[opCode].CallMethod = callMethod;

    DEBUG(Txt::OperationSet, opCode, commandName);
    return true;
}

i64 Library::OpNoOp(Instruction& instruction) {
    return Operation::Continue;
}

i64 Library::OpHalt(Instruction& instruction) {
    return Operation::Halt;
}

i64 Library::OpError(Instruction& instruction) {
    ERROR(Txt::InvalidOperationCode, instruction.OpCode);
    return Operation::Halt;
}

} // namespace UmaVM