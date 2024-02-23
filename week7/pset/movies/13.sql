SELECT DISTINCT(name) FROM people
WHERE id IN
(
    SELECT person_id FROM stars
    WHERE movie_id IN
    (
        SELECT movies.id FROM people
        JOIN stars ON stars.person_id = people.id
        JOIN movies ON stars.movie_id = movies.id
        WHERE people.name =
        (
            SELECT name FROM people
            WHERE name = 'Kevin Bacon' and birth = 1958
        )
    )
)
AND name != 'Kevin Bacon';