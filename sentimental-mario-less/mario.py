from cs50 import get_int


# TODO
height = get_int('Height: ')
while height < 1 or height > 8:
    print('Only height between 1 and 8, inclusive, allowed.')
    height = get_int('Height: ')

for row in range(height):
    print(' ' * (height - row - 1), end='')
    print('#' * (row + 1))
