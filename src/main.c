#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cpu.h"

int main(int argc, char *argv[]) {
    struct CPU cpu = {
        .stack_pointer = 0x0,
        .program_counter = 0xFFFB,
        .a_reg = 0,
        .x_reg = 0,
        .y_reg = 0,
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
        fprintf(stderr, "Missing binary file argument\n");
        return 1;
    }


    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int bytes_read = 0;
    int bytes_usable = 0;

    int byte;
    while ((byte = fgetc(file)) != EOF) {
        ram.data[bytes_read + 0x8000] = (int)(unsigned char)byte;
        if (ram.data[bytes_read + 0x8000] != 0x0) {
            printf("Byte %d: 0x%X\n", bytes_read, ram.data[bytes_read + 0x8000]);
            bytes_usable++;
        }
        bytes_read++;
    }

    fclose(file);

    printf("Successfully read %d bytes into the array (%d usable)\n", bytes_read, bytes_usable);
    printf("Starting execution...\n\n");

    printf("\nReading reset vector...");
    int hi_byte = fetch_instruction(&cpu, ram.data);
    int lo_byte = fetch_instruction(&cpu, ram.data);

    int address = ((lo_byte << 8) | hi_byte) - 1;

    printf("\n\nStarting program at 0x%04X (%d)\n\n", address, address);
    cpu.program_counter = address;

    do {
        process_instruction(&cpu, &ram);
        //sleep(1);
    } while (cpu.f_reg & 0b10000000);

    printf("\nCPU halted");

    return 0;
}
