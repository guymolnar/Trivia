import socket

HOST = "127.0.0.1"
PORT = 8826

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    while True:
        data = s.recv(4096)
        print(data.decode())
        msg = input(">> ")
        if msg.lower() == "quit":
            break

        s.sendall(msg.encode())

        print(f"Received: {data.decode()}\n")
