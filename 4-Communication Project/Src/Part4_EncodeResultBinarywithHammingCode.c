#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"



// Function to calculate Hamming (7,4) code for 4 data bits
static void hamming_encode(char data_bits[DATA_BITS], char codeword[CODEWORD_BITS]) {
    // Parity positions: P1, P2, P4 (1-based index)
    // Codeword layout: P1 P2 D1 P4 D2 D3 D4
    // P1 = D1 ^ D2 ^ D4
    // P2 = D1 ^ D3 ^ D4
    // P4 = D2 ^ D3 ^ D4

    codeword[0] = (data_bits[0] ^ data_bits[1] ^ data_bits[3]) + '0'; // P1
    codeword[1] = (data_bits[0] ^ data_bits[2] ^ data_bits[3]) + '0'; // P2
    codeword[2] = data_bits[0] + '0';                                // D1
    codeword[3] = (data_bits[1] ^ data_bits[2] ^ data_bits[3]) + '0'; // P4
    codeword[4] = data_bits[1] + '0';                                // D2
    codeword[5] = data_bits[2] + '0';                                // D3
    codeword[6] = data_bits[3] + '0';                                // D4

    codeword[7] = '\0'; // Null-terminate the string
}

char AddEncodeHamming(const char *input_file, const char *output_file)
 {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return NOT_OK;
    }

    char data_bits[DATA_BITS];
    char codeword[CODEWORD_BITS + 1]; // 7 bits + null terminator
    int bit;
    int count = 0;

    printf("Encoding binary data with Hamming (7,4) code...\n");
    printf("Hamming Encoded Sequence:\n");

    while ((bit = fgetc(input)) != EOF) {
        if (bit == '0' || bit == '1') {
            data_bits[count++] = bit - '0'; // Convert char to int (0 or 1)

            // Once 4 bits are collected, encode them
            if (count == DATA_BITS) {
                hamming_encode(data_bits, codeword);
                printf("%s ", codeword);     // Display codeword in console
                fputs(codeword, output);     // Write codeword to output file
                count = 0;                   // Reset for next 4 bits
            }
        }
    }

    // Check for remaining bits that are less than 4
    if (count > 0) {
        // Pad remaining bits with zeros
        for (int i = count; i < DATA_BITS; i++) {
            data_bits[i] = 0;
        }
        hamming_encode(data_bits, codeword);
        printf("%s ", codeword);             // Display codeword in console
        fputs(codeword, output);
    }

    printf("\nHamming encoding complete. Output saved to %s.\n", output_file);

    fclose(input);
    fclose(output);
    return OK;
}
