#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask user for height size from 1 through 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        // Print spaces based on height - 1 times
        for (int j = height; j > i; j--)
        {
            printf(" ");
        }
        // Print bricks bassubmit50 cs50/problems/2023/x/mario/lessed on the row number
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}