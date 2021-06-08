from cs50 import get_int

# main function


def main():
    # create pyramid object and prompt height
    pyramid = Pyramid()
    # build pyramid
    pyramid.build_pyramid()


class Pyramid:
    """This Pyramid will take in a max height and a pyramid height
    which will then check to see if pyramid height falls between zero and max height
    lastly it will print out a pyramid of given height"""

    # __init__
    def __init__(self, max_height: int = 8):
        self.height: int = 0
        self.max_height = max_height
        # if the height does not satisfy requirements: REPROMPT
        while self.height > self.max_height or self.height < 1:
            self.height = get_int("Height: ")

    def build_pyramid(self):
        # grid comprised of spaces and hashes
        # as iterate through rows, nrspaces decr & nrhashes incr
        nr_spaces: int = self.height - 1
        nr_hashes: int = 0
        # for each loc determine is print # or ' '
        for row in range(self.height):
            for col in range(self.height):
                if col >= nr_spaces:
                    print("#", end='')
                else:
                    print(" ", end='')
            print("  ", end='')
            for col in range(self.height):
                if col <= nr_hashes:
                    print("#", end='')
            nr_spaces -= 1
            nr_hashes += 1
            print("")


# call main function
if __name__ == '__main__':
    main()
