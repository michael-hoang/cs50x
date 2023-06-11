# TODO
from cs50 import get_string


def coleman_liau_index(text: str) -> int:
    """Return the Coleman-Liau index of a text."""
    letters = len([char for char in text if char.isalpha()])
    # Split string into a list. Default separator is any whitespace.
    words = len(text.split())
    sentences = len([char for char in text if char in '.!?'])
    l = letters / words * 100
    s = sentences / words * 100
    return round(0.0588 * l - 0.296 * s - 15.8)


text = get_string('Text: ')
i = coleman_liau_index(text)
if i < 1:
    print('Before Grade 1')
elif i > 15:
    print('Grade 16+')
else:
    print(f'Grade {i}')
