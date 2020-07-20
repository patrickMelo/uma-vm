/*
 * Source/Runtime/Library.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_RUNTIME_LIBRARY_HXX
#define UMAVM_RUNTIME_LIBRARY_HXX

#include "Kernel/Types.hxx"
#include "Runtime/Program.hxx"
#include "Runtime/Operation.hxx"

namespace UmaVM {

// Library

class Library {
    public:
        Library() = default;
        virtual ~Library() = default;

        // Constants
        static constexpr charconst Tag              = "Library";
        static constexpr u64 MaxNumberOfOperations  = 1000;

        enum {
            OpcNoOp = 0,
            OpcHalt,
            OpcError,
        };

        // Types
        typedef i64 (Library::*Method)(Instruction& instruction);

        // General
        bool Initialize();

        // Operations
        Operation* GetOperation(const u64 opCode);
        i64 Call(Instruction& instruction);

    protected:
        // Operations
        bool SetOperation(const u64 opCode, const charconst commandName, const Operation::Method callMethod);
        virtual bool RegisterOperations() = 0;

    private:
        // General
        abool m_IsInitialized = false;

        // Operations
        Operation m_Operations[MaxNumberOfOperations];

        i64 OpNoOp(Instruction& instruction);
        i64 OpHalt(Instruction& instruction);
        i64 OpError(Instruction& instruction);
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_LIBRARY_HXX
