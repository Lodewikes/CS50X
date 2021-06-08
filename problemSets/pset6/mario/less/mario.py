from cs50 import get_int

# main function


def main():
    height = prompt_height(8)
    make_pyramid(height)


# function to promt height from user
def prompt_height(maxheight: int):
    height = 0

    while (height > maxheight or height < 1):
        height = get_int("Height:")
    return height


# function to build and print pyramid
def make_pyramid(height: int):
    # nr of spaces required in a row
    q = height - 1
    # iterate through rows
    for j in range(height):
        # iterate through columns
        for i in range(height):
            # if location column location >= nr of spaces in that row print #
            if i >= q:
                print("#", end='')
            # if location column location <= nr of spaces in that row print space
            else:
                print(" ", end='')
            i += 1
        # print new line
        print("")
        # adjust number of spaces required in new row
        q -= 1
        j += 1


# run main function
if __name__ == '__main__':
    main()
