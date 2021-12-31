from queue import Queue
from typing import List


class Consumer:
    def __init__(self, queue: Queue) -> None:
        self._queue = queue
        self._consume_list = []

    @property
    def consume_list(self) -> List:
        return self._consume_list

    def recieve(self, amount: int) -> None:
        for _ in range(amount):
            g = self._queue.get()
            self._consume_list.append(g)
            self._queue.task_done()
