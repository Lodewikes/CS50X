-- Dink reg, maar kyk count
-- NOT FINISHED
SELECT DISTINCT people.name FROM people 
JOIN stars ON stars.person_id = people.id 
JOIN movies ON movies.id = stars.movie_id 
WHERE movies.year = "2004"
AND stars.person_id IN (SELECT DISTINCT people.id FROM people)
GROUP BY people.id
ORDER BY people.birth;

