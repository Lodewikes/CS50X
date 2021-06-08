-- Keep a log of any SQL queries you execute as you solve the mystery.

-- crime scene full display
SELECT * FROM crime_scene_reports WHERE day = "28" AND month = "7" AND year = "2020" AND street = "Chamberlin Street"; 
-- happened at 10: 15 at courthouse

-- interviews
SELECT transcript FROM interviews WHERE day = "28" AND month = "7" AND year = "2020" like "%courthouse%"; 
-- thief left within 10 min of the crime.
-- Thief drew money from atm 
-- made a 1min call
-- plan to fly out of fiftyvile

-- courthouse security logs
-- SELECT activity FROM courthouse_security_logs; -- bad idea

-- get names of people leaving withing that 10 min time frame
SELECT name FROM people 
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate 
WHERE day = "28" AND month="7" AND year="2020" AND hour="10" AND minute >= "15"
AND minute < 25 AND activity= "exit";

-- Patrick (sus)
-- Ernest (sus)
-- Amber (sus)
-- Danielle (sus)
-- Roger (sus)
-- Elizabeth (sus)
-- Russell (sus)
-- Evelyn (sus)

-- See who withdrew money
SELECT DISTINCT name FROM people 
JOIN bank_accounts ON people.id = bank_accounts.person_id 
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number 
WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" 
AND atm_location = "Fifer Street";

-- Danielle (sus)
-- Bobby
-- Madison
-- Ernest (sus)
-- Roy
-- Elizabeth (sus)
-- Victoria
-- Russell (sus)

-- see who made a call
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller 
WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60";
-- Roger
-- Evelyn
-- Ernest (sus)
-- Evelyn
-- Madison
-- Russell (sus)
-- Kimberly
-- Bobby
-- Victoria

-- who flew?
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number 
WHERE flight_id = (
		SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" 
		ORDER BY hour, minute LIMIT 1
);

-- Doris
-- Roger
-- Ernest (sus)
-- Edward
-- Evelyn
-- Madison
-- Bobby
-- Danielle

-- Ernest was everywhere. (Thief)

-- find destination of the flight
SELECT city FROM airports WHERE id = (
		SELECT destination_airport_id FROM flights 
		WHERE day = "29" AND month = "7" AND year = "2020" 
		ORDER BY hour, minute LIMIT 1
);
-- to London bruv, innit! (destination)

-- who did he call?
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller = (
		SELECT phone_number FROM people WHERE name = "Ernest"
);

-- he called Berthold (accomplice)
