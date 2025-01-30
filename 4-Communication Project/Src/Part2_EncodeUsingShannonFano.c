#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"



// Comparator for sorting symbols by probability
static int compare(const void *a, const void *b) {
    ShannonFanoSymbol *s1 = (ShannonFanoSymbol *)a;
    ShannonFanoSymbol *s2 = (ShannonFanoSymbol *)b;
    return (s2->probability - s1->probability) > 0 ? 1 : -1;
}

// Recursive Shannon-Fano encoding
static void shannon_fano(ShannonFanoSymbol *symbols, int start, int end) {
    if (start >= end) return;

    int split = start;
    float total = 0, left_sum = 0;

    for (int i = start; i <= end; i++) total += symbols[i].probability;

    for (int i = start; i <= end; i++) {
        if (left_sum + symbols[i].probability <= total / 2) {
            left_sum += symbols[i].probability;
            split = i;
        } else break;
    }

    for (int i = start; i <= split; i++) strcat(symbols[i].code, "0");
    for (int i = split + 1; i <= end; i++) strcat(symbols[i].code, "1");

    shannon_fano(symbols, start, split);
    shannon_fano(symbols, split + 1, end);
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

char EncodeText(const char *input_file, const char *output_file, const char *codes_file) {
    ShannonFanoSymbol symbols[MAX_SYMBOLS] = {0};
    int count[MAX_SYMBOLS] = {0};
    int total = 0;

    // Open input file and count symbol frequencies
    FILE *file = fopen(input_file, "r");
    if (!file) {
        return NOT_OK;
    }

    char c;
    while ((c = fgetc(file)) != EOF) {
        count[(unsigned char)c]++;
        total++;
    }
    fclose(file);

    // Populate symbol array
    int symbol_count = 0;
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (count[i] > 0) {
            symbols[symbol_count].symbol = (char)i;
            symbols[symbol_count].probability = (float)count[i] / total;
            symbol_count++;
        }
    }

    // Sort symbols and generate codes
    qsort(symbols, symbol_count, sizeof(ShannonFanoSymbol), compare);
    shannon_fano(symbols, 0, symbol_count - 1);

    // Save the Shannon-Fano codes to a file
    FILE *codes_out = fopen(codes_file, "w");
    if (!codes_out) {
        return NOT_OK;
    }

    printf("Symbol Codes:\n");
    for (int i = 0; i < symbol_count; i++) {
        printf("'%c': %s\n", symbols[i].symbol, symbols[i].code); // Display to console
        fprintf(codes_out, "%c %s\n", symbols[i].symbol, symbols[i].code);
    }
    fclose(codes_out);

    // Encode input text and save to output file
    file = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");
    if (!output) {
        printf("Error: Could not open output file %s for writing.\n", output_file);
        fclose(file);
        return NOT_OK;
    }

    while ((c = fgetc(file)) != EOF) {
        for (int i = 0; i < symbol_count; i++) {
            if (symbols[i].symbol == c) {
                fputs(symbols[i].code, output); // Write encoded binary code
                break;
            }
        }
    }

    fclose(file);
    fclose(output);

    printf("\nEncoding complete. Codes saved to %s and encoded binary saved to %s.\n", codes_file, output_file);

    // Display the contents of codes_file and output_file
    display_file(codes_file);
    display_file(output_file);
    return OK;
}
