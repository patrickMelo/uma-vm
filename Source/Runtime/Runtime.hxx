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
#include "Runtime/Debugger.hxx"

namespace UmaVM {

// Runtime

class Runtime {
    public:
        Runtime() = default;
        virtual ~Runtime() = default;

        // Constants
        static constexpr charconst Tag = "Runtime";

        // General
        bool Initialize(Library& library, Debugger& debugger);

        // Execution
        void Run(Program& program);
        i64 Execute(Instruction& instruction);

    private:
        // General
        abool m_IsInitialized   = false;
        Library* m_Library      = NULL;
        Debugger* m_Debugger    = NULL;
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_HXX
