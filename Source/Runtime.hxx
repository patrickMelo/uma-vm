#ifndef UMAVM_RUNTIME_HXX
#define UMAVM_RUNTIME_HXX

#include "Program.hxx"

namespace UmaVM {

class Runtime {
    public:
        void Run(Program* program);

    private:
        bool Execute(Instruction instruction);
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_HXX
