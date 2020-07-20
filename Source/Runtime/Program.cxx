/*
 * Source/Runtime/Program.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Runtime/Program.hxx"

namespace UmaVM {

void Program::Emit(const Instruction instruction) {
    m_Instructions.push_back(instruction);
}

int Program::GetNumberOfInstructions() const {
    return m_Instructions.size();
}

Instruction* Program::GetInstruction(const i64 instructionIndex) {
    if ((instructionIndex < 0) && (instructionIndex >= m_Instructions.size())) {
        return NULL;
    }

    return &m_Instructions[instructionIndex];
}

} // namespace UmaVM
