#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int avg = (blue + red + green) / 3;

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }

    }
    return;
}

int limit_value(int input, int limit){
    int value;
    if(input > limit){
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
            int blue = image[i][j].rgbtBlue;
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int sepiaRed = limit_value(round(0.393 * red + 0.769 * green + 0.189 * blue), 255);
            int sepiaGreen = limit_value(round(0.349 * red + 0.686 * green + 0.168 * blue), 255);
            int sepiaBlue = limit_value(round(0.272 * red + 0.534 * green + 0.131 * blue), 255);

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
        }

    }
    return;
}

void swap(RGBTRIPLE *pix1, RGBTRIPLE *pix2){
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
        for (int j = 0; j < width/2; j++)
        {
            swap(&image[i][j], &image[i][k - j]);
            //k--;
        }
    }
    return;
}

bool IndexValidity(int i, int j, int height, int width){
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
	int totalRed, totalGreen, totalBlue, nrOfValids = 0;
	RGBTRIPLE blurImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
			totalRed = 0;
			totalBlue = 0;
			totalGreen = 0;
			nrOfValids = 0;
            // if valid location, add to total, incerement nr of totals
            int loci, locj = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    loci = i + l;
                    locj = j + k;
                    // bool valid = IndexValidity(loci, locj, height, width);
					if ((loci < height) && (loci >=  0) && (locj < width) && (locj >= 0))
                    // if (valiid == true)
                    {
                        totalRed = totalRed + image[loci][locj].rgbtRed;
                        totalGreen = totalGreen + image[loci][locj].rgbtGreen;
                        totalBlue = totalBlue + image[loci][locj].rgbtBlue;
                        nrOfValids++;
                    }
                }
            }
            blurImage[i][j].rgbtRed = limit_value(round(totalRed / nrOfValids), 255);
            blurImage[i][j].rgbtBlue = limit_value(round(totalBlue / nrOfValids), 255);
            blurImage[i][j].rgbtGreen = limit_value(round(totalGreen / nrOfValids), 255);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurImage[i][j].rgbtBlue;
			image[i][j].rgbtRed = blurImage[i][j].rgbtRed;
			image[i][j].rgbtGreen = blurImage[i][j].rgbtGreen;
        }
    }

    return;
}
