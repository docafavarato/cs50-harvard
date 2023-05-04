#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26

int main(int argc, string argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // Check key length and characters
    string key = argv[1];
    int keylen = strlen(key);
    if (keylen != ALPHABET_SIZE)
    {
        printf("Key must contain %d characters.\n", ALPHABET_SIZE);
        return 1;
    }
    for (int i = 0; i < keylen; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }

    // Check key uniqueness
    int freq[ALPHABET_SIZE] = {0};
    for (int i = 0; i < keylen; i++)
    {
        int index = tolower(key[i]) - 'a';
        if (freq[index]++ > 0)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    // Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // Substitute letters
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int index = tolower(plaintext[i]) - 'a';
            char c = islower(plaintext[i]) ? tolower(key[index]) : toupper(key[index]);
            printf("%c", c);
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

    return 0;
}
