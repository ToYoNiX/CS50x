SELECT DISTINCT(name) FROM people, stars
WHERE stars.person_id = people.id AND movie_id IN (
    SELECT movie_id FROM people, stars
    WHERE people.id = stars.person_id AND name = 'Kevin Bacon' and birth = 1958
) AND name != 'Kevin Bacon';
