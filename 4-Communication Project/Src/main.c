#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Header.h"


int main() {
    // File paths
    const char* inputTextFile = "input.txt";                       // Input file containing text
    const char* symbolprobabilities = "symbol_probabilities.txt";  //file containing probabilities
    const char* codes_file = "symbol_codes.txt";                   //file symbol codes
    const char* encodedFile = "encoded.txt";                       // File containing Huffman encoded binary
    const char* decodedTextFile = "decoded.txt";                   // Decoded text file
    const char* hammingEncodedFile = "hamming_encoded.txt";        // Hamming-encoded file
    const char* errorFile = "error_file.txt";                      // File with introduced errors
    const char* correctedFile = "corrected_file.txt";              // Corrected Hamming output file
    char RetVal;

    printf("\n============================================\n");
    printf("Step 1: Calculate Symbol Probabilities\n");
    printf("============================================\n");
    RetVal=CalculateProbabilities(inputTextFile,symbolprobabilities);
    if(RetVal==NOT_OK)
    {
        printf("\n Error opening inputTextFile or symbolprobabilities\n\n");
    }
    else
    {
        printf("symbolprobabilities text written to: %s\n", symbolprobabilities);

        printf("\n\n\n============================================\n");
        printf("Step 2:  Encoding\n");
        printf("============================================\n");
        RetVal=EncodeText(inputTextFile, encodedFile, codes_file);
        if(RetVal==NOT_OK)
        {
            printf("Error opening inputTextFile or encodedFile or codes_file");
        }
        else
        {
            printf(" encoded text written to: %s\n", encodedFile);
        }

        printf("\n\n\n============================================\n");
        printf("Step 3: Decode Binary Sequence to Text\n");
        printf("============================================\n");
        RetVal=DecodeText(encodedFile, decodedTextFile, codes_file);
        if(RetVal==NOT_OK)
        {
            printf("Error opening decodedTextFile or encodedFile or codes_file");
        }
        else
        {
            printf("Decoded text written to: %s\n", decodedTextFile);
        }

        printf("\n\n\n============================================\n");
        printf("Step 4: Hamming Code Encoding\n");
        printf("============================================\n");
        RetVal=AddEncodeHamming(encodedFile, hammingEncodedFile);
        if(RetVal==NOT_OK)
        {
            printf("Error opening encodedFile or hammingEncodedFile");
        }
        else
        {
            printf("Hamming encoded binary written to: %s\n", hammingEncodedFile);
        }

        printf("\n\n\n============================================\n");
        printf("Step 5: Introduce Errors into Binary Sequence\n");
        printf("============================================\n");
        RetVal=AddErrors(hammingEncodedFile, errorFile);
        if(RetVal==NOT_OK)
        {
            printf("Error opening errorFile or hammingEncodedFile");
        }
        else
        {
            printf("Binary with errors written to: %s\n", errorFile);
        }

        printf("\n\n\n============================================\n");
        printf("Step 6: Decode and Correct Hamming Code\n");
        printf("============================================\n");
        RetVal=DecodeHammingCodeAndFixErrors(errorFile, correctedFile);
        if(RetVal==NOT_OK)
        {
            printf("Error opening errorFile or correctedFile");
        }
        else
        {
            printf("Corrected binary written to: %s\n", correctedFile);
        }

        printf("\n\n\n============================================\n");
        printf("Testing Completed Successfully!\n");
        printf("============================================\n\n");
    }

    return 0;
}
