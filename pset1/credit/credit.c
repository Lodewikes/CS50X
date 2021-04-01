#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

// Predefine functions
void cardValidityTest(long int cardNumber, int length);
int countDigits(long int cardNumber);
void red_string();
void cyan_string();
void string_colour_reset();

// main
int main(void)
{
    long int cardNumber;
    do
    {
        cardNumber = get_long("Number: ");
    }
    while (cardNumber < 0);

    int length = countDigits(cardNumber);
    cardValidityTest(cardNumber, length);
}

// create functions

// count number of digits
int countDigits(long int cardNumber)
{
    int length = 0;
    while (cardNumber != 0)
    {
        cardNumber /= 10;
        ++length;
    }
    //int length = 1 + (int)log10(cardNumber);
    return length;
}

// check if card is valid
void cardValidityTest(long int cardNumber, int length)
{
    // define array
    int digitArray[length];
    int index = 0;


    // break number into digits && append to array
    do
    {
        int digit = cardNumber % 10;
        digitArray[index] = digit;
        index++;
    }
    while (cardNumber /= 10);

    // find correct values in array
    int twiceValue;
    int sum = 0;
    for (int locaterIndex = 1; locaterIndex < length; locaterIndex = locaterIndex + 2)
    {
        twiceValue = digitArray[locaterIndex] * 2;
        do
        {
            int newDigit = twiceValue % 10;
            sum = sum + newDigit;
        }
        while (twiceValue /= 10);
    }
    for (int otherIndex = 0; otherIndex < length; otherIndex = otherIndex + 2)
    {
        int singleValue = digitArray[otherIndex];
        sum = sum + singleValue;
    }
    // determine type of card
    if (sum % 10 == 0)
    {
        // determine if visa
        if (digitArray[length - 1] == 4 && (length == 13 || length == 16))
        {
            printf("VISA\n");
        }
        // determine if mastercard
        else if (digitArray[length - 1] == 5 && length == 16)
        {
            if (digitArray[length - 2] >= 1 && digitArray[length - 2] <= 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // determine if AMEX
        else if (digitArray[length - 1] == 3 && length == 15)
        {
            if (digitArray[length - 2] == 4 || digitArray[length - 2] == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // else not a valid card
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
