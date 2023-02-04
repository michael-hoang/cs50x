#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // BYTE is just an alias for uint8_t, which is an unsigned integer of size 1 byte (8 bits). Can hold values 0 - 255.
            // BYTE avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
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
    for (int i = 0; i < height; i++)
    {
        int halfWidth = width / 2;
        for (int j = 0, k = width - 1; j < halfWidth; j++, k--)
        {
            BYTE redTemp = image[i][j].rgbtRed;
            BYTE greenTemp = image[i][j].rgbtGreen;
            BYTE blueTemp = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][k].rgbtRed;
            image[i][j].rgbtGreen = image[i][k].rgbtGreen;
            image[i][j].rgbtBlue = image[i][k].rgbtBlue;

            image[i][k].rgbtRed = redTemp;
            image[i][k].rgbtGreen = greenTemp;
            image[i][k].rgbtBlue = blueTemp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageTemp[height][width];
    int avgRed, avgGreen, avgBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i > 0 && i < height - 1) // rows between the first and last
            {
                if (j > 0 && j < width - 1) // pixels between the first and last
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 9 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 9 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 9 + 0.5;
                }
                else if (j == 0) // first pixel (left edge)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6 + 0.5;
                }
                else // last pixel (right edge)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed) / 6 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen) / 6 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue) / 6 + 0.5;
                }
            }
            else if (i == 0) // first row
            {
                if (j > 0 && j < width - 1) // pixels between first and last (top edge)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6 + 0.5;
                }
                else if (j == 0) // first pixel (top left corner)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4 + 0.5;
                }
                else // last pixel (top right corner)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4 + 0.5;
                }
            }
            else // last row
            {
                if (j > 0 && j < width - 1) // pixels between first and last (bottom edge)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6 + 0.5;
                }
                else if (j == 0) // first pixel (bottom left corner)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4 + 0.5;
                }
                else // last pixel (bottom right corner)
                {
                    avgRed = (float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4 + 0.5;
                    avgGreen = (float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4 + 0.5;
                    avgBlue = (float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4 + 0.5;
                }
            }

            imageTemp[i][j].rgbtRed = avgRed;
            imageTemp[i][j].rgbtGreen = avgGreen;
            imageTemp[i][j].rgbtBlue = avgBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imageTemp[i][j].rgbtRed;
            image[i][j].rgbtGreen = imageTemp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imageTemp[i][j].rgbtBlue;
        }
    }
    return;
}