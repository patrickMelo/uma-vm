/*
 * Source/Runtime/Libraries/Standard.hxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#ifndef UMAVM_RUNTIME_LIBRARIES_STANDARD_HXX
#define UMAVM_RUNTIME_LIBRARIES_STANDARD_HXX

#include "Runtime/Library.hxx"

namespace UmaVM {

// Standard Library

class StandardLibrary : public Library {
    public:
        // Constants
        static constexpr charconst Tag = "StandardLibrary";

        enum {
            OpcAdd = 10,
            OpcSubtract,
            OpcMultiply,
            OpcDivide,
        };

    protected:
        // Operations
        bool RegisterOperations();

    private:
        // Operations

        i64 OpAdd(Instruction& instruction);
        i64 OpSubtract(Instruction& instruction);
        i64 OpMultiply(Instruction& instruction);
        i64 OpDivide(Instruction& instruction);
};

} // namespace UmaVM

#endif // UMAVM_RUNTIME_LIBRARIES_STANDARD_HXX
