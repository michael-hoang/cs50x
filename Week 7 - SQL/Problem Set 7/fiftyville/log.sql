-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Problem: CS50 duck was stolen.
-- Objective: Identify thief, hideout location, and accomplice.
-- Clue: Theft took place on July 28, 2021 on Humphrey Street.

-- Retrieve all reports of incident on July 28, 2021.
SELECT * FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28;
-- Clue: At 10:15am, Humphrey Street bakery, 3 witnesses mentioned the bakery.

-- Get interview transcript of all 3 witnesses on July 28, 2021.
SELECT * FROM interviews
WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- Clue: Escaped in car within 10 minutes of theft, check parking security, thief
--- withdrew money at ATM on Leggett Street same morning, was on the phone w/
-- accomplice for < 1 min, talked about earliest flight out of Fiftyville tomorrow.

-- Get bakery security log on July 28, 2021 at 10th hour.
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND activity = "exit"
ORDER BY id;
-- Clue: License plate #'s of all cars that left parking lot between 10:15 and 10:25.

-- Get phone call log on July 28, 2021 that are less than 60 seconds.
SELECT * FROM phone_calls
WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60;
-- Clue: Phone #'s of all callers and receivers that are less than 60 seconds.

-- Request for all ATM withdrawal transactions occured on July 28, 2021 on Leggett Street.
SELECT * FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street"
AND transaction_type = "withdraw";
-- Clue: Bank account numbers of all withdrawal transaction.

-- Get bank account information using bank account numbers from ATM withdrawal log.
SELECT * FROM bank_accounts
WHERE account_number IN (
    SELECT account_number FROM atm_transactions
    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street"
    AND transaction_type = "withdraw"
);
-- Clue: Person IDs associated with bank accounts.

-- Get ID of airport in Fiftyville.
SELECT id FROM airports WHERE city = "Fiftyville"

-- Get the earliest flight leaving Fiftyville on July 29, 2021
SELECT * FROM flights
WHERE origin_airport_id IN (
    SELECT id FROM airports WHERE city = "Fiftyville"
)
AND year = 2021 AND month = 7 AND day = 29
ORDER BY hour LIMIT 1;

-- Get information of all passengers that departed Fiftyville on July 29, 2021.
SELECT * FROM passengers
WHERE flight_id IN (
    SELECT id FROM flights
    WHERE origin_airport_id IN (
        SELECT id FROM airports WHERE city = "Fiftyville"
    )
    AND year = 2021 AND month = 7 AND day = 29
    ORDER BY hour LIMIT 1
);
-- Clue: Passport numbers of all passengers in designated flight.


-- Narrow down suspects using above clues.
SELECT * FROM people
WHERE id IN (
    SELECT person_id FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street"
        AND transaction_type = "withdraw"
    )
)
AND phone_number IN (
    SELECT caller FROM phone_calls
    WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
)
AND license_plate IN (
    SELECT license_plate FROM bakery_security_logs
    WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND activity = "exit"
    ORDER BY id
)
AND passport_number IN (
    SELECT passport_number FROM passengers
    WHERE flight_id IN (
        SELECT id FROM flights
        WHERE origin_airport_id IN (
            SELECT id FROM airports WHERE city = "Fiftyville"
        )
        AND year = 2021 AND month = 7 AND day = 29
        ORDER BY hour LIMIT 1
    )
);

-- Find hideout location.
SELECT * FROM airports
WHERE id IN (
    SELECT destination_airport_id FROM flights
    WHERE id IN (
        SELECT flight_id FROM passengers
        WHERE passport_number IN (
            SELECT passport_number FROM people
            WHERE id IN (
                SELECT person_id FROM bank_accounts
                WHERE account_number IN (
                    SELECT account_number FROM atm_transactions
                    WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street"
                    AND transaction_type = "withdraw"
                )
            )
            AND phone_number IN (
                SELECT caller FROM phone_calls
                WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
            )
            AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND activity = "exit"
                ORDER BY id
            )
            AND passport_number IN (
                SELECT passport_number FROM passengers
                WHERE flight_id IN (
                    SELECT id FROM flights
                    WHERE origin_airport_id IN (
                        SELECT id FROM airports WHERE city = "Fiftyville"
                    )
                    AND year = 2021 AND month = 7 AND day = 29
                    ORDER BY hour LIMIT 1
                )
            )
        )
    )
);

-- Find accomplice.
SELECT * FROM people
WHERE phone_number IN (
    SELECT receiver FROM (
        SELECT * FROM phone_calls
        WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
    )
    WHERE caller IN (
        SELECT phone_number FROM people
        WHERE id IN (
            SELECT person_id FROM bank_accounts
            WHERE account_number IN (
                SELECT account_number FROM atm_transactions
                WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street"
                AND transaction_type = "withdraw"
            )
        )
        AND phone_number IN (
            SELECT caller FROM phone_calls
            WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60
        )
        AND license_plate IN (
            SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND activity = "exit"
            ORDER BY id
        )
        AND passport_number IN (
            SELECT passport_number FROM passengers
            WHERE flight_id IN (
                SELECT id FROM flights
                WHERE origin_airport_id IN (
                    SELECT id FROM airports WHERE city = "Fiftyville"
                )
                AND year = 2021 AND month = 7 AND day = 29
                ORDER BY hour LIMIT 1
            )
        )
    )
);