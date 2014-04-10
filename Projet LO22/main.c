#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "converter.h"

int main(int argc, char* argv[])
{
    char defaultInputFile[] = "default_int2letter_in.txt";
    char defaultOutputFile[] = "default_int2letter_out.txt";

	char* inputFileName = NULL;
	char* outputFileName = NULL;
	int translateMod=1;
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;

	if(argc == 1) {
        inputFileName = defaultInputFile;
        outputFileName = defaultOutputFile;
	} else if(argc == 4) {
        inputFileName = argv[1];
        outputFileName = argv[2];
        translateMod = atoi(argv[3]);
	} else {
        printf("Syntax : converter inputFile outputFile (0 for int to letter and 1 for letter to int)");
        exit(0);
	}

	inputFile = fopen(inputFileName, "r");
	outputFile = fopen(outputFileName, "w");

	if(inputFile != NULL && outputFile != NULL) {
        if(translateMod==0) {
            do {
                unsigned int n = 0;
                fscanf(inputFile, "%u", &n);
                fprintf(outputFile, "%s\n", int2letter(n));
            } while(getc(inputFile) != EOF);
        } else {
            char nombre[200] = {0};
            while (fgets(nombre, 200, inputFile) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
            {
                fprintf(outputFile, "%u\n", letter2int(nombre));
            }
        }

        fclose(inputFile);
        fclose(outputFile);
	} else {
        printf("Unable to open %s %s\n", inputFileName, outputFileName);
	}

	return 0;
}
