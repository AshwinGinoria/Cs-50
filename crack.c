#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check No. Command line arguments entered 
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
    // Getting hash and salt
    string hash = argv[1];
    char leters[53] ="\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
    char salt[3];
    salt[0] = hash[0];
    salt[1] = hash[1];
    salt[2] = '\0';
    // i determines the legth of the password being guessed.
    char temp[6] = "\0\0\0\0\0\0";
    for (int i5 = 0 ; i5 < 53 ; i5++)
    {
        for (int i4 = 0 ; i4 < 53 ; i4++)
        {
            for (int i3 = 0 ; i3 < 53 ; i3++)
            {
                for (int i2 = 0 ; i2 < 53 ; i2++)
                {
                    for (int i1 = 0 ; i1 < 53 ; i1++)
                    {
                        temp[0] = leters[i1];
                        temp[1] = leters[i2];
                        temp[2] = leters[i3];
                        temp[3] = leters[i4];
                        temp[4] = leters[i5];
                        if (strcmp(crypt(temp, salt), hash) == 0)
                        {
                            printf("%s\n", temp);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    printf("Password Unable to crack!!\n");
    return 2;
}
