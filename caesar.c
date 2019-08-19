#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Prints Usage if no of keys is invalid
    if (argc != 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
    // Prints Usage if Invalid Key is Entered
    else if (atoi(argv[1]) == 0)
    {
        printf("Usage: ./caesar key\n");
        return 2;
    }
    // atoi returns integer value from a string
    int shift = atoi(argv[1]) ; 
    char text[100];
    // Taking Input
    printf("plaintext: ");
    scanf("%[^\n]s", text);
    printf("ciphertext: ");
    // Ciphering text using type casting
    for (int i = 0, l = strlen(text) ; i < l ; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            printf("%c", (char)((int)('A' + (text[i] - 'A' + shift) % 26)));
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            printf("%c", (char)((int)('a' + (text[i] - 'a' + shift) % 26)));
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
