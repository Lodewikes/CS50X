#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>

int prompt_height(int max);
void make_pyramid(int height);

// main
int main(void)
{

    // prompt user for pyramid height
    int height = prompt_height(8);

    // call function to generate pyramid
    make_pyramid(height);
}


// prompt user to input a height for pyramid
int prompt_height(int max)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > max || height < 1);

    return height;
}


// generate pyramid based on input height
void make_pyramid(int height)
{
    int nr_spaces = height - 1;
    int nr_hashes = 0;
    // loop through matrix
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < height; col++)
        {
            if (col >= nr_spaces)
            {
                // print hashes
                printf("#");
            }
            else
            {
                // print spaces
                printf(" ");
            }
        }
        // print gap
        printf("  ");
        for (int col = 0; col < height; col++)
        {
            if (col <= nr_hashes)
            {
                printf("#");
            }
        }
        nr_spaces--;
        nr_hashes++;
        printf("\n");
    }
}