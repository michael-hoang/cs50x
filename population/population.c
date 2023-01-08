#include <cs50.h>
#include <stdio.h>

int get_growth_year(int start, int end);
void print_growth_year(int year);

int main(void)
{
    // TODO: Prompt for start size
    int start_pop;
    do
    {
        start_pop = get_int("Start size: ");
    }
    while (start_pop < 9);

    // TODO: Prompt for end size
    int end_pop;
    do
    {
        end_pop = get_int("End size: ");
    }
    while (end_pop < start_pop);

    // TODO: Calculate number of years until we reach threshold
    int years = get_growth_year(start_pop, end_pop);

    // TODO: Print number of years
    print_growth_year(years);
}

int get_growth_year(int start, int end)
{
    int born_per_year, pass_per_year, year_end_pop;
    int growth_year = 0;
    while (start < end)
    {
        born_per_year = start / 3;
        pass_per_year = start / 4;
        year_end_pop = start + born_per_year - pass_per_year;
        growth_year ++;
        start = year_end_pop;
    }
    return growth_year;
}

void print_growth_year(int year)
{
    printf("Years: %i\n", year);
}
