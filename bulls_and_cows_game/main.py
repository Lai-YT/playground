import random

from player_io import PlayerConsole


class BullsAndCowsGame:
    def __init__(self, secret, io):
        self._secret = secret
        self._io = io
        self._is_done = False
        self._guess = None
        self._records = []

    def start(self):
        while not self._is_done:
            self._guess = self._io.read_guess()
            self._match_guess_with_secret()
            self._io.write_records(self._records)
        self._io.write_congrats()

    def _match_guess_with_secret(self):
        a = 0
        b = 0
        for i in range(4):
            if self._is_right_position(i):
                a += 1
            elif self._is_right_digit(i):
                b += 1
        if self._is_full_matched():
            self._is_done = True
        self._record_guess_with_match(a, b)

    def _record_guess_with_match(self, a, b):
        match_ = ''
        if a != 0:
            match_ += f'{a}A'
        if b != 0:
            match_ += f'{b}B'
        if not match_:
            match_ = '0'
        self._records.append({'guess': self._guess, 'match': match_})

    def _is_right_position(self, pos):
        return self._guess[pos] == self._secret[pos]

    def _is_right_digit(self, pos):
        return self._guess[pos] in self._secret

    def _is_full_matched(self):
        return self._guess == self._secret


def generate_secret():
    secret = random.sample('0123456789', k=4)
    random.shuffle(secret)
    return ''.join(secret)


def main():
    secret = generate_secret()
    game = BullsAndCowsGame(secret=secret, io=PlayerConsole())
    game.start()


if __name__ == '__main__':
    main()
