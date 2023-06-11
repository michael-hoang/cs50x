import random

from pyfiglet import Figlet, FigletFont
from sys import argv, exit


def terminate(code):
    """Exit program and display usage."""
    print('Usage: python figlet.py [arg1] [arg2]\n')
    print('optional arguments (both required):')
    print('\targ1: -f or --font')
    print('\targ2: font_name')
    print('\n\tTip: Enter "pyfiglet -l" in terminal for list of fonts.\n')
    exit(code)


# Get a list of Figlet fonts
fonts = FigletFont.getFonts()
argc = len(argv)
if argc == 1:
    font = random.choice(fonts)
elif argc == 3:
    font_flag = argv[1]
    if font_flag != '-f':
        if font_flag != '--font':
            terminate(1)
    font = argv[2]
    if (font not in fonts):
        terminate(2)
else:
    terminate(3)

text = input('Input: ')
f = Figlet(font)
print(f'Output:\n{f.renderText(text)}')
