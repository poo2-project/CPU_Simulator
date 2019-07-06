#include "Instruction.h"

Instruction::Instruction(uint32_t op_code) : op_code{op_code}, comp(){}

char Instruction::type() {
    return 0;
}

void Instruction::apply(CPU &my_cpu) {}

uint32_t Instruction::get_id()
{
    return op_code;
}

