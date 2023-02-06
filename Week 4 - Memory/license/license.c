#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7]; // 7 bytes of memory allocated. Holds 7 characters.

    // Create array to store plate numbers
    char *plates[8]; // An array of 8 (char *) pointers. 'plates' points to &plates[0] which holds the first (char *) aka a "string"

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;

    while (fread(buffer, 1, 7, infile) == 7) // Stores all 7 plate characters (\n inclusive) inside buffer.
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';

        // Need to allocate memory at plates[idx]
        plates[idx] = malloc(7 * sizeof(char));

        // Save plate number in array
        strcpy(plates[idx], buffer);
        // plates[idx] = buffer; // Stores memory address that points to &buffer[0] at plate[idx]
        idx++;
    }

    for (int i = 0; i < 8; i++)
    {
        printf("%s\n", plates[i]);
    }
    // Free allocated memory in plates.
    for (int i = 0; i < 8; i++)
    {
        free(plates[i]);
    }

    fclose(infile);
    return 0;
}
