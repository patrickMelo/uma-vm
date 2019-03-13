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
