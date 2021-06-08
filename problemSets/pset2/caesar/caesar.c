// encrypting messages using Caesar's cipher
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

string prompt_message();
void caesars_cipher(int key, string message);

int main(int argc, string argv[])
{
    // prompt user for + int as argv
    if (argc == 2)
    {
        int key = atoi(argv[1]);
        int modified_key;

        if (key >= 1)
        {
            string message;
            // call prompt function
            message = prompt_message();
            printf("ciphertext: ");
            // call encrypt function
            caesars_cipher(key, message);
        }
        else
        {
            printf("usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    return 0;
}


// prompt user for text
string prompt_message()
{
    string text;
    text = get_string("plaintext: ");
    return text;
}

// encrypt the message
void caesars_cipher(int key, string message)
{
    if (key >= 26)
    {
        key = key % 26;
    }

    for (int i = 0; i < strlen(message); i++)
    {
        // handle lower case
        if (message[i] >= 'a' && message[i] <= 'z')
        {
            if (message[i] + key > 121)
            {
                message[i] = message[i] - 26;
            }
            message[i] = message[i] + key;
            //printf("%c", message[i] + key);
        }
        // handle upper case
        else if (message[i] >= 'A' && message[i] <= 'Z')
        {
            if (message[i] + key > 90)
            {
                message[i] = message[i] - 26;
            }
            message[i] = message[i] + key;
            //printf("%c", message[i] + key);
        }
    }
    printf("%s", message);
    printf("\n");
}

