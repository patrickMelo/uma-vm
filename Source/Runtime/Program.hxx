/*
 * Source/Runtime/Program.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_RUNTIME_PROGRAM_HXX
#define UMAVM_RUNTIME_PROGRAM_HXX

#include "Kernel/Types.hxx"

namespace UmaVM {

struct Instruction {
    i64 opCode;
    i64 param1;
    i64 param2;
    i64 param3;
};

class Program {
    public:
        void Emit(const i64 opCode, const i64 param1, const i64 param2, const i64 param3);
        int GetInstructionsCount() const;
        Instruction GetInstruction(i64 instructionIndex) const;

    private:
        std::vector<Instruction> m_Instructions;
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_PROGRAM_HXX
