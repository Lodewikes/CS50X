import sys
import pandas as pd
import re


def main():

    # ensure right parameters supplied
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    else:
        # open .csv and .txt files
        with open(sys.argv[1], 'r') as database_file:
            with open(sys.argv[2], 'r') as sequence_file:
                # create dna object
                dna = Dna(database_file, sequence_file)
                # determine dna STR's that exist in database
                dna.str_codes()
                # count nr of consecutive times STR occurs in dna srting
                dna.count_sequences()
                # match sequence count with database to determine individual
                name = dna.match_sequences_with_database()
                # print name of identified individual
                # else print no match
                if name is None:
                    print("No match")
                else:
                    print(name)


class Dna:
    """
    Dna class to count STR's in dna squence and match that to individuals
    in a database, thus identifying which dna sequence belongs to which individual
    """

    # constructors
    def __init__(self, database_file, sequence_file):
        self.str_code_list = []
        self.data = pd.read_csv(database_file)
        self.sequence = sequence_file.read()
        self.df = pd.DataFrame()

    # determine list of STR_codes that exist in database (headers)
    def str_codes(self):
        for col in self.data.columns:
            self.str_code_list.append(col)
        self.str_code_list.remove('name')

    # Function to count each pattern in a sequence
    @staticmethod
    def count(code, sequence):
        p = rf'({code})\1*'
        pattern = re.compile(p)
        match = [match for match in pattern.finditer(sequence)]
        maximum = 0
        for i in range(len(match)):
            if match[i].group().count(code) > maximum:
                maximum = match[i].group().count(code)
        return maximum

    # create dataframe with each STR and nr of occurences
    def count_sequences(self):
        self.df = pd.DataFrame()
        for code in self.str_code_list:
            counter = self.count(code, self.sequence)
            self.df[code] = [counter]
        return self.df

    # match dataframe with database to return name of identified person
    def match_sequences_with_database(self):
        temp_df = self.data.drop('name', axis=1)

        for row in range(len(temp_df)):
            counter = 0
            for col in range(len(temp_df.columns)):
                left = self.df.iloc[[0], [col]].values
                right = temp_df.iloc[[row], [col]].values
                if int(left) == int(right):
                    counter += 1
            if counter == len(temp_df.columns):
                name = str(self.data.iloc[row, 0])
                return name


# run main function
if __name__ == '__main__':
    main()
