# Questions

## What's `stdint.h`?

Its a header file that provides more flexibiliy to typedefs

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

'u' in the name stands for unsigned. which means that the first bit is also being used to store value and does not signify '+' or '-',  int implies that the data will be integer and 8,16,32 specifies the memory in bits to be used to store data.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE - 1 byte
DWORD - 4 byte
LONG - 4 byte
WORD - 2 byte

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

the first two bytes of any BMP file must be 0x42 0x4D in hexadecimal symbolizing BM used to identify file type.

## What's the difference between `bfSize` and `biSize`?

bfsize is file size in bytes
bisize is size of the header in bytes

## What does it mean if `biHeight` is negative?

image vertically flipped

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

fopen(x) may return NULL if there is no file named x.

## Why is the third argument to `fread` always `1` in our code?

the third argument specifies the number of elements to be read but since we are reading elements one by one it is always 1.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

moves the file pointer a specific unit from its current location.

## What is `SEEK_CUR`?

moves the file pointer to a specific location in the file.
