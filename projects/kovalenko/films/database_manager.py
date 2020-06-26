import sqlite3

class DBManager:
    def __init__(self, name = 'films.db'):
        self.con = sqlite3.connect(name)
        self.cur = self.con.cursor()
    
    def get(self, title, genre, yearFrom, yearTo, durationFrom, durationTo, count=10):
        query = 'SELECT Films.id, Films.title, year, genres.title, duration FROM Films JOIN genres ON Films.genre=genres.id'
        query += ' WHERE year BETWEEN {} AND {}'.format(yearFrom, yearTo)
        query += ' AND duration BETWEEN {} AND {}'.format(durationFrom, durationTo)
        if title: query += " AND Films.title like '%{}%'".format(title)
        if genre: query += " AND genre = (SELECT id FROM genres WHERE title='{}')".format(genre)
        return self.cur.execute(query).fetchmany(count)

    def add(self, title, year, genre, duration):
        try:
            print('adding')
            genre = self.getOne("SELECT id FROM genres WHERE title = '{}'".format(genre))
            query = "INSERT INTO Films(title, genre, year, duration) VALUES ('{}', {}, {}, {})".format(title, genre, year, duration)
            return self.cur.execute(query)
        except Exception as e:
            print(e)

    def delete(self, id):
        return self.cur.execute("DELETE FROM Films WHERE id = {}".format(id))

    def update(self, id, title, year, genre, duration):
        genre = self.getOne("SELECT id FROM genres WHERE title = '{}'".format(genre))
        query = "UPDATE Films SET title = '{}', genre = '{}', year = {}, duration = {} WHERE id = {}".format(title, genre, year, duration, id)
        return self.cur.execute(query)

    def getInitValues(self):
        minYear = self.getOne("SELECT MIN(year) FROM Films")
        maxYear = self.getOne("SELECT MAX(year) FROM Films")
        minDuration = 0
        maxDuration = self.getOne("SELECT MAX(duration) FROM Films WHERE NOT duration = ''")
        return map(int, (minYear, maxYear, minDuration, maxDuration))

    def getGenres(self):
        result = self.cur.execute("SELECT title FROM genres")
        return (el[0] for el in result)

    def getOne(self, query):
        return self.cur.execute(query).fetchall()[0][0]

    def close(self):
        self.con.close()

if __name__ == '__main__':
    manager = DBManager()

    manager.add('Коваленко человек', 'драма', 2020, 200)