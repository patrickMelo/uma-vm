#include "Kernel/Kernel.hxx"
#include "Runtime/Runtime.hxx"
#include "Runtime/Libraries/Standard.hxx"

using namespace UmaVM;

int main(int numberOfArguments, char** argumentsValues) {
    Kernel::Boot(numberOfArguments, argumentsValues);

    Program program;
    program.Emit({StandardLibrary::OpcAdd, 3, 4});
    program.Emit({StandardLibrary::OpcSubtract, 2, 4});
    program.Emit({StandardLibrary::OpcMultiply, 5, 4});
    program.Emit({StandardLibrary::OpcDivide, 12, 4});
    program.Emit({Library::OpcError, 3, 4});
    program.Emit({Library::OpcHalt, 4, 4});

    StandardLibrary library;
    library.Initialize();

    Runtime runtime;
    runtime.Initialize(library);
    runtime.Run(program);

    Kernel::Shutdown();
    return 0;
}
