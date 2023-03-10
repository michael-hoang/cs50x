SELECT DISTINCT people.name
FROM people JOIN stars ON people.id = stars.person_id
            JOIN movies on stars.movie_id = movies.id
WHERE movies.id IN (SELECT movie_id
            FROM people JOIN stars ON people.id = stars.person_id
                        JOIN movies ON stars.movie_id = movies.id
            WHERE people.name == 'Kevin Bacon' AND people.birth = 1958
        )
AND people.id NOT IN (SELECT DISTINCT people.id
            FROM people JOIN stars ON people.id = stars.person_id
                        JOIN movies ON stars.movie_id = movies.id
            WHERE people.name = 'Kevin Bacon' AND people.birth = 1958
        );