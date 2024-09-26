SELECT name FROM movies, directors, people, ratings WHERE movies.id = directors.movie_id AND directors.person_id = people.id AND ratings.movie_id = movies.id AND ratings.rating >= 9.0;
