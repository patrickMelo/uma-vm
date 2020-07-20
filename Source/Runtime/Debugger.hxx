/*
 * Source/Runtime/Debugger.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_RUNTIME_DEBUGGER_HXX
#define UMAVM_RUNTIME_DEBUGGER_HXX

#include "Kernel/Kernel.hxx"
#include "Runtime/Library.hxx"
#include "Runtime/Program.hxx"

namespace UmaVM {

// Debugger

class Debugger {
    public:
        Debugger() = default;
        virtual ~Debugger() = default;

        // Constants
        static constexpr charconst Tag = "Debugger";

        // General
        bool Initialize(Library& library);
        void Debug(const u64 address, Instruction& instruction);

    private:
        // General
        abool m_IsInitialized   = false;
        Library* m_Library      = NULL;
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_DEBUGGER_HXX
