SELECT people.name FROM people
WHERE people.id IN (
    SELECT DISTINCT directors.person_id
    FROM directors JOIN ratings ON directors.movie_id = ratings.movie_id
    WHERE ratings.rating >= 9.0
    );