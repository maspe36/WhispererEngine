# Import socket module
import socket               

# Create a socket object
s = socket.socket()         

# Define the port on which you want to connect
port = 8888                

# connect to the server on local computer
s.connect(('74.208.200.101', port))

# receive data from the server
while 1:
	print(s.recv(1024))
	s.sendall(b'We got it pal!\n')
# close the connection
#s.close()      