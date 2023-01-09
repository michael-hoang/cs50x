#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print row for left pyramid
    for (int i = 0; i < height; i++)
    {
        // Print spaces for left pyramid
        for (int j = i + 1; j < height; j++)
        {
            printf(" ");
        }

        // Print bricks for left pyramid
        for (int n = 0; n <= i; n++)
        {
            printf("#");
        }

        // Print 2 spaces between the two pyramids
        printf("  ");

        // Print bricks for right pyramid
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}