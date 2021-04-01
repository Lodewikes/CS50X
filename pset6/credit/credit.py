def main():
    # Call functions
    card = CreditCard()
    card.length_check()
    card.check_sum()
    card.card_validity_test()
    card.show_card_type()


class CreditCard:

    # Constructor
    def __init__(self):
        self.lengthvalid: bool = False
        self.sumvalid: bool = False
        self.sum = 0
        self.cardvalid: bool = False
        self.type: str = ''
        self.card_number = -1

        # prompt user for number
        while self.card_number < 0:
            self.card_number = int(input("Number: "))

        self.card_number = str(self.card_number)

    # determine the length of the number
    def length_check(self):

        if len(self.card_number) == 13 or len(self.card_number) == 15 or len(self.card_number) == 16:
            self.lengthvalid = True
        else:
            self.lengthvalid = False
        return len(self.card_number)

    # check sum
    def check_sum(self):
        self.sum = 0
        max_index = len(self.card_number) - 1
        index = 0
        if len(self.card_number) == 16:
            index = 0
        elif len(self.card_number) == 15 or len(self.card_number) == 13:
            index = 1

        for i in range(len(self.card_number)):
            if index > max_index:
                break
            else:
                twice_val = int(self.card_number[index]) * 2
                if twice_val >= 10:
                    self.sum += 1
                    digit = twice_val - 10
                    self.sum += digit
                else:
                    self.sum += twice_val
                index += 2

        if len(self.card_number) == 16:
            index = 1
        elif len(self.card_number) == 15 or len(self.card_number) == 13:
            index = 0

        for j in range(len(self.card_number)):
            if index <= max_index:
                single_val = int(self.card_number[index])
                self.sum += single_val
                index += 2
            else:
                break

        if (self.sum % 10) == 0:
            self.sumvalid = True
        else:
            self.sumvalid = False

    # determine if the card number is valid
    def card_validity_test(self):

        if self.lengthvalid and self.sumvalid:
            self.cardvalid = True
            return True
        else:
            self.cardvalid = False
            return False

    # determine the type of card
    def card_type(self):
        # VISA
        if int(self.card_number[0]) == 4:
            self.type = "VISA"
        # MATSERCARD
        elif int(self.card_number[0]) == 5:
            if 1 <= int(self.card_number[1]) <= 5:
                self.type = "MASTERCARD"
        # AMEX
        elif int(self.card_number[0]) == 3:
            if int(self.card_number[1]) == 4 or int(self.card_number[1]) == 7:
                self.type = "AMEX"
        # Not a valid card
        else:
            self.type = "INVALID"

    # print the card type
    def show_card_type(self):
        if self.cardvalid:
            if (self.sum % 10) == 0:
                self.card_type()
            else:
                self.type = "INVALID"
        else:
            self.type = "INVALID"

        print(self.type)


if __name__ == '__main__':
    main()
