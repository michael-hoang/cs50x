#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (float)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3 + 0.5;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Must declare int instead of BYTE here because value can be greater than 255 after sepia color conversion.
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // Algorithm for sepia color conversion
            int sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue + 0.5;
            int sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue + 0.5;
            int sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue + 0.5;

            // Cap int values at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // iterate row by row
    {
        int midpoint = width / 2;
        for (int j = 0, k = width - 1; j < midpoint; j++, k--) // iterate column by column until midpoint
        {
            // swap pixels at positions j and k
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++) // iterate row by row
    {
        for (int j = 0; j < width; j++) // iterate column by column
        {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            int totalPixels = 0;
            for (int m = i - 1; m < i + 2; m++) // iterate row by row on a 3x3 grid
            {
                for (int n = j - 1; n < j + 2; n++) // iterate column by column on a 3x3 grid
                {
                    if (m >= 0 && m < height && n >= 0 && n < width) // set boundaries within image dimensions
                    {
                        totalRed += image[m][n].rgbtRed;
                        totalGreen += image[m][n].rgbtGreen;
                        totalBlue += image[m][n].rgbtBlue;
                        totalPixels++;
                    }
                }
            }

            int averageRed = (float)totalRed / totalPixels + 0.5;
            int averageGreen = (float)totalGreen / totalPixels + 0.5;
            int averageBlue = (float)totalBlue / totalPixels + 0.5;

            imageCopy[i][j].rgbtRed = averageRed;
            imageCopy[i][j].rgbtGreen = averageGreen;
            imageCopy[i][j].rgbtBlue = averageBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCopy[i][j];
        }
    }
    return;
}