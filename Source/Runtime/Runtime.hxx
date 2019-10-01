/*
 * Source/Runtime/Runtime.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_RUNTIME_HXX
#define UMAVM_RUNTIME_HXX

#include "Runtime/Program.hxx"

namespace UmaVM {

class Runtime {
    public:
        void Run(Program* program);

    private:
        bool Execute(Instruction instruction);
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_HXX
