import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader: csv.DictReader) -> dict:
    """Return a dictionary containing the most recent 14 days of new cases for each state."""
    recent_total_cases = {}
    # Create and reverse list so that the most recent cases are first.
    data_list = list(reader)[::-1]
    for data in data_list:
        state = data['state']
        cases = int(data['cases'])
        if state not in recent_total_cases:
            recent_total_cases[state] = [cases]
        elif len(recent_total_cases[state]) != 15:
            recent_total_cases[state].append(cases)
        else:
            break

    new_cases = {
        state: [cases[i] - cases[i+1] for i in range(0, len(cases)-1)]
        for state, cases in recent_total_cases.items()
    }

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases: dict, states: list):
    """Print out the seven day average for the given state(s)."""
    for state in new_cases:
        if state in new_cases:
            current_average = round(sum(new_cases[state][:7]) / 7)
            previous_average = round(sum(new_cases[state][7:]) / 7)
            try:
                percent_change = round(
                    (current_average - previous_average) / previous_average * 100)
                change, article = ('decrease', 'a') if percent_change < 0 else ('increase', 'an')
            except ZeroDivisionError:
                print(f'{state} had a 7-day average of {current_average}.')
            else:
                print(
                    f'{state} had a 7-day average of {current_average} and {article} {change} of {abs(percent_change)}%.')


main()
