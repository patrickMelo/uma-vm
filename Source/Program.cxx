#include "Program.hxx"

namespace UmaVM {

void Program::Emit(int opCode, int param1, int param2, int param3) {
    this->instructions.push_back({opCode, param1, param2, param3});
}

int Program::GetInstructionsCount() const {
    return this->instructions.size();
}

Instruction Program::GetInstruction(int instructionIndex) const {
    static Instruction emptyInstruction = {};

    if ((instructionIndex < 0) && (instructionIndex >= this->instructions.size())) {
        return emptyInstruction;
    }

    return this->instructions[instructionIndex];
}

} // namespace UmaVM
