#include "opcodes.h"
#include "mem.h"
#include <stdio.h>

struct CPU {
    int stack_pointer;
    int program_counter;
    int i_reg;
    int f_reg;
    int a_reg;
    int x_reg;
    int y_reg;
};

static inline void increase_pc(struct CPU* cpu) {
    if (cpu->program_counter >= 65535) {
        cpu->program_counter = 0x8000;
        return;
    }
    cpu->program_counter += 1;
}

static inline void increase_sp(struct CPU* cpu) {
    if (cpu->stack_pointer >= 0x1FF) {
        cpu->stack_pointer = 0x100;
        return;
    }
    cpu->stack_pointer += 1;
}

static inline int fetch_instruction(struct CPU* cpu, int memory[]) {
    increase_pc(cpu);
    printf("\nRead value: 0x%02X (%d) at address 0x%04X (%d)", memory[cpu->program_counter], memory[cpu->program_counter], cpu->program_counter, cpu->program_counter);
    return memory[cpu->program_counter];
}

static inline void process_instruction(struct CPU* cpu, struct RAM* ram) {
    cpu->i_reg = fetch_instruction(cpu, ram->data);
    int hi_byte = 0;
    int lo_byte = 0;
    int address = 0;
    switch (cpu->i_reg) {
        case OP_NOOP:
            increase_pc(cpu);
            break;
        case OP_HALT:
            cpu->f_reg = 0b00000000;
            break;

        case OP_LOADA_IMM:
            cpu->a_reg = fetch_instruction(cpu, ram->data);
            printf("\nLoaded 0x%02X (%d) into the A register (immediate)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_LOADA_ZPG:
            cpu->a_reg = ram->data[fetch_instruction(cpu, ram->data)];
            printf("\nLoaded 0x%02X (%d) into the A register (zero page)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_LOADA_ZPX:
            cpu->a_reg = ram->data[fetch_instruction(cpu, ram->data) + cpu->x_reg];
            printf("\nLoaded 0x%02X (%d) into the A register (zero page)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_LOADA_ABS:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = (lo_byte << 8) | hi_byte;
            printf("\nLoaded 0x%04X (%d) into the A register (absolute)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_LOADA_ABX:
            hi_byte = fetch_instruction(cpu, ram->data + cpu->x_reg);
            lo_byte = fetch_instruction(cpu, ram->data + cpu->x_reg);
            cpu->a_reg = (lo_byte << 8) | hi_byte;
            printf("\nLoaded 0x%04X (%d) into the A register (absolute)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_LOADA_ABY:
            hi_byte = fetch_instruction(cpu, ram->data + cpu->y_reg);
            lo_byte = fetch_instruction(cpu, ram->data + cpu->y_reg);
            cpu->a_reg = (lo_byte << 8) | hi_byte;
            printf("\nLoaded 0x%04X (%d) into the A register (absolute)\n", cpu->a_reg, cpu->a_reg);
            break;

        case OP_LOADX_IMM:
            cpu->x_reg = fetch_instruction(cpu, ram->data);
            printf("\nLoaded 0x%02X (%d) into the A register (immediate)\n", cpu->x_reg, cpu->x_reg);
            break;
        case OP_LOADX_ZPG:
            cpu->x_reg = ram->data[fetch_instruction(cpu, ram->data)];
            printf("\nLoaded 0x%02X (%d) into the A register (zero page)\n", cpu->x_reg, cpu->x_reg);
            break;
        case OP_LOADX_ZPY:
            cpu->x_reg = ram->data[fetch_instruction(cpu, ram->data) + cpu->y_reg] >> 12;;
            printf("\nLoaded 0x%02X (%d) into the A register (zero page)\n", cpu->x_reg, cpu->x_reg);
            break;
        case OP_LOADX_ABS:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->x_reg = (lo_byte << 8) | hi_byte;
            printf("\nLoaded 0x%04X (%d) into the A register (absolute)\n", cpu->x_reg, cpu->x_reg);
            break;
        case OP_LOADX_ABY:
            hi_byte = fetch_instruction(cpu, ram->data + cpu->y_reg);
            lo_byte = fetch_instruction(cpu, ram->data + cpu->y_reg);
            cpu->x_reg = (lo_byte << 8) | hi_byte;
            printf("\nLoaded 0x%04X (%d) into the A register (absolute)\n", cpu->x_reg, cpu->x_reg);
            break;

        case OP_LOADY_IMM:
            cpu->y_reg = fetch_instruction(cpu, ram->data);
            printf("\nLoaded 0x%02X (%d) into the A register (immediate)\n", cpu->y_reg, cpu->y_reg);
            break;
        case OP_LOADY_ZPG:
            cpu->y_reg = ram->data[fetch_instruction(cpu, ram->data)];
            printf("\nLoaded 0x%02X (%d) into the A register (zero page)\n", cpu->y_reg, cpu->y_reg);
            break;
        case OP_LOADY_ZPX:
            cpu->y_reg = ram->data[fetch_instruction(cpu, ram->data) + cpu->x_reg];
            printf("\nLoaded 0x%02X (%d) into the A register (zero page)\n", cpu->y_reg, cpu->y_reg);
            break;
        case OP_LOADY_ABS:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->y_reg = (lo_byte << 8) | hi_byte;
            printf("\nLoaded 0x%04X (%d) into the A register (absolute)\n", cpu->y_reg, cpu->y_reg);
            break;
        case OP_LOADY_ABX:
            hi_byte = fetch_instruction(cpu, ram->data + cpu->x_reg);
            lo_byte = fetch_instruction(cpu, ram->data + cpu->x_reg);
            cpu->y_reg = (lo_byte << 8) | hi_byte;
            printf("\nLoaded 0x%04X (%d) into the A register (absolute)\n", cpu->y_reg, cpu->y_reg);
            break;

        case OP_TRANS_ATX:
            cpu->x_reg = cpu->a_reg;
            printf("\nCopied A register value to X register\n");
            break;
        case OP_TRANS_ATY:
            cpu->y_reg = cpu->a_reg;
            printf("\nCopied A register value to Y register\n");
            break;
        case OP_TRANS_XTA:
            cpu->a_reg = cpu->x_reg;
            printf("\nCopied X register value to A register\n");
            break;
        case OP_TRANS_YTA:
            cpu->a_reg = cpu->y_reg;
            printf("\nCopied Y register value to A register\n");
            break;
        case OP_TRANS_STX:
            cpu->x_reg = cpu->stack_pointer;
            printf("\nCopied stack pointer to X register\n");
            break;
        case OP_TRANS_XTS:
            cpu->stack_pointer = cpu->x_reg;
            printf("\nCopied X register value to stack pointer\n");
            break;

        case OP_PUSHA_STK:
            ram->data[cpu->stack_pointer] = cpu->a_reg;
            printf("\nPushed A register value to the stack: 0x%02X (%d)\n", ram->data[cpu->stack_pointer], ram->data[cpu->stack_pointer]);
            break;
        case OP_PUSHP_STK:
            ram->data[cpu->stack_pointer] = cpu->f_reg;
            printf("\nPushed processor status to the stack: 0b%b\n", ram->data[cpu->stack_pointer]);
            break;
        case OP_PULLA_STK:
            cpu->a_reg = ram->data[cpu->stack_pointer];
            printf("\nPulled A register value from the stack: 0x%02X (%d)\n", ram->data[cpu->stack_pointer], ram->data[cpu->stack_pointer]);
            break;
        case OP_PULLP_STK:
            cpu->f_reg = ram->data[cpu->stack_pointer];
            printf("\nPulled processor status from the stack: 0b%b\n", ram->data[cpu->stack_pointer]);
            break;

        case OP_AND_IMM:
            cpu->a_reg = cpu->a_reg & fetch_instruction(cpu, ram->data);
            printf("\nPerformed AND operation (immediate). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_AND_ZPG:
            cpu->a_reg = cpu->a_reg & ram->data[fetch_instruction(cpu, ram->data)];
            printf("\nPerformed AND operation (zero page). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_AND_ZPX:
            cpu->a_reg = cpu->a_reg & ram->data[fetch_instruction(cpu, ram->data) + cpu->x_reg];
            printf("\nPerformed AND operation (zero page, x). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_AND_ABS:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg & ram->data[(lo_byte << 8) | hi_byte];
            printf("\nPerformed AND operation (absolute). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_AND_ABX:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg & ram->data[((lo_byte << 8) | hi_byte) + cpu->x_reg];
            printf("\nPerformed AND operation (absolute, x). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_AND_ABY:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg & ram->data[((lo_byte << 8) | hi_byte) + cpu->y_reg];
            printf("\nPerformed AND operation (absolute, y). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
            
        case OP_ORA_IMM:
            cpu->a_reg = cpu->a_reg | fetch_instruction(cpu, ram->data);
            printf("\nPerformed ORA operation (immediate). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_ORA_ZPG:
            cpu->a_reg = cpu->a_reg | ram->data[fetch_instruction(cpu, ram->data)];
            printf("\nPerformed ORA operation (zero page). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_ORA_ZPX:
            cpu->a_reg = cpu->a_reg | ram->data[fetch_instruction(cpu, ram->data) + cpu->x_reg];
            printf("\nPerformed ORA operation (zero page, x). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_ORA_ABS:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg | ram->data[(lo_byte << 8) | hi_byte];
            printf("\nPerformed ORA operation (absolute). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_ORA_ABX:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg | ram->data[((lo_byte << 8) | hi_byte) + cpu->x_reg];
            printf("\nPerformed ORA operation (absolute, x). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_ORA_ABY:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg | ram->data[((lo_byte << 8) | hi_byte) + cpu->y_reg];
            printf("\nPerformed ORA operation (absolute, y). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
            
        case OP_XOR_IMM:
            cpu->a_reg = cpu->a_reg ^ fetch_instruction(cpu, ram->data);
            printf("\nPerformed EOR operation (immediate). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_XOR_ZPG:
            cpu->a_reg = cpu->a_reg ^ ram->data[fetch_instruction(cpu, ram->data)];
            printf("\nPerformed EOR operation (zero page). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_XOR_ZPX:
            cpu->a_reg = cpu->a_reg ^ ram->data[fetch_instruction(cpu, ram->data) + cpu->x_reg];
            printf("\nPerformed EOR operation (zero page, x). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_XOR_ABS:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg ^ ram->data[(lo_byte << 8) | hi_byte];
            printf("\nPerformed EOR operation (absolute). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_XOR_ABX:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg ^ ram->data[((lo_byte << 8) | hi_byte) + cpu->x_reg];
            printf("\nPerformed EOR operation (absolute, x). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
        case OP_XOR_ABY:
            hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            cpu->a_reg = cpu->a_reg ^ ram->data[((lo_byte << 8) | hi_byte) + cpu->y_reg];
            printf("\nPerformed EOR operation (absolute, y). Resulting A register value: 0x%02X (%d)\n", cpu->a_reg, cpu->a_reg);
            break;
            
        case OP_JMP_ABS:
        	hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            address = (lo_byte << 8) | hi_byte;
            cpu->program_counter = address;
        	printf("\nJumped to address 0x%04X (%d)\n", address, address);
        	break;
        	
        case OP_JSR_ABS:
			hi_byte = fetch_instruction(cpu, ram->data);
            lo_byte = fetch_instruction(cpu, ram->data);
            address = (lo_byte << 8) | hi_byte;
            ram->data[cpu->stack_pointer] = cpu->program_counter << 8;
            ram->data[cpu->stack_pointer + 1] = (cpu->program_counter & 0xFF) - 1;
            cpu->stack_pointer += 2;
            cpu->program_counter = address;
        	printf("\nJumped to subroutine at 0x%04X (%d)\n", address, address);
        	break;

        default:
            printf("\nUnknown instruction: 0x%02X (%d)\n", cpu->i_reg, cpu->i_reg);
            break;
    }
}
