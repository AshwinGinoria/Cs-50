// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy float infile outfile\n");
        return 1;
    }

    // remember filenames
    float factor = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf,bfn;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi,bin;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Copying Header information to new
    bin = bi;
    bfn = bf;


    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determining padding for printlines
    int newpadding = (4 - ((int)(factor * bi.biWidth) * sizeof(RGBTRIPLE)) % 4) % 4;

    bin.biWidth *= factor;
    bin.biHeight *= factor;
    bin.biSizeImage = (bin.biWidth * sizeof(RGBTRIPLE) + newpadding) * abs(bin.biHeight);
    bfn.bfSize = bin.biSizeImage + bfn.bfOffBits;


    // write outfile's BITMAPFILEHEADER
    fwrite(&bfn, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bin, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Storing Scan line length
    int slength = bi.biWidth * sizeof(RGBTRIPLE) + padding ;

    if (factor >= 1)
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            for (int l = 0; l < factor ; l++)
            {
                if (l != 0)
                {
                    fseek(inptr, -slength, SEEK_CUR);
                }
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile factor no of times
                    for (int k = 0; k < factor; k++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);

                // adding padding to outputFile
                for (int k = 0; k < newpadding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
    }
    else
    {
        int decrease = (int)(1/factor);
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            if (i % 2 != 0)
            {
                fseek(inptr, slength, SEEK_CUR);
                continue;
            }
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                if (j % 2 != 0)
                {
                    fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                    continue;
                }
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile factor no of times
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // adding padding to outputFile
            for (int j = 0; j < newpadding; j++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
