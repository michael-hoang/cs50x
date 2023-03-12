import csv

from cs50 import SQL

db = SQL('sqlite:///roster.db')
with open('students.csv') as f:
    reader = csv.DictReader(f)
    houses = []
    for row in reader:
        student_name = row['student_name']
        house_name = row['house']
        db.execute('INSERT INTO students (student_name) VALUES (?)', student_name)
        if house_name not in houses:
            db.execute('INSERT INTO houses (house_name) VALUES (?)', house_name)
            houses.append(house_name)

        student_id = db.execute('SELECT id FROM students WHERE student_name = ?', student_name)[0]['id']
        house_id = db.execute('SELECT id FROM houses WHERE house_name = ?', house_name)[0]['id']
        db.execute('INSERT INTO house_assignments (students_id, houses_id) VALUES (?, ?)', student_id, house_id)
        