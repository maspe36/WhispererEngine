import sys
import socket
import threading


ENCODING = "utf-8"

def listen():
    while 1:
        data = sock.recv(4096)
        if data:
            print(data.decode(ENCODING))
        else:
            print('\nDisconnected from server')
            sys.exit()


def listen_to_keypress():
    while 1:
        message = input("Enter text (or Enter to quit): \n")
        if not message:
            break

        sock.sendall((message + "\n").encode(ENCODING))


sock = socket.socket()
port = 8888

# sock.connect(("74.208.200.101", port))
sock.connect(("127.0.0.1", port))

threading.Thread(target=listen).start()
threading.Thread(target=listen_to_keypress).start()
