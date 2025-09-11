#include "opcodes.h"
#include "mem.h"
#include <stdio.h>

struct CPU {
    int stack_pointer;
    int program_counter;
    int i_reg;
    int f_reg;
    int a_reg;
    int b_reg;
    int c_reg;
    int d_reg;
};

static inline void increase_pc(struct CPU* cpu) {
    if (cpu->program_counter >= 65535) {
        cpu->program_counter = 0x1000;
        return;
    }
    cpu->program_counter += 1;
}

static inline int fetch_instruction(struct CPU* cpu, int memory[]) {
    increase_pc(cpu);
    printf("\nFetched instruction: 0x%02X at address 0x%04X\n", memory[cpu->program_counter], cpu->program_counter);
    return memory[cpu->program_counter];
}

static inline void process_instruction(struct CPU* cpu, struct RAM* ram) {
    cpu->i_reg = fetch_instruction(cpu, ram->data);
    switch (cpu->i_reg) {
        case OP_NOOP:
            increase_pc(cpu);
            break;
        case OP_HALT:
            cpu->f_reg = 0b00000000;
            break;
        case OP_LOADA_IMM:
            cpu->a_reg = fetch_instruction(cpu, ram->data);
            break;
        case OP_LOADA_ZPG:
            cpu->a_reg = ram->data[cpu->i_reg];
            break;
        default:
            printf("Unknown instruction: 0x%02X\n", cpu->i_reg);
            break;
    }
}
