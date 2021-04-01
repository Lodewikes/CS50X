#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // promt user for name
    string name = get_string("What's your name? ");
    // print "hello, so-and-so"
    printf("hello, %s\n", name);
}