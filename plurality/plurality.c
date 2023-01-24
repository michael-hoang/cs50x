#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    // Bubble Sort
    int n = candidate_count - 1;
    int swap_counter = 1;
    while (swap_counter != 0)
    {
        swap_counter = 0;
        for (int i = 0; i < n; i++)
        {
            int left_candidate_vote = candidates[i].votes;
            int right_candidate_vote = candidates[i + 1].votes;
            if (left_candidate_vote > right_candidate_vote)
            {
                candidate placeholder[] = {candidates[i]};
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = placeholder[0];
                swap_counter++;
            }
        }
        n--; // decrement array size per passthrough to account for a new element getting "bubbled" to the end.
    }

    // Prints winner(s)
    int last_index = candidate_count - 1;
    printf("%s\n", candidates[last_index].name);

    while (candidates[last_index - 1].votes == candidates[last_index].votes)
    {
        printf("%s\n", candidates[last_index - 1].name);
        last_index--;
    }
    return;
}