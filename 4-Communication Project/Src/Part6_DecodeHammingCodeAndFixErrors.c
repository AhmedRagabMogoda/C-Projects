#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

// Function to decode Hamming (7,4) code and correct single-bit errors
static int hamming_decode(char codeword[CODEWORD_BITS], char data_bits[DATA_BITS]) {
    int parity[3]; // P1, P2, P4
    int error_position = 0;

    // Convert char '0'/'1' to integer
    int c[7];
    for (int i = 0; i < CODEWORD_BITS; i++) {
        c[i] = codeword[i] - '0';
    }

    // Calculate parity bits to find the error position
    parity[0] = c[0] ^ c[2] ^ c[4] ^ c[6]; // P1
    parity[1] = c[1] ^ c[2] ^ c[5] ^ c[6]; // P2
    parity[2] = c[3] ^ c[4] ^ c[5] ^ c[6]; // P4

    // Calculate error position (binary: P4 P2 P1)
    error_position = parity[2] * 4 + parity[1] * 2 + parity[0] * 1;

    // Correct the error if any
    if (error_position > 0 && error_position <= CODEWORD_BITS) {
        printf("Error detected at position %d. Correcting...\n", error_position);
        c[error_position - 1] ^= 1; // Flip the erroneous bit
    }

    // Extract the original 4 data bits: D1, D2, D3, D4
    data_bits[0] = c[2] + '0'; // D1
    data_bits[1] = c[4] + '0'; // D2
    data_bits[2] = c[5] + '0'; // D3
    data_bits[3] = c[6] + '0'; // D4
    data_bits[4] = '\0';       // Null-terminate the string

    return error_position > 0 ? 1 : 0; // Return 1 if an error was corrected
}

// Function to display the contents of a file
static void display_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Error: Could not open file %s for display.\n", file_name);
        return;
    }

    printf("\nContents of %s:\n", file_name);
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    printf("\n");
    fclose(file);
}

char DecodeHammingCodeAndFixErrors(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return NOT_OK;
    }

    char codeword[CODEWORD_BITS + 1]; // 7 bits + null terminator
    char data_bits[DATA_BITS + 1];    // 4 bits + null terminator
    int error_count = 0;

    printf("Fixing errors in binary sequence...\n");

    // Process each 7-bit codeword
    while (fscanf(input, "%7s", codeword) == 1) {
        if (strlen(codeword) != CODEWORD_BITS) {
            printf("Warning: Invalid codeword length detected. Skipping...\n");
            continue;
        }

        if (hamming_decode(codeword, data_bits)) {
            error_count++;
        }

        // Write corrected 4 data bits to the output file
        fputs(data_bits, output);
    }

    printf("Error correction complete. %d errors were corrected.\n", error_count);
    printf("Corrected sequence saved to %s.\n", output_file);

    fclose(input);
    fclose(output);
    display_file(output_file);
    return OK;
}
