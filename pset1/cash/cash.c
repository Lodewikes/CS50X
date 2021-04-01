#include <stdio.h>
#include <cs50.h>
#include <math.h>

void greedyAlgorithm(int centsOwed);

// execute functions and prompt user for input
int main(void)
{

    float change;
    do
    {
        // prompt user for owed change
        change = get_float("Change owed: ");
    }
    while (change < 0);

    int centsOwed = round(change * 100);

    // call function
    greedyAlgorithm(centsOwed);

    return 0;
}


// calculate fewest number of coins for change
void greedyAlgorithm(int centsOwed)
{

    int penny = 1;
    int nickel = 5;
    int dime = 10;
    int quarter = 25;

    // calculate number of each type of coin
    int nrQuarters = centsOwed / quarter;
    centsOwed = centsOwed % quarter;

    int nrDimes = centsOwed / dime;
    centsOwed = centsOwed % dime;

    int nrNickels = centsOwed / nickel;
    centsOwed = centsOwed % nickel;

    int nrPennies = centsOwed / penny;
    centsOwed = centsOwed % penny;

    // determine total number of coins
    int totalCoinsUsed = nrQuarters + nrDimes + nrNickels + nrPennies;

    // print total coins
    printf("%i\n", totalCoinsUsed);
}
