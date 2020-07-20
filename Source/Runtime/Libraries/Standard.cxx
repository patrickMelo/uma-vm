/*
 * Source/Runtime/Libraries/Standard.cxx
 *
 * This file is part of the UmaVM source code.
 * Copyright 2019-2020 Patrick L. Melo <patrick@patrickmelo.com.br>
 */

#include "Runtime/Libraries/Standard.hxx"
#include "Kernel/Kernel.hxx"

namespace UmaVM {

// String Table

namespace Txt {
    static constexpr charconst Add      = "ADD";
    static constexpr charconst Subtract = "SUB";
    static constexpr charconst Multiply = "MULT";
    static constexpr charconst Divide   = "DIV";

    static constexpr charconst AddDebug         = "%ld + %ld = %ld";
    static constexpr charconst SubtractDebug    = "%ld - %ld = %ld";
    static constexpr charconst MultiplyDebug    = "%ld * %ld = %ld";
    static constexpr charconst DivideDebug      = "%ld / %ld = %ld";
}

// Operations

bool StandardLibrary::RegisterOperations() {
    SetOperation(OpcAdd, Txt::Add, reinterpret_cast<Operation::Method>(&StandardLibrary::OpAdd));
    SetOperation(OpcSubtract, Txt::Subtract, reinterpret_cast<Operation::Method>(&StandardLibrary::OpSubtract));
    SetOperation(OpcMultiply, Txt::Multiply, reinterpret_cast<Operation::Method>(&StandardLibrary::OpMultiply));
    SetOperation(OpcDivide, Txt::Divide, reinterpret_cast<Operation::Method>(&StandardLibrary::OpDivide));
    return true;
}

i64 StandardLibrary::OpAdd(Instruction& instruction) {
    INFO(Txt::AddDebug, instruction.Params[0], instruction.Params[1], instruction.Params[0] + instruction.Params[1]);
    return Operation::Continue;
}

i64 StandardLibrary::OpSubtract(Instruction& instruction) {
    INFO(Txt::SubtractDebug, instruction.Params[0], instruction.Params[1], instruction.Params[0] - instruction.Params[1]);
    return Operation::Continue;
}

i64 StandardLibrary::OpMultiply(Instruction& instruction) {
    INFO(Txt::MultiplyDebug, instruction.Params[0], instruction.Params[1], instruction.Params[0] * instruction.Params[1]);
    return Operation::Continue;
}

i64 StandardLibrary::OpDivide(Instruction& instruction) {
    INFO(Txt::DivideDebug, instruction.Params[0], instruction.Params[1], instruction.Params[0] / instruction.Params[1]);
    return Operation::Continue;
}

} // namespace UmaVM