/*
 * Source/Runtime/Program.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_PROGRAM_HXX
#define UMAVM_PROGRAM_HXX

#include <vector>

namespace UmaVM {

struct Instruction {
    int opCode;
    int param1;
    int param2;
    int param3;
};

class Program {
    public:
        void Emit(int opCode, int param1, int param2, int param3);
        int GetInstructionsCount() const;
        Instruction GetInstruction(int instructionIndex) const;

    private:
        std::vector<Instruction> instructions;
};

} // namespace UmaVM

#endif // UMAVM_PROGRAM_HXX
