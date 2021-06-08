from cs50 import get_string
import re


def main():

    readability = Readability()
    grade = readability.getIndex()

    # grade 16+
    if grade >= 16:
        print("Grade 16+")
    # grade less than 1
    elif grade < 1:
        print("Before Grade 1")
    # else grade
    else:
        print(f"Grade {grade}")


class Readability:

    # constructor prompts user for text
    def __init__(self):
        self.__text = get_string("Text: ")
        self.__letter_count = self.__letterCounter()
        self.__word_count = self.__wordCounter()
        self.__sentence_count = self.__sentenceCounter()
        self.__index = self.__indexCalculator()

    # count number of alphabetic letters in string
    def __letterCounter(self):
        count = 0
        for i in self.__text.lower():
            if i.isalpha():
                count += 1
        return count

    # count number of words in string
    def __wordCounter(self):
        return len(self.__text.strip().split(" "))

    # count number of sentences in string
    def __sentenceCounter(self):
        count = len(re.split(r'[.!?]+', self.__text)) - 1
        return count

    # calculate the index
    def __indexCalculator(self):
        l = (self.__letter_count / self.__word_count) * 100
        s = (self.__sentence_count / self.__word_count) * 100
        return round(0.0588 * l - 0.296 * s - 15.8)

    # getter for letter count
    def getLetterCount(self):
        return self.__letter_count

    # getter for word count
    def getWordCount(self):
        return self.__word_count

    # getter for sentence count
    def getSentenceCount(self):
        return self.__sentence_count

    # getter for index
    def getIndex(self):
        return self.__index


if __name__ == "__main__":
    main()
