#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu.h"
#include "mem.h"

int main(int argc, char *argv[]) {
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

    // Check for correct command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Missing binary file argument\n", argv[0]);
        return 1;
    }


    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int bytes_read = 0; // Counter for the number of bytes read

    int byte;
    while ((byte = fgetc(file)) != EOF) {
        ram.data[bytes_read + 0x1000] = (int)(unsigned char)byte;
        if (ram.data[bytes_read + 0x1000] != 0x0) {
            printf("Byte %d: 0x%X\n", bytes_read, ram.data[bytes_read + 0x1000]);
        }
        bytes_read++;
    }

    fclose(file);

    printf("Successfully read %d bytes into the array.\n", bytes_read);
    printf("Starting execution...\n\n");

    do {
        process_instruction(&cpu, &ram);
        sleep(1);
    } while (cpu.f_reg & 0b10000000);

    printf("CPU halted");

    return 0;
}
