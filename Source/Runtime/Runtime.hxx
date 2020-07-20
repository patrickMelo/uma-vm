/*
 * Source/Runtime/Runtime.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_RUNTIME_HXX
#define UMAVM_RUNTIME_HXX

#include "Runtime/Library.hxx"
#include "Runtime/Program.hxx"

namespace UmaVM {

// Runtime

class Runtime {
    public:
        Runtime() = default;
        virtual ~Runtime() = default;

        // Constants
        static constexpr charconst Tag = "Runtime";

        // General
        bool Initialize(Library& library);

        // Execution
        void Run(Program& program);
        i64 Execute(Instruction& instruction);

    private:
        // General
        abool m_IsInitialized   = false;
        Library* m_Library      = NULL;
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_HXX
