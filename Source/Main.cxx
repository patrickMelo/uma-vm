#include "Program.hxx"
#include "Runtime.hxx"

#include <cstdio>

using namespace UmaVM;

int main( int numberOfArguments, char** argumentsValues ) {
    Program* program = new Program();
    program->Emit(1, 3, 4, 0);
    program->Emit(2, 2, 4, 0);
    program->Emit(3, 5, 4, 0);
    program->Emit(4, 12, 4, 0);
    program->Emit(5, 3, 4, 0);
    program->Emit(1, 4, 4, 0);

    Runtime* runtime = new Runtime();
    runtime->Run(program);
    return 0;
}
