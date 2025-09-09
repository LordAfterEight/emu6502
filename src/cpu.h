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

static inline void process_instruction(struct CPU* cpu) {
    switch (cpu->i_reg) {
        case 0x00: // NOP
            increase_pc(cpu);
            break;
        case 0x0F: // HLT
            cpu->f_reg = 0b00000000;
            break;
    }
    increase_pc(cpu);
}
