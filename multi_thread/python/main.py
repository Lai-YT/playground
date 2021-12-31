import threading
from queue import PriorityQueue
from typing import List

from consumer import Consumer
from producer import Producer


def main() -> None:
    queue = PriorityQueue()

    # create consumer and producers
    producers: List[Producer] = []
    for _ in range(3):
        producers.append(Producer(queue))
    consumer = Consumer(queue)
    
    # create threads
    produce_threads: List[threading.Thread] = []
    for producer in producers:
        thread = threading.Thread(target=producer.send, args=(3,))
        produce_threads.append(thread)
    consume_thread = threading.Thread(target=consumer.recieve, args=(9,))

    # start and join threads
    for thread in produce_threads:
        thread.start()
        thread.join()
    consume_thread.start()
    consume_thread.join()

    print(consumer.consume_list)


if __name__ == '__main__':
    main()
