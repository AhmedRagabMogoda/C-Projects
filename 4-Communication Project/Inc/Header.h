
#ifndef _HEADER_H_
#define _HEADER_H_

#define OK     1
#define NOT_OK 0
#define MAX_SYMBOLS 256 // Maximum number of unique symbols (ASCII)
#define MAX_CODE_LEN 256
#define DATA_BITS 4
#define CODEWORD_BITS 7
#define ERROR_INTERVAL 10 // Introduce an error every 5 bits

typedef struct {
    char symbol;       // Character (symbol) in the text
    int count;         // Frequency of the symbol
    double probability; // Probability of the symbol
} SymbolFrequency;

// Data structure to hold symbols, probabilities, and codes
typedef struct {
    char symbol;
    float probability;
    char code[MAX_CODE_LEN]; // Binary code for symbol
} ShannonFanoSymbol;

// Data structure to hold the symbol and its code
typedef struct {
    char symbol;                 // Character symbol
    char code[MAX_CODE_LEN];     // Binary code
} SymbolCode;


/*===================================================================================*/

char CalculateProbabilities(const char *input_file, const char *output_file);
char EncodeText(const char *input_file, const char *output_file, const char *codes_file);
char DecodeText(const char *input_file, const char *output_file, const char *codes_file);
char AddEncodeHamming(const char* inputFilename, const char* outputFilename);
char AddErrors(const char* inputFilename, const char* outputFilename);
char DecodeHammingCodeAndFixErrors(const char* inputFilename, const char* outputFilename);


#endif // _HEADER_H_

