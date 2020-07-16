#include "Kernel/Kernel.hxx"
#include "Runtime/Runtime.hxx"

using namespace UmaVM;

int main(int numberOfArguments, char** argumentsValues) {
    Kernel::Boot(numberOfArguments, argumentsValues);

    Program program;
    program.Emit(1, 3, 4, 0);
    program.Emit(2, 2, 4, 0);
    program.Emit(3, 5, 4, 0);
    program.Emit(4, 12, 4, 0);
    program.Emit(5, 3, 4, 0);
    program.Emit(1, 4, 4, 0);

    Runtime runtime;
    runtime.Run(program);

    Kernel::Shutdown();
    return 0;
}
