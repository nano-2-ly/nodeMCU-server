# Echo server program
import socket
import sqlite3

conn_db = sqlite3.connect('./nodemcu_DB.db')
cs = conn_db.cursor()
query = "CREATE TABLE IF NOT EXISTS data (ip VARCHAR(255), data VARCHAR(255))"
cs.execute(query)
HOST = ''                 # Symbolic name meaning all available interfaces
PORT = 8000            # Arbitrary non-privileged port
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(1)

    while True:
        conn, addr = s.accept()
        print(addr)
        data = conn.recv(1024)
        if not data: break
        print(data)
        conn.sendall(data)
        query = "INSERT into data values (?, ?)"
        cs.execute(query,(addr[0], data.decode()))
        conn_db.commit()