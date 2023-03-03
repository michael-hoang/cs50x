class Jar:
    """A class that represents a cookie jar in which to store cookies."""

    def __init__(self, capacity=12):
        """Initialize a cookie jar with the given capacity."""
        self._capacity = capacity
        self._size = 0

        if self._capacity < 0:
            raise ValueError(
                'Cookie jar capacity cannot be a non-negative integer.')

    def __str__(self) -> str:
        """Return the number of 🍪 in the cookie jar."""
        return '🍪' * self.size

    def deposit(self, n):
        """Add n cookies to the cookie jar."""
        self._size += n
        if self.size > self._capacity:
            raise ValueError(
                'The cookie jar has reached its capacity and cannot hold anymore cookies.')

    def withdraw(self, n):
        """Remove n cookies from the cookie jar."""
        self._size -= n
        if self.size < 0:
            raise ValueError(
                'There aren\'t that many cookies in the cookie jar.')

    @property
    def capacity(self):
        """Return the cookie jar's capacity."""
        return self._capacity

    @property
    def size(self):
        """Return the number of cookies actually in the cookie jar."""
        return self._size


def main():
    jar = Jar()
    print('Instantiating a Jar called jar with a default capacity of 12...')
    print(str(jar.capacity))
    print('Printing the number of cookies in the jar...')
    print(str(jar))
    print('Putting 2 cookies in the cookie jar...')
    jar.deposit(2)
    print('Printing the number of cookies in the jar...')
    print(str(jar))
    print('Taking 1 cookie from the cookie jar...')
    jar.withdraw(1)
    print('Printing the number of cookies in the jar...')
    print(str(jar))


main()
