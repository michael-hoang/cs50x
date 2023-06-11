// Practice using structs
// Practice writing a linear search function

/**
 * Beach Burger Shack has the following 10 items on their menu
 * Burger: $9.5
 * Vegan Burger: $11
 * Hot Dog: $5
 * Cheese Dog: $7
 * Fries: $5
 * Cheese Fries: $6
 * Cold Pressed Juice: $7
 * Cold Brew: $3
 * Water: $2
 * Soda: $2
*/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Number of menu items
// Adjust this value (10) to number of items input below
#define NUM_ITEMS 10

// Menu itmes have item name and price
typedef struct
{
    string item;
    float price;
}
menu_item;

// Array of menu items
menu_item menu[NUM_ITEMS];

// Add items to menu
void add_items(void);

// Calculate total cost
float get_cost(string item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i].price);
    }
    printf("\n");

    float total = 0;
    while (true)
    {
        string item = get_string("Enter a food item: ");
        if (strlen(item) == 0)
        {
            printf("\n");
            break;
        }

        total += get_cost(item);
    }

    printf("Your total cost is: $%.2f\n", total);
}

// Add at least the first four items to the menu array
void add_items(void)
{
    string item[] = {"Burger", "Vegan Burger", "Hot Dog", "Cheese Dog", "Fries", "Cheese Fries", "Cold Pressed Juice", "Cold Brew", "Water", "Soda"};
    float price[] = {9.5, 11, 5, 7, 5, 6, 7, 3, 2, 2};

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        menu[i].item = item[i];
        menu[i].price = price[i];
    }
    return;
}

// Search through the menu array to find an item's cost
float get_cost(string item)
{
    // Convert item string to title case
    int length = strlen(item);
    int whitespace_flag;
    for (int j = 0; j < length; j++)
    {
        // If not first index, no preceding whitespace, and is uppercase
        if (j != 0 && whitespace_flag == 0 && isupper(item[j]))
        {
            item[j] = item[j] + 32; // Add 32 to ASCII integer to convert char from upper to lowercase
        }
        // If character is the first index or has preceding whitespace AND is lowercase
        else if ((j == 0 || whitespace_flag == 1) && islower(item[j]))
        {
            item[j] = item[j] - 32; // Subtract 32 to convert char from lower to uppercase
            whitespace_flag = 0; // Reset whitespace_flag
        }
        // If character with preceding whitespace is already uppercase, reset whitespace_flag
        else if (whitespace_flag == 1 && isupper(item[j]))
        {
            whitespace_flag = 0;
        }
        else if (isspace(item[j]))
        {
            whitespace_flag = 1;
        }
    }

    for (int i = 0; i < NUM_ITEMS; i++)
    {

        if (strcmp(menu[i].item, item) == 0)
        {
            return menu[i].price;
        }
    }
    printf("Invalid Item!\n");
    return 0.0;
}