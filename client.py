import sys
import socket
import threading
import argparse

ENCODING = "utf-8"
LOCAL_ENDPOINT = "127.0.0.1"
REMOTE_ENDPOINT = "74.208.200.101"

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

parser = argparse.ArgumentParser()
parser.add_argument('--remote', action='store_true')
args = parser.parse_args()

if args.remote:
    print("Attempting to connect to the remote...")
    ENDPOINT = REMOTE_ENDPOINT
else:
    print("Attempting to connect to the localhost...")
    ENDPOINT = LOCAL_ENDPOINT

sock = socket.socket()
port = 8888

sock.connect((ENDPOINT, port))

threading.Thread(target=listen).start()
threading.Thread(target=listen_to_keypress).start()
