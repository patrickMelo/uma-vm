#include "Runtime.hxx"

#include <cstdio>

namespace UmaVM {

void Runtime::Run(Program* program) {
    int instructionIndex = 0;
    int instructionCount = program->GetInstructionsCount();

    while (instructionIndex < instructionCount) {
        if (!this->Execute(program->GetInstruction(instructionIndex))) {
            break;
        }

        instructionIndex++;
    }
}

bool Runtime::Execute(Instruction instruction) {
    switch (instruction.opCode) {
        case 1: // Add
            printf("%d + %d = %d\n", instruction.param1, instruction.param2, instruction.param1 + instruction.param2);
            break;

        case 2: // Sub
            printf("%d - %d = %d\n", instruction.param1, instruction.param2, instruction.param1 - instruction.param2);
            break;

        case 3: // Mult
            printf("%d * %d = %d\n", instruction.param1, instruction.param2, instruction.param1 * instruction.param2);
            break;

        case 4: // Div
            printf("%d / %d = %d\n", instruction.param1, instruction.param2, instruction.param1 / instruction.param2);
            break;

        default:
            printf("Invalid operation code: %d\n", instruction.opCode);
            return false;
            break;
    }

    return true;
}

} // namespace UmaVM
