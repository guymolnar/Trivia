import socket
import json
import struct

LOGIN_REQUEST_CODE = 1
SIGNUP_REQUEST_CODE = 2

HOST = "127.0.0.1"
PORT = 8826


def validate_username(username):
    if not username:
        raise ValueError("Username cannot be empty")
    if not username.isalnum():
        raise ValueError("Username must contain only letters and numbers")


def build_packet(code, payload):
    body = json.dumps(payload).encode("utf-8")
    return bytes([code]) + len(body).to_bytes(4, byteorder='big') + body


def parse_response(data):
    if len(data) < 5:
        return None, None
    code = data[0]
    length = int.from_bytes(data[1:5], byteorder='big')
    body = data[5:5 + length]
    try:
        return code, json.loads(body.decode("utf-8"))
    except Exception:
        return code, None


def send_request(code, payload, label):
    print(f"\n--- {label} ---")
    print(f"Sending: {payload}")
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((HOST, PORT))
            # Hello handshake

            s.sendall(build_packet(code, payload))
            data = s.recv(4096)
            code_resp, body = parse_response(data)
            print(f"Response code: {code_resp}, body: {body}")
            return body
        except ConnectionRefusedError:
            print("ERROR: Could not connect to server")
            return None


if __name__ == "__main__":
    # Test 1: signup new user
    send_request(SIGNUP_REQUEST_CODE,
                 {"username": "guy", "password": "1234", "mail": "guy@test.com"},
                 "Signup new user (should succeed)")

    # Test 2: signup same username again
    send_request(SIGNUP_REQUEST_CODE,
                 {"username": "guy", "password": "5678", "mail": "guy2@test.com"},
                 "Signup duplicate username (should fail)")

    # Test 3: login with correct credentials
    send_request(LOGIN_REQUEST_CODE,
                 {"username": "guy", "password": "1234"},
                 "Login correct credentials (should succeed)")

    # Test 4: login user already logged in
    send_request(LOGIN_REQUEST_CODE,
                 {"username": "guy", "password": "1234"},
                 "Login already logged in (should fail)")

    # Test 5: login user that doesn't exist
    send_request(LOGIN_REQUEST_CODE,
                 {"username": "ghost", "password": "1234"},
                 "Login non-existent user (should fail)")

    # Test 6: input validation - empty username
    try:
        validate_username("")
    except ValueError as e:
        print(f"\n--- Input validation: empty username ---\nCaught: {e}")

    # Test 7: input validation - username with special chars
    try:
        validate_username("guy@#!")
    except ValueError as e:
        print(f"\n--- Input validation: special chars ---\nCaught: {e}")
