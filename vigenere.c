#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isword(int length, char a[]);
int shift(char c);

int main(int argc, string argv[])
{
    // Prints Usage if no of keys is invalid
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    // Prints Usage if Invalid Keyword is Entered
    else if ( isword(strlen(argv[1]), argv[1]) == 0 )
    {
        printf("Usage: ./vigenere keyword\n");
        return 2;
    }
    int l = strlen(argv[1]) ;
    string keyword = argv[1] ;
    char plain_text[100] ;
    printf("plaintext: ");
    scanf("%[^\n]s", plain_text );
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plain_text) ; i < n ; i++)
    {
        if ( islower(plain_text[i]) )
        {
            printf("%c", (char)('a' + (plain_text[i] - 'a' + shift(keyword[i % l])) % 26)) ;
        }
        else if( isupper(plain_text[i]))
        {
            printf("%c", (char)('A' + (plain_text[i] - 'A' + shift(keyword[i % l])) % 26));
        }
        else
        {
            printf("%c", plain_text[i]) ;
        }
    }
    printf("\n") ;
}

int isword(int length, char a[])
{
    for(int i = 0 ; i < length ; i++)
    {
        if (!((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z')))
        {
            return 0;
        }
    }
    return 1;
}

int shift(char c)
{
    if ( c - 'a' >= 0)
        return (int)(c - 'a');
    else
        return (int)(c - 'A');
}
