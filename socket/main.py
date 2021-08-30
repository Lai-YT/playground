import logging
import threading
import time

from client import Client, ClientHeartbeat
from server import EchoServer


def run_server():
    server = EchoServer()
    server.run()


def run_client():
    client = Client()
    time.sleep(1)  # wait for connection
    client.run()


def run_client_heartbeat(period):
    client = ClientHeartbeat()
    time.sleep(1)  # wait for connection
    client.run(period)


if __name__ == '__main__':
    logging.basicConfig(format='%(message)s', level=logging.INFO)

    server_thread = threading.Thread(target=run_server)
    server_thread.start()
    time.sleep(1)  # make sure server is running before client try to connect

    client_thread = threading.Thread(target=run_client)
    client_thread.start()
    time.sleep(1)

    # Comment out since can't connect multiple clients at once.
    # client_heartbeat_thread = threading.Thread(target=run_client_heartbeat, args=(1,))
    # client_heartbeat_thread.start()
    # client_heartbeat_thread.join()

    server_thread.join()
    client_thread.join()
