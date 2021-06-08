#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            avg = round((image[j][i].rgbtBlue + image[j][i].rgbtRed + image[j][i].rgbtGreen) / 3.0);

            // apply average colour to each pixel
            image[j][i].rgbtRed = avg;
            image[j][i].rgbtGreen = avg;
            image[j][i].rgbtBlue = avg;
        }

    }
}

// if rgb value exceeds 255, limit it to 255
int limit_value(int input, int limit)
{
    int value;
    if (input > limit)
    {
        value = limit;
    }
    else
    {
        value = input;
    }
    return value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get color of pixel
            int blue = image[i][j].rgbtBlue;
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;

            // apply sepia colouring to each pixel
            int sepiaRed = limit_value(round(0.393 * red + 0.769 * green + 0.189 * blue), 255);
            int sepiaGreen = limit_value(round(0.349 * red + 0.686 * green + 0.168 * blue), 255);
            int sepiaBlue = limit_value(round(0.272 * red + 0.534 * green + 0.131 * blue), 255);

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }

    }
}

// swap function to reflect image
void swap(RGBTRIPLE *pix1, RGBTRIPLE *pix2)
{
    RGBTRIPLE temp = *pix1;
    *pix1 = *pix2;
    *pix2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int k = width - 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][k - j]);
            //k--;
        }
    }
}

// check if index i, j is a valid pixel
bool IndexValidity(int i, int j, int height, int width)
{
    if (i >= 0 && i < height && j >= 0 && j < width)
    {
        return true;
    }
    else
    {
        return false;
    }

}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int totalRed, totalGreen, totalBlue;
    float nrOfValids;
    // create temporary image
    RGBTRIPLE blurImage[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            totalRed = 0;
            totalGreen = 0;
            totalBlue = 0;
            nrOfValids = 0.00;

            // sums values of surrounding pixels if they are within bounds
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }
                    // calculate colour totals
                    totalRed += image[j + k][i + h].rgbtRed;
                    totalGreen += image[j + k][i + h].rgbtGreen;
                    totalBlue += image[j + k][i + h].rgbtBlue;
                    nrOfValids++;
                }
            }

            // blur the image
            blurImage[j][i].rgbtRed = limit_value(round(totalRed / nrOfValids), 255);
            blurImage[j][i].rgbtGreen = limit_value(round(totalGreen / nrOfValids), 255);
            blurImage[j][i].rgbtBlue = limit_value(round(totalBlue / nrOfValids), 255);
        }
    }

    // apply the blurring to original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurImage[i][j].rgbtBlue;
            image[i][j].rgbtRed = blurImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurImage[i][j].rgbtGreen;
        }
    }
}
