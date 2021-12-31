import random
import time
from queue import Queue


class Producer:
    def __init__(self, queue: Queue) -> None:
        self._queue = queue

    def send(self, amount: int) -> None:
        """Sends random number [1, 100] to the queue after
        random delay time (0, 1.0].
        """
        for _ in range(amount):
            time.sleep(random.random())
            self._queue.put(random.randint(1, 100))
