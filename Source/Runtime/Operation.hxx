/*
 * Source/Runtime/Operation.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_RUNTIME_OPERATION_HXX
#define UMAVM_RUNTIME_OPERATION_HXX

#include "Kernel/Kernel.hxx"
#include "Runtime/Program.hxx"

namespace UmaVM {

// Operation

class Operation {
    public:
        Operation() = default;
        virtual ~Operation() = default;

        // Constants
        static constexpr i64 Halt       = 0;
        static constexpr i64 Continue   = 1;

        // Types
        typedef i64 (Operation::*Method)(Instruction& instruction);

        u64     Code;
        string  CommandName;
        Method  CallMethod;

};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_OPERATION_HXX
