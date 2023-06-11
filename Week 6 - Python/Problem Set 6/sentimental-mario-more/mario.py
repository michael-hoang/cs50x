from cs50 import get_int


# TODO
height = get_int('Height: ')
while height < 1 or height > 8:
    print('Only height between 1 and 8, inclusive, allowed.')
    height = get_int('Height: ')

for row in range(height):
    bricks = '#' * (row + 1)
    print(' ' * (height - row - 1), end='')
    print(bricks, end='')
    # gap between two pyramid halves
    print('  ', end='')
    print(bricks)