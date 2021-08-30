import logging
import socket

HOST = '0.0.0.0'
PORT = 7_000
BUFFSIZE = 1024


class EchoServer:
    """This server sends back what it receives from the client."""

    def __init__(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.bind((HOST, PORT))
        self._socket.listen(5)

        logging.info(f'server: start at: {HOST}:{PORT}')

    def run(self):
        logging.info('wait for connection...')

        while True:
            conn, addr = self._socket.accept()
            logging.info(f'server: connected by ' + str(addr))

            while True:
                in_data = conn.recv(BUFFSIZE)
                if len(in_data) == 0:
                    conn.close()
                    logging.info('server: client closed connection.')
                    break
                logging.info('server: recv ' + in_data.decode())

                out_data = 'echo ' + in_data.decode()
                conn.send(out_data.encode())
