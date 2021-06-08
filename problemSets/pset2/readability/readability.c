/* program to test the grade level readability of a text
We will use one coleman-liau index
formula is: index = 0.0699*L - 0.296*S - 15.8
L = avg nr letters per 100 words
S = avg nr sentences per 100 words
*/
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <math.h>

//function declarators
string prompt_text();
int letter_counter(string text);
int word_counter(string text, int nr_letters);
int sentence_counter(string text, int nr_letters);
float index_calc(int nr_letters, int nr_words, int nr_sentences);

int main(void)
{

    // prompt user for text
    string sentence;
    sentence = prompt_text();

    int stringlength = strlen(sentence);

    // count nr of letters
    int nr_letters;
    nr_letters = letter_counter(sentence);

    // count nr of words (spaces)
    int nr_words;
    nr_words = word_counter(sentence, stringlength);

    // count nr of sentences (. , ! , ?)
    int nr_sentences;
    nr_sentences = sentence_counter(sentence, stringlength);

    // calculate index
    float index;
    index = index_calc(nr_letters, nr_words, nr_sentences);
    //printf("grade = %f\n", round(index));
    int grade = (int) round(index);
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
    // print Grade x where x is grade level, to nearest int
    // 16+ for 16 and higher grade
    // less than 1 "before grade 1"
    return 0;

}

// prompt user for text
string prompt_text()
{
    string text;
    text = get_string("text: ");
    return text;
}

int letter_counter(string text)
{
    int nr_letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            nr_letters++;
        }
    }
    return nr_letters;
}

// word counter function
int word_counter(string text, int nr_letters)
{
    int nr_words = 1;

    for (int i = 0; i < nr_letters; i++)
    {
        if (text[i] == ' ')
        {
            nr_words++;
        }
    }
    return nr_words;
}

// sentence counter function
int sentence_counter(string text, int nr_letters)
{
    int nr_sentences = 0;

    for (int i = 0; i < nr_letters; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            nr_sentences++;
        }
    }
    return nr_sentences;
}

float index_calc(int nr_letters, int nr_words, int nr_sentences)
{
    float numLetters = (float) nr_letters;
    float numWords = (float) nr_words;
    float numSens = (float) nr_sentences;
    float index, l, s;

    l = (numLetters / numWords) * 100;
    s = (numSens / numWords) * 100;
    index = 0.0588 * l - 0.296 * s - 15.8;
    return index;
}

