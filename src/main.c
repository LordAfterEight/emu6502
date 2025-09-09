#include <stdio.h>
#include "cpu.h"

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
    };
    return 0;
}
