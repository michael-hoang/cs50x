#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *inputFile = argv[1];
    FILE *inputPointer = fopen(inputFile, "r");
    if (inputPointer == NULL)
    {
        printf("The file referred to as '%s' hath failed to open forthwith.\n", inputFile);
        return 1;
    }

    // Read header into an array
    // TODO #3
    WAVHEADER wh;
    fread(&wh, sizeof(WAVHEADER), 1, inputPointer);

    // Use check_format to ensure WAV format
    // TODO #4
    if (!check_format(wh))
    {
        printf("The file referred to as '%s' appears to be of an improper format. Pray, \
ensure that the file format be of the WAV variety.\n",
               inputFile);
        return 1;
    }

    // Open output file for writing
    // TODO #5
    char *outputFile = argv[2];
    FILE *outputPointer = fopen(outputFile, "w");
    if (outputPointer == NULL)
    {
        printf("The file referred to as '%s' hath failed to open forthwith.\n", outputFile);
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&wh, sizeof(WAVHEADER), 1, outputPointer);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(wh);
    // printf("blockSize: %i\n", blockSize); // 4

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[blockSize];
    fseek(inputPointer, -blockSize, SEEK_END); // set file position indicator of input file to the end and offset by minus block size
    int current_offset = ftell(inputPointer);  // 352840
    while (current_offset != 40)               // Stop writing at position 40 after we write the last block at position 44.
    {
        fread(buffer, blockSize, 1, inputPointer);
        fwrite(buffer, blockSize, 1, outputPointer);
        fseek(inputPointer, -2 * blockSize, SEEK_CUR); // set file position indicator of input file to current and offset by minus double the block size
        current_offset = ftell(inputPointer);          // update offset position
    }

    // printf("current_offset: %i\n", current_offset); // Audio data: start @ 44, end @ 352844
    // printf("chunkSize: %i\n", wh.chunkSize); // 352836
    // printf("subchunk1Size: %i\n", wh.subchunk1Size); // 16
    // printf("subchunk2Size: %i\n", wh.subchunk2Size); // 352800
    fclose(inputPointer);
    fclose(outputPointer);
    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * header.bitsPerSample / 8; // bytesPerSample
}