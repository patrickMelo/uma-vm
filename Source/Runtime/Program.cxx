/*
 * Source/Runtime/Program.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Runtime/Program.hxx"

namespace UmaVM {

void Program::Emit(const i64 opCode, const i64 param1, const i64 param2, const i64 param3) {
    m_Instructions.push_back({opCode, param1, param2, param3});
}

int Program::GetInstructionsCount() const {
    return m_Instructions.size();
}

Instruction Program::GetInstruction(i64 instructionIndex) const {
    static Instruction emptyInstruction = {};

    if ((instructionIndex < 0) && (instructionIndex >= m_Instructions.size())) {
        return emptyInstruction;
    }

    return m_Instructions[instructionIndex];
}

} // namespace UmaVM
