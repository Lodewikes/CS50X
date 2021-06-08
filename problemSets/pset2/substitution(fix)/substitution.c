#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool check_cmd_validity(int argc, string argv);
string prompt_message(string user_question);
void encrypt(string key, string message);

int main (int argc, string argv[]){

    string key;
    string message;

    // check if the command line argument has valid key
    bool validity;
    validity = check_cmd_validity(argc, argv[1]);
    if (validity == false)
    {
        return 1;
    }
    else{
    key = argv[1];
    message = prompt_message("plaintext: ");
    printf("ciphertext: ");
    encrypt(key, message);
    }

    return 0;
}

bool check_cmd_validity(int argc, string argv){

    if (argc == 2){
        if (strlen(argv) == 26){
            for (int i = 0; i < 26; i++)
            {
                if ((argv[i] >= 65 && argv[i] <= 90) || (argv[i] >= 97 && argv[i] <= 121))
                {
                    printf("invalid character, must be alphabetic\n");
                    return true;
                }
            }
             // run program
            return true;
        }
        else{
            printf("Key must contain 26 characters\n");
            return false;
        }
    }
    else {
        printf("Usage: ./substitution key\n");
        return false;
    }
}

// prompt user for text
string prompt_message(string user_question){
    string text;
    printf("%s", user_question);
    text = get_string("");
    return text;
}

void encrypt(string key, string message){

    string upper_alphabet, lower_alphabet;
    upper_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    lower_alphabet = "abcdefghijklmnopqrstuvwxyz";

    // loop through letters of message
    for (int i = 0; i < strlen(message); i++)
    {
        if (message[i] >= 'a' && message[i] <= 'z'){
            for (int j = 0, n = strlen(lower_alphabet); j < n; j++)
            {
                if (message[i] == lower_alphabet[j])
                {
                    printf("%c", key[j] + 32);
                }
            }
        }
        else if(message[i] >= 'A' && message[i] <= 'Z'){
            for (int j = 0, n = strlen(lower_alphabet); j < n; j++){
                if (message[i] == upper_alphabet[j])
                {
                    printf("%c", key[j]);
                }
            }
        }
        else {
            printf("%c", message[i]);
        }
    }

    printf("\n");
    // for each letter
        // loop through alphabet and match letters
        // at ith array of matching letter
        // find corresponding jumbled letter
}