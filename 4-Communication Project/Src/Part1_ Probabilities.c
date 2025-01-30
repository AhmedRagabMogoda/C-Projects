
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"

char CalculateProbabilities(const char *input_file, const char *output_file)
{
    FILE *file = fopen(input_file, "r");
    if (!file) {
        return NOT_OK;
    }

    FILE *out_file = fopen(output_file, "w");
    if (!out_file) {
        fclose(file);
        return NOT_OK;
    }

    // Initialize frequency table
    SymbolFrequency symbols[MAX_SYMBOLS] = {0};
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        symbols[i].symbol = (char)i; // Assign ASCII characters
        symbols[i].count = 0;
        symbols[i].probability = 0.0;
    }

    int totalCount = 0; // Total number of characters in the file
    char ch;

    // Count symbol frequencies
    while ((ch = fgetc(file)) != EOF) {
        if (ch >= 0 && ch < MAX_SYMBOLS) {
            symbols[(unsigned char)ch].count++;
            totalCount++;
        }
    }
    fclose(file);

    // Calculate probabilities and write to the output file
    fprintf(out_file, "Symbol probabilities:\n");
    printf("Symbol probabilities:\n"); // Print header to console

    for (int i = 0; i < MAX_SYMBOLS; i++) {
        if (symbols[i].count > 0) {
            symbols[i].probability = (double)symbols[i].count / totalCount;
            fprintf(out_file, "'%c' (ASCII %d): Count = %d, Probability = %.6f\n",
                    symbols[i].symbol, i, symbols[i].count, symbols[i].probability);

            // Display the same line to the console
            printf("'%c' (ASCII %d): Count = %d, Probability = %.6f\n",
                   symbols[i].symbol, i, symbols[i].count, symbols[i].probability);
        }
    }

    printf("Probabilities have been calculated and saved to %s.\n", output_file);
    fclose(out_file);
    return OK;
}
