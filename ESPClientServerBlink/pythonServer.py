import time
import socket

# creating a socket object
s = socket.socket(socket.AF_INET,
                  socket.SOCK_STREAM)

# get local Host machine name
host = '' # or just use (host == '')
port = 9999

print("creating server at " + host + " " + str(port))
# bind to pot
s.bind((host, port))

# Que up to 5 requests
s.listen(5)
while True:
    print("Waiting for clients")
    conn, addr = s.accept()
    print("got a connection from %s" % str(addr))
    while True:
        # establish connection
        data = conn.recv(1024)
        #sends data back to the client
        print("got " + data + "from client " + str(addr))
        conn.sendall(data);
        if not data:
            break
        #else:

