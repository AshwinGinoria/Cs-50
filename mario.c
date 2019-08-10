#include <cs50.h>
#include <stdio.h>

void pyramid(int);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height : ");
    }while( height < 1 || height > 8 );
    pyramid(height);
}

void pyramid(int h)
{
    for ( int i=0 ; i < h ; i++ )
    {
        for ( int j=1 ; j<h-i ; j++ )
            printf(" ");
        for( int j=0 ; j<=i ; j++ )
            printf("#");
        printf("  ");
        for( int j=0 ; j<=i ; j++ )
            printf("#");
        printf("\n");
    }
}
