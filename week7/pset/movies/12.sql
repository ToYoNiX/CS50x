SELECT title FROM movies WHERE id in (
    SELECT movie_id FROM people, stars
    WHERE people.id = stars.person_id AND people.name = 'Jennifer Lawrence' AND movie_id IN (
        SELECT movie_id FROM people, stars
        WHERE people.id = stars.person_id AND people.name = 'Bradley Cooper'
    )
);
