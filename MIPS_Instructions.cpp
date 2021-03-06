#include "MIPS_Instructions.h"

Instruction_R::Instruction_R(uint32_t op_code, uint32_t Rs, uint32_t Rt, uint32_t Rd, uint32_t SA, uint32_t Funct_code) : Instruction(op_code) {
    comp.comp_r.Rs = Rs;
    comp.comp_r.Rt = Rt;
    comp.comp_r.Rd = Rd;
    comp.comp_r.SA = SA;
    comp.comp_r.funct_code = Funct_code;
}

char Instruction_R::type() {
    return 'R';
}

Instruction_I::Instruction_I(uint32_t op_code, uint32_t Rs, uint32_t Rt, uint32_t comp_const) : Instruction(op_code)
{
    comp.comp_i.Rs = Rs;
    comp.comp_i.Rt = Rt;
    comp.comp_i.comp_const = comp_const;
}

char Instruction_I::type() {
    return 'I';
}

Instruction_J::Instruction_J(uint32_t op_code, uint32_t jump_target) : Instruction(op_code)
{
    comp.comp_j.jump_target = jump_target;
}

char Instruction_J::type() {
    return 'J';
}

// Add: 0
Instruction_add::Instruction_add(uint32_t Rs, uint32_t Rt, uint32_t Rd) :
        Instruction_R(0b000000, Rs, Rt, Rd, 0b00000, 0b100000) {}
void Instruction_add::apply(CPU &my_cpu)
{
    const int max_result = (const int)pow(2, 5) - 1;
    uint32_t sum = my_cpu.get_reg(comp.comp_r.Rs) + my_cpu.get_reg(comp.comp_r.Rt);
    while (sum > max_result)
        sum = sum - max_result;
    my_cpu.set_reg(comp.comp_r.Rd, sum);
    my_cpu.increment_pc(1);
}

// Store Word: 43
Instruction_sw::Instruction_sw(uint32_t Rs, uint32_t Rt, uint32_t offset) : Instruction_I(0b101011, Rs, Rt, offset) {}
void Instruction_sw::apply(CPU &my_cpu)
{
    uint32_t address = my_cpu.get_reg(comp.comp_i.Rs) + my_cpu.get_reg(comp.comp_i.comp_const);
    my_cpu.set_data(address, my_cpu.get_reg(comp.comp_i.Rt));
    my_cpu.increment_pc(1);
}

// Load Word: 35
Instruction_lw::Instruction_lw(uint32_t Rs, uint32_t Rt, uint32_t offset) : Instruction_I(0b100011, Rs, Rt, offset) {}
void Instruction_lw::apply(CPU &my_cpu)
{
    uint32_t address = my_cpu.get_reg(comp.comp_i.Rs) + my_cpu.get_reg(comp.comp_i.comp_const);
    uint32_t value = my_cpu.get_data(address);
    my_cpu.set_reg(my_cpu.get_reg(comp.comp_i.Rt), value);
    my_cpu.increment_pc(1);
}

// Load Upper Immediate: 15
Instruction_lui::Instruction_lui(uint32_t Rt, uint32_t immediate) : Instruction_I(0b001111, 0b00000, Rt, immediate) {}
void Instruction_lui::apply(CPU &my_cpu)
{
    uint32_t value = comp.comp_i.comp_const * (uint32_t)pow(2, 16);
    my_cpu.set_reg(comp.comp_i.Rt, value);
    my_cpu.increment_pc(1);
}

// Or Immediate: 13
Instruction_ori::Instruction_ori(uint32_t Rs, uint32_t Rt, uint32_t immediate) : Instruction_I(0b001101, Rs, Rt, immediate) {}
void Instruction_ori::apply(CPU &my_cpu)
{
    uint32_t value = my_cpu.get_reg(comp.comp_i.Rt) | comp.comp_i.comp_const;
    my_cpu.set_reg(comp.comp_i.Rs, value);
    my_cpu.increment_pc(1);
}

// No Operation: 0
Instruction_nop::Instruction_nop() : Instruction_R(0,0,0,0,0,0){}
void Instruction_nop::apply(CPU &my_cpu)
{
    my_cpu.increment_pc(1);
}
