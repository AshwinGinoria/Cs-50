#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover Image\n");
        return 1;
    }

    // remeber filename
    char *infile = argv[1];

    // Open Input File
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    const int block_size = 512;
    char filename[sizeof "Image100.jpg"];
    int count = 1, num;
    char Buffer[block_size];
    int flag = 0;
    char byte1, byte2, byte3;
    byte1 = 0xff;
    byte2 = 0xd8;
    byte3 = 0xff;
    FILE *outptr;


    while (1)
    {
        // Reading one block from memoryt card to Buffer
        num = fread(Buffer, block_size, 1, inptr);

        // n = 0 => EOF therefore close open files and exit.
        if (num == 0)
        {
            if (flag == 1)
            {
                fclose(outptr);
            }
            fclose(inptr);
            printf("End Of File reached after recovering %d Images.\n", count);
            return 0;
        }

        // Checking for JPEG signatures in the start of Buffer
        if (Buffer[0] == byte1 && Buffer[1] == byte2 && Buffer[2] == byte3)
        {
            // If output file already open then close it.
            if (flag == 1)
            {
                fclose(outptr);
            }

            // Opening new Output file.
            sprintf(filename, "Image%03d.jpg", count);
            outptr = fopen(filename, "w");

            // Incrementing count and setting flag == true
            count++;
            flag = 1;

            // Writing the current contents of buffer to output file
            fwrite(Buffer, block_size, 1, outptr);
        }
        // IF NO JPEG Signatures found at the start of buffer
        else
        {
            // If a file is already open write the contents of buffer to the open file.
            if (flag == 1)
            {
                fwrite(Buffer, block_size, 1, outptr);
            }
        }
    }

}

