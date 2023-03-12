CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER,
    house_name TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE house_assignments (
    students_id INTEGER,
    houses_id INTEGER,
    FOREIGN KEY(students_id) REFERENCES students (id),
    FOREIGN KEY(houses_id) REFERENCES houses (id)
);