import sqlite3 as lite
import time

database_filename = 'nodemcu_DB.db'
conn = lite.connect(database_filename)
cs = conn.cursor()

query = "SELECT * FROM data;"
cs.execute(query)
all_rows = cs.fetchall()

print(all_rows)