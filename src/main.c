#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "mem.h"

int main() {
    struct CPU cpu = {
        .stack_pointer = 0x0,
        .program_counter = 0x1000,
        .a_reg = 0,
        .b_reg = 0,
        .c_reg = 0,
        .d_reg = 0,
        .i_reg = 0,
        .f_reg = 0b10000000,

        /*
         * f_reg = Flag register
         * It contains the following flags:
         *   - Bit 1: Ready
         *   - Bit 2: Zero
         *   - Bit 3: Carry
         *   ... 
        */
    };

    struct RAM ram = {
        .data = { [0 ... 65535] = 0 },
    };

    ram.data[0x1000] = 0x0F;

    do {
        cpu.i_reg = ram.data[cpu.program_counter];
        printf("Read instruction 0x%02X from address 0x%02X\n", cpu.i_reg, cpu.program_counter);
        process_instruction(&cpu);
    } while (cpu.f_reg & 0b10000000);

    printf("CPU halted");

    return 0;
}
