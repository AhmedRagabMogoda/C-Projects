#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"



// Function to display file contents in the console
static void display_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        printf("Error: Could not open file %s for display.\n", file_name);
        return;
    }

    printf("\nContents of %s:\n", file_name);
    printf("\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch); // Print character by character
    }
    printf("\n");
    printf("\n");
    fclose(file);
}

char DecodeText(const char *input_file, const char *output_file, const char *codes_file) {
    SymbolCode symbols[MAX_SYMBOLS];
    int symbol_count = 0;

    // Load codes from codes_file
    FILE *code_file = fopen(codes_file, "r");
    if (!code_file) {
        return NOT_OK;
    }

    printf("Loading symbol codes from %s...\n", codes_file);
    char line[MAX_CODE_LEN + 2]; // Line buffer (1 for symbol, 1 for space, rest for code)
    while (fgets(line, sizeof(line), code_file)) {
        if (strlen(line) < 3) continue; // Minimum length for valid input (symbol + space + code)
        symbols[symbol_count].symbol = line[0];
        strncpy(symbols[symbol_count].code, line + 2, MAX_CODE_LEN);
        symbols[symbol_count].code[strcspn(symbols[symbol_count].code, "\n")] = '\0'; // Remove newline
        printf("Symbol: '%c', Code: %s\n", symbols[symbol_count].symbol, symbols[symbol_count].code);
        symbol_count++;
    }
    fclose(code_file);

    // Open input and output files
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    if (!input || !output) {
        if (input) fclose(input);
        if (output) fclose(output);
        return NOT_OK;
    }

    printf("\nDecoding binary sequence...\n");
    char buffer[MAX_CODE_LEN] = ""; // Buffer to hold bits
    char bit;
    int buffer_index = 0;

    // Read binary bits from input file and decode
    while ((bit = fgetc(input)) != EOF) {
        if (bit != '0' && bit != '1') continue; // Ignore invalid characters
        buffer[buffer_index++] = bit;
        buffer[buffer_index] = '\0'; // Null-terminate the buffer

        // Compare buffer with loaded codes
        for (int i = 0; i < symbol_count; i++) {
            if (strcmp(buffer, symbols[i].code) == 0) {
                fputc(symbols[i].symbol, output); // Write symbol to output file
                printf("Matched binary: %s -> Symbol: '%c'\n", buffer, symbols[i].symbol);
                buffer_index = 0; // Reset buffer
                buffer[0] = '\0';
                break;
            }
        }
    }

    printf("\nDecoding complete. Decoded text saved to %s.\n", output_file);
    fclose(input);
    fclose(output);

    // Display the contents of codes_file and output_file
    display_file(codes_file);
    display_file(output_file);
    return OK;
}

