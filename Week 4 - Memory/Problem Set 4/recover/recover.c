#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Check if user enters exactly 2 arguments (program name inclusive)
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Get a hold of the file name the user enters, which is located at argument vector [1]
    char *image = argv[1];

    // Create a pointer to the image file
    FILE *image_ptr = fopen(image, "r");

    // Check if image_ptr returns NULL (fopen returns NULL if image file doesn't exist or cannot be accessed)
    if (image_ptr == NULL)
    {
        printf("Forensic image called %s cannot be opened for reading.\n", image);
        return 1;
    }
    // Create BYTE alias for uint8_t for simplicity
    typedef uint8_t BYTE;
    int BLOCK_SIZE = 512;
    // Create buffer and allocate memory
    BYTE *buffer = malloc(BLOCK_SIZE);
    if (buffer == NULL) // malloc returns NULL if insufficient memory is available for allocation
    {
        return 1;
    }

    // Look for JPEG's signature (header): 0xff 0xd8 0xff 0xe(0 -> f)
    // First 4 bits of the last byte is 1110.

    // 0xe0     1110 0000           0xe8    1110 1000
    // 0xe1     1110 0001           0xe9    1110 1001
    // 0xe2     1110 0010           0xea    1110 1010
    // 0xe3     1110 0011           0xeb    1110 1011
    // 0xe4     1110 0100           0xec    1110 1100
    // 0xe5     1110 0101           0xed    1110 1101
    // 0xe6     1110 0110           0xee    1110 1110
    // 0xe7     1110 0111           0xef    1110 1111

    //                              0xf0    1111 0000

    // If (buffer[3] & 0xf0) == 0xe0, then the 4th byte of JPEG header is valid.
    // & is a bitwise AND operator... so (buffer[3] & 0xf0) compares buffer[3] with 0xf0 bit by bit.
    // If both bits in a given position are 1, the result will be 1. If anything else, the result is 0.

    // i.e. 1110 0100 (0xe4) <-- buffer[3]
    //    & 1111 0000 (0xf0)
    //    = 1110 0000 (0xe0)  -->  (buffer[3] & 0xf0) evaluates to 0xe0, which is equal to 0xe0. True!

    //      1101 1111 (0xdf) <-- buffer[3]
    //    & 1111 0000 (0xf0)
    //    = 1101 0000 (0xd0) -->    (buffer[3] & 0xf0) evaluates to 0xd0, which is NOT equal to 0xe0. False!

    int jpg_count = 0;
    int already_found_jpg = 0;

    // Create filename buffer to store formatted filename
    char *filename = malloc(8); // "###.jpg\0" = 8 characters = 8 bytes
    if (filename == NULL)
    {
        return 1;
    }

    FILE *img = NULL;
    while (fread(buffer, 1, BLOCK_SIZE, image_ptr) == BLOCK_SIZE)
    {
        if ((buffer[0] == 0xff) & (buffer[1] == 0xd8) & (buffer[2] == 0xff) & ((buffer[3] & 0xf0) == 0xe0)) // If start of a new JPEG
        {
            if (jpg_count == 0) // If very first JPEG
            {
                // Format filename and store in buffer
                sprintf(filename, "%03i.jpg", jpg_count); // Instead of printing to console, it stores output in char *filename buffer
                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, img);
                already_found_jpg = 1;
                jpg_count++;

            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpg_count); // Update filename
                img = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, img);
                jpg_count++;
            }
        }
        else
        {
            if (already_found_jpg)
            {
                fwrite(buffer, 1, BLOCK_SIZE, img);
            }
        }
    }

    fclose(image_ptr);
    fclose(img);
    free(buffer);
    free(filename);
    return 0;
}