import socket
import json

LOGIN_REQUEST_CODE = 1
SIGNUP_REQUEST_CODE = 2

HOST = "127.0.0.1"
PORT = 8826


def build_packet(code, payload):
    body = json.dumps(payload).encode("utf-8")
    return bytes([code]) + len(body).to_bytes(4, byteorder='big') + body


def send_request(code, payload):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        s.sendall(build_packet(code, payload))
        data = s.recv(4096)
        print(f"[code={code}] sent: {payload}")
        print(f"raw response ({len(data)} bytes): {data!r}")
        try:
            print("decoded:", data.decode("utf-8"))
        except UnicodeDecodeError:
            pass


if __name__ == "__main__":
    #send_request(LOGIN_REQUEST_CODE, {"username": "guy", "password": "1234"})
    send_request(SIGNUP_REQUEST_CODE, {"username": "guy", "password": "1234", "mail": "a@b.com"})