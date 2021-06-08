SELECT DISTINCT people.name FROM people
JOIN directors on people.id = directors.person_id 
JOIN movies on movies.id = directors.movie_id 
JOIN ratings on movies.id = ratings.movie_id
WHERE ratings.rating >= "9.0"
GROUP BY directors.person_id;
