-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To get some information about the crime
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street' AND year = 2021 AND day = 28 AND month = '7';

/*
    Description
    Street: Humphrey Street, Day = 28, Month = 7, Year = 2021, crime_id = 295
    Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
    Interviews were conducted today with three witnesses who were present at the time.
    Each of their interview transcripts mentions the bakery.
*/

-- To get information from the interviewees
SELECT * FROM interviews WHERE year = 2021 AND day = 28 AND month = '7';

/*
    Data collected
    From: Ruth, interview_id = 161
    Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
    If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

    From: Eugene, interview_id = 162
    I don't know the thief's name, but it was someone I recognized.
    Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

    From: Raymond, interview_id = 163
    As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
    In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
    The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

-- According to Ruth: To know who was in the parking lot this day
SELECT DISTINCT(name) FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021 AND day = 28 AND month = '7';

/*
    Who were in the parking lot that day
    +---------+
    |  name   |
    +---------+
    | Alice   |
    | Peter   |
    | Rachel  |
    | Debra   |
    | Wayne   |
    | Jordan  |
    | Iman    |
    | Bruce   |
    | George  |
    | Michael |
    | Taylor  |
    | Andrew  |
    | Diana   |
    | Ralph   |
    | Kelsey  |
    | Joshua  |
    | Carolyn |
    | Robin   |
    | Donna   |
    | Martha  |
    | Luca    |
    | Vanessa |
    | Barry   |
    | Sofia   |
    | Brandon |
    | Sophia  |
    | Denise  |
    | Thomas  |
    | Jeremy  |
    | Judith  |
    | Mary    |
    | Vincent |
    | Daniel  |
    | Frank   |
    | Amanda  |
    | John    |
    | Ethan   |
    +---------+
*/

-- According to Eugene: Let's see who was withdrawing some money from an  ATM on Leggett Street from the people who was in the parking lot
SELECT DISTINCT(name) FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.day = 28 AND bakery_security_logs.month = '7'
AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.year = 2021
AND atm_transactions.day = 28 AND atm_transactions.month = '7';
/*
    People who were in the parking lot and did an atm_transaction at Leggett Street that day's morning
    +--------+
    |  name  |
    +--------+
    | Luca   |
    | Taylor |
    | Bruce  |
    | Iman   |
    | Diana  |
    +--------+
*/

-- According to Raymond: Let's compine all of those with a phone call was done that day the duration was less than a minute
SELECT DISTINCT(name) FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.day = 28 AND bakery_security_logs.month = '7'
AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.year = 2021
AND atm_transactions.day = 28 AND atm_transactions.month = '7'
AND phone_calls.duration < 60;

/*
    +--------+
    |  name  |
    +--------+
    | Taylor |
    | Bruce  |
    | Diana  |
    +--------+
*/

-- Let's find out who of those were on a flight going out from Fiftyville
SELECT DISTINCT(name) FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7
AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.year = 2021
AND atm_transactions.day = 28 AND atm_transactions.month = 7
AND phone_calls.duration < 60
AND airports.city = 'Fiftyville'
AND flights.day = 29 AND flights.month = 7 AND flights.year = 2021;

/*
    Wow! All of them were on a flight that day
    +--------+
    |  name  |
    +--------+
    | Bruce  |
    | Diana  |
    | Taylor |
    +--------+
*/

-- Let's see who were on the earliest flight
SELECT DISTINCT(name), flights.hour, flights.minute FROM people
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
JOIN phone_calls ON phone_calls.caller = people.phone_number
JOIN passengers ON passengers.passport_number = people.passport_number
JOIN flights ON flights.id = passengers.flight_id
JOIN airports ON airports.id = flights.origin_airport_id
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7
AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.year = 2021
AND atm_transactions.day = 28 AND atm_transactions.month = 7
AND phone_calls.duration < 60
AND airports.city = 'Fiftyville'
AND flights.day = 29 AND flights.month = 7 AND flights.year = 2021
ORDER BY flights.hour;

/*
    We Down to two.
    +--------+------+--------+
    |  name  | hour | minute |
    +--------+------+--------+
    | Bruce  | 8    | 20     |
    | Taylor | 8    | 20     |
    | Diana  | 16   | 0      |
    +--------+------+--------+
*/

/*
    According to Ruth: The car stayed in the parking lot for less than ten minute.
    Let's see the duration both Bruce and Taylor take between the theift and moving from the parking lot.
*/
-- For Bruce
SELECT hour, minute, activity FROM bakery_security_logs
WHERE license_plate =
(
    SELECT license_plate FROM people
    WHERE name = 'Bruce'
)
AND day = 28 AND year = 2021 AND month = 7;
/*
    +------+--------+----------+
    | hour | minute | activity |
    +------+--------+----------+
    | 8    | 23     | entrance |
    | 10   | 18     | exit     |
    +------+--------+----------+
*/
-- So, Bruce left after the crime by 3 minutes

-- For Taylor
SELECT hour, minute, activity FROM bakery_security_logs
WHERE license_plate =
(
    SELECT license_plate FROM people
    WHERE name = 'Taylor'
)
AND day = 28 AND year = 2021 AND month = 7;
/*
    +------+--------+----------+
    | hour | minute | activity |
    +------+--------+----------+
    | 8    | 34     | entrance |
    | 10   | 35     | exit     |
    +------+--------+----------+
*/
-- So, Taylor left after the crime by 20 minutes

/*
    Finaly, We know that the theif was Bruce
    Let's find out where he was escaping to and who is the accomplice.
*/

-- Where Bruce was heading to
SELECT city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
JOIN passengers ON passengers.flight_id = flights.id
JOIN people ON people.passport_number = passengers.passport_number
WHERE people.name = 'Bruce';
/*
    So, He was heading to New York City
    +---------------+
    |     city      |
    +---------------+
    | New York City |
    +---------------+
*/

-- The accomplice Who Bruce called him after the crime
SELECT name FROM people
JOIN phone_calls ON phone_calls.receiver = people.phone_number
WHERE phone_calls.caller =
(
    SELECT phone_number FROM people
    WHERE name = 'Bruce'
)
AND phone_calls.year = 2021 AND phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 60;
/*
    So, the accomplice was Robin
    +-------+
    | name  |
    +-------+
    | Robin |
    +-------+
*/