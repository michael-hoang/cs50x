SELECT AVG(rating) FROM (
    SELECT movies.year, ratings.rating
    FROM movies JOIN ratings
    ON movies.id = ratings.movie_id
    WHERE movies.year = 2012
);