import logging
import socket
import time

from server import BUFFSIZE, HOST, PORT


class Client:
    def __init__(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.connect((HOST, PORT))

    def run(self):
        while True:
            out_data = input('client: please input message: ')
            logging.info('client: send ' + out_data)
            self._socket.send(out_data.encode())

            in_data = self._socket.recv(BUFFSIZE)
            if len(in_data) == 0:
                self._socket.close()
                logging.info('client: server closed connection')
                break
            logging.info('client: recv ' + in_data.decode())


class ClientHeartbeat:
    """Automatically sends every second."""
    def __init__(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._socket.connect((HOST, PORT))

    def run(self, period):
        while True:
            out_data = 'heartbeat'
            logging.info('client heartbeat: send ' + out_data)
            self._socket.send(out_data.encode())

            in_data = self._socket.recv(BUFFSIZE)
            if len(in_data) == 0:
                self._socket.close()
                logging.info('client heartbeat: server closed connection.')
                break
            logging.info('client heartbeat: recv ' + in_data.decode())

            time.sleep(period)
