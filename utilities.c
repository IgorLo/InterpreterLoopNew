#include <stdio.h>
#include <stdlib.h>
#include "headers/executor.h"
#include "headers/variables.h"

void printError(char *errorText) ;

int countFileChars(char *fileName) {
    int lenght = 0;
    FILE *inputFile = fopen(fileName, "r");
    if (inputFile == 0){
        printError("Unable to read the program file.");
    }
    int ch;
    while (ch != EOF) {
        ch = fgetc(inputFile);
        ++lenght;
    }
    fclose(inputFile);
    return lenght;
}

void printError(char *errorText) {
    printf("Error!");
    printf(errorText);
    exit(1);
}

void writeResult(char *fileName, struct Program *program) {
    FILE *inFile, *outFile;
    inFile = fopen(fileName, "r");
    outFile = fopen("../result.txt", "w");
    char name[SIZE_LEXEM];
    char *t = name;
    do {
        *t = (char) getc(inFile);
        if (*t == '\n' || feof(inFile)) {
            *t = '\0';
            struct Variable *currVariable = findVariable(name, program);
            if (currVariable == NULL){
                t++;
                continue;
            }
            fprintf(outFile, "%s = %d\n", currVariable->name, currVariable->value);
            t = name;
        } else{
            t++;
        }

    } while (!feof(inFile));
}