#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>

// generate pyramid based on input height

void make_pyramid(int height);
int prompt_height(int max);

// main
int main(void)
{

    // prompt user for pyramid height
    int height = prompt_height(8);
    // print pyramid
    make_pyramid(height);
}

// print pyramid
void make_pyramid(int height)
{
    int q = height - 1;
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < height; i++)
        {
            if (i >= q)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        q = q - 1;
        printf("\n");
    }

}

// prompt user for height
int prompt_height(int max)
{

    int height = get_int("Height: ");
    while (height > max || height < 1)
    {
        height = get_int("Height: ");
    }
    return height;
}
