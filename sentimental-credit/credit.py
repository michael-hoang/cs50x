# TODO
def get_credit_card_numbers():
    """Prompt user to enter a credit card number."""
    while True:
        numbers = input('Number: ')
        if numbers.isnumeric():
            return numbers

        print('Enter only numeric characters.')


def get_credit_card_network(numbers: str) -> str or bool:
    """Return AMEX, MASTERCARD, VISA, or False."""
    prefix = int(numbers[:2])
    length = len(numbers)
    if prefix > 50 and prefix < 56 and length == 16:
        return 'MASTERCARD'
    elif (prefix == 34 or prefix == 37) and length == 15:
        return 'AMEX'
    elif numbers[0] == '4' and (length == 13 or length == 16):
        return 'VISA'
    else:
        return False


def luhns_algo(numbers: str) -> bool:
    """Return True if credit card numbers pass Luhn's Algorithm."""
    sum1 = 0
    sum2 = 0
    for i in range(len(numbers)):
        index = -(i + 1)
        if (index % 2) == 0:
            digit_x2_int = int(numbers[index]) * 2
            digit_x2_str = str(digit_x2_int)
            if len(digit_x2_str) > 1:
                sum2 += int(digit_x2_str[0]) + int(digit_x2_str[1])
            else:
                sum2 += digit_x2_int
        else:
            sum1 += int(numbers[index])
    # if the total modulo 10 is congruent to 0
    if (sum1 + sum2) % 10 == 0:
        return True

    return False


def main():
    numbers = get_credit_card_numbers()
    network = get_credit_card_network(numbers)
    if luhns_algo(numbers) and network:
        print(network)
    else:
        print('INVALID')


# Run program
main()
