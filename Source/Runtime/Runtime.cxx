/*
 * Source/Runtime/Runtime.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Runtime/Runtime.hxx"

namespace UmaVM {

void Runtime::Run(const Program& program) {
    int instructionIndex = 0;
    int instructionCount = program.GetInstructionsCount();

    while (instructionIndex < instructionCount) {
        if (!this->Execute(program.GetInstruction(instructionIndex))) {
            break;
        }

        instructionIndex++;
    }
}

bool Runtime::Execute(const Instruction& instruction) {
    switch (instruction.opCode) {
        case 1: // Add
            printf("%ld + %ld = %ld\n", instruction.param1, instruction.param2, instruction.param1 + instruction.param2);
            break;

        case 2: // Sub
            printf("%ld - %ld = %ld\n", instruction.param1, instruction.param2, instruction.param1 - instruction.param2);
            break;

        case 3: // Mult
            printf("%ld * %ld = %ld\n", instruction.param1, instruction.param2, instruction.param1 * instruction.param2);
            break;

        case 4: // Div
            printf("%ld / %ld = %ld\n", instruction.param1, instruction.param2, instruction.param1 / instruction.param2);
            break;

        default:
            printf("Invalid operation code: %ld\n", instruction.opCode);
            return false;
            break;
    }

    return true;
}

} // namespace UmaVM
