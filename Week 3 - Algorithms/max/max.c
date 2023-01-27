// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    // Bubble Sort
    int swap_flag;
    // In best case scenario, this outer loop runs 1 time because swap_flag will be
    // zero and loop will break out at the end.
    for (int passthrough = 0; passthrough <= (n - 1); passthrough++)
    {
        // Reset swap_flag to zero.
        swap_flag = 0;
        // Main loop where swapping occurs. In best case scenario, this inner loop runs
        // n-2 times. With each passthrough, the biggest unsorted number bubbles to the
        // right of the array. We subtract the number of passthroughs from n-2 so that we
        // only need to look at the pairs of numbers that haven't been sorted yet.
        for (int i = 0; i <= (n - 2 - passthrough); i++)
        {
            if (array[i] > array[i + 1])
            {
                int placeholder = array[i];
                array[i] = array[i + 1];
                array[i + 1] = placeholder;
                swap_flag = 1;
            }
        }
        // Conditional test to see if there was any swapping for the current passthrough.
        // If no swapping occur (swap_flag == 0), then array is sorted and we can break
        // from the outer for loop.
        if (swap_flag == 0)
        {
            break;
        }
    }
    return array[n - 1];
}
