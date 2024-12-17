import socket

class UDPSocket:
    def __init__(self, timeout=5):
        """Initialize the UDP socket with a configurable timeout."""
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(timeout)

    def close(self):
        """Close the socket explicitly."""
        self.sock.close()

    def send_datagram(self, msg: bytes, address: tuple):
        """Send a UDP datagram to the specified address."""
        try:
            bytes_sent = self.sock.sendto(msg, address)
            return bytes_sent
        except socket.timeout:
            print("Error: Connection timed out.")
            return -1
        except Exception as e:
            print(f"Error sending datagram [{type(e).__name__}]: {e}")
            return -1

    def recv_datagram(self, bufsize: int):
        """Receive a UDP datagram."""
        try:
            data, addr = self.sock.recvfrom(bufsize)
            return data, addr
        except socket.timeout:
            print("Timeout: No response from server.")
            return None, None
        except Exception as e:
            print(f"Error receiving datagram [{type(e).__name__}]: {e}")
            return None, None

if __name__ == "__main__":
    SERVER = "127.0.0.1"
    PORT = 8888
    BUFLEN = 1024

    print(f"Ensure the server is running at {SERVER}:{PORT}")
    client_sock = UDPSocket()
    server_address = (SERVER, PORT)

    print(f"Client initialized. Server address: {SERVER}, port: {PORT}")

    try:
        while True:
            message = input("Enter message (or type 'exit' to quit): ").strip()
            if message.lower() == "exit":
                print("Client shutting down.")
                break

            if not message:
                print("Please enter a non-empty message.")
                continue

            bytes_sent = client_sock.send_datagram(message.encode(), server_address)
            if bytes_sent == -1:
                print("Failed to send message.")
                continue

            data, _ = client_sock.recv_datagram(BUFLEN)
            if data:
                print(f"Received from server: {data.decode()}")
            else:
                print("No response from server.")

    except KeyboardInterrupt:
        print("\nClient interrupted. Shutting down.")

    finally:
        client_sock.close()
        print("Socket closed.")
