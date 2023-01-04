from abc import ABC, abstractmethod


class PlayerIO(ABC):
    @abstractmethod
    def read_guess(self):
        pass

    @abstractmethod
    def write_records(self, records):
        pass

    @abstractmethod
    def write_congrats(self):
        """Writes the congratulation message for a right guess."""


class PlayerConsole(PlayerIO):
    def read_guess(self):
        return input('Please input a 4-digit number: ')

    def write_records(self, records):
        for i, record in enumerate(records):
            print(f'{i + 1:02d}: {record["guess"]} -> {record["match"]}')
        print()

    def write_congrats(self):
        # go to the (start of the) previous line to discard blank line
        print('\033[F', end='')
        print("Congratulation! You've got the number!")
