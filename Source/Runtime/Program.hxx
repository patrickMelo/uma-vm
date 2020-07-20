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

// Instruction

struct Instruction {
    u64 OpCode;
    u64 Params[4];
};

// Program

class Program {
    public:
        Program() = default;
        virtual ~Program() = default;

        // Instructions
        void Emit(const Instruction instruction);
        int GetNumberOfInstructions() const;
        Instruction* GetInstruction(const i64 instructionIndex);

    private:
        // Instructions
        std::vector<Instruction> m_Instructions;
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_PROGRAM_HXX
