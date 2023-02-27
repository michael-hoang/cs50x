from cs50 import get_float


# TODO
while True:
    dollars = get_float('Change owed: ')
    if dollars >= 0:
        break

    print('Provide a non-negative value.')

min_coins = 0
# exclude dollar and half-dollar coins
coins = [0.25, 0.10, 0.05, 0.01]
for coin in coins:
    min_coins += dollars // coin
    dollars = round(dollars % coin, 2)

print(int(min_coins))
