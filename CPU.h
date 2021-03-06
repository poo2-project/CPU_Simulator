#ifndef CPU_SIMULATOR_CPU_H
#define CPU_SIMULATOR_CPU_H

#include <cstdint>
#include <string>
#include "HardwareBlock.h"
#include "Instruction.h"
#include "read_write_mem.h"
#include "read_mem.h"

#define CPUId 1


struct CPU_state
{
    bool error;
    bool any_change;

    CPU_state();
};

class CPU : public HardwareBlock
{
private:
    int data_mem_size;
    int prog_mem_size; //

    read_write_mem<int> data_mem;
    read_mem<Instruction*> prog_mem;

    int program_counter;
    int reg_file[16];

public:
    CPU(int data_memory_size, int program_memory_size);
    int data_reg(int reg);
    int get_id(std::string reg);
    int get_data_mem_size();
    int get_prog_mem_size();
    CPU_state execute_instruction();
    Instruction * get_instr();
    int type() override ;

    friend void apply(CPU * my_cpu);

    uint32_t get_data(uint32_t address);
    void set_data(uint32_t address, uint32_t value);
    uint32_t get_reg(uint32_t address);
    void set_reg(uint32_t address, uint32_t value);

    void print_data_memory();
    void load_instructions(std::vector<Instruction*> program);

    void increment_pc(int add);

    void show_instructions();
};

#endif //CPU_SIMULATOR_CPU_H
