#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void ifnullclosefile(FILE *file, bool setnull);

int main(int argc, char *argv[])
{
    // check for command arguments
    if (argc != 2)
    {
        puts("Usage: ./recover image");
        return 1;
    }
    else
    {
        FILE *outfile = NULL;
        int count = 0;
        FILE *infile = fopen(argv[1], "rb");
        char *jpeg = (char *)malloc(8 * sizeof(char));
        unsigned char *buffer = (unsigned char *)malloc(512 * sizeof(unsigned char));
        if (infile == NULL || jpeg == NULL || buffer == NULL)
        {
            puts("could not open file");
            return 1;
        }

        do
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {

                // now recover and write jpeg
                ifnullclosefile(outfile, true); // TODO line seems unecessary

                sprintf(jpeg, "%03i.jpg", count);
                outfile = fopen(jpeg, "wb");

                if (outfile == NULL)
                {
                    printf("Cannot open %s\n", jpeg);
                    return 1;
                }

                fwrite(buffer, sizeof(buffer), 1, outfile);
                //printf("%s %#X\n", jpeg, buffer[3]);
                count++;
            }
            else
            {
                if (outfile != NULL)
                {
                    fwrite(buffer, sizeof(buffer), 1, outfile);
                }
            }

        }
        while (fread(buffer, sizeof(buffer), 1, infile));

        ifnullclosefile(infile, false);
        ifnullclosefile(outfile, false);
        free(buffer);
        free(jpeg);
    }
    return 0;
}

// close file
void ifnullclosefile(FILE *file, bool setnull)
{
    if (file != NULL)
    {
        fclose(file);
        if (setnull == true)
        {
            file = NULL;
        }

    }
}
