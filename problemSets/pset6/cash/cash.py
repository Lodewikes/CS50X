from cs50 import get_float


def main():

    coins = Change.greedy_algorithm(Change())
    print(coins)


class Change:

    # constructor
    def __init__(self):
        self.change = -1
        self.penny = 1
        self.nickel = 5
        self.dime = 10
        self.quarter = 25
        self.total_coins = 0

        # prompt for change
        while self.change < 0:
            self.change = get_float("Change owed: ")

        self.cents_owed = round(self.change * 100)

    # method
    def greedy_algorithm(self):
        # calculate nr of each coin owed
        nr_quarters = int(self.cents_owed / self.quarter)
        self.cents_owed = self.cents_owed % self.quarter
        nr_dimes = int(self.cents_owed / self.dime)
        self.cents_owed = self.cents_owed % self.dime
        nr_nickels = int(self.cents_owed / self.nickel)
        self.cents_owed = self.cents_owed % self.nickel
        nr_pennies = int(self.cents_owed / self.penny)
        self.cents_owed = self.cents_owed % self.penny

        # quit if
        if self.cents_owed != 0:
            print("calcError: change left")
            return 1
        # calculate total coins owed
        self.total_coins = nr_pennies + nr_dimes + nr_nickels + nr_quarters
        return self.total_coins


if __name__ == '__main__':
    main()
