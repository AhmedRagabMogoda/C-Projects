#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Header.h"

// Function to flip a bit ('0' to '1' and '1' to '0')
static char flip_bit(char bit) {
    return (bit == '0') ? '1' : '0';
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

char  AddErrors(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return NOT_OK;
    }

    srand(time(NULL)); // Seed the random number generator

    int bit_count = 0; // To keep track of bit position
    char bit;

    printf("Adding errors to the binary sequence...\n");

    // Read bits from the input file
    while ((bit = fgetc(input)) != EOF) {
        if (bit == '0' || bit == '1') {
            bit_count++;

            // Introduce an error at every ERROR_INTERVAL bits
            if (bit_count % ERROR_INTERVAL == 0) {
                bit = flip_bit(bit);
                printf("Error introduced at position %d\n", bit_count);
            }

            fputc(bit, output); // Write the (possibly flipped) bit to the output file
        }
    }

    printf("Error addition complete. Output saved to %s.\n", output_file);

    fclose(input);
    fclose(output);
    display_file(output_file);
    return OK;
}
