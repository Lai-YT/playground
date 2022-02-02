import backend
from data import Item


def main():

    print('--- create ---')
    backend.create_items(
        [
            Item('bread', 0.5, 20),
            Item('milk', 1.0, 10),
            Item('wine', 10.0, 5),
        ]
    )
    backend.create_item(Item('beer', 3.0, 15))

    print('--- read ---')
    print(backend.read_items())
    print(backend.read_item('bread'))

    print('--- update ---')
    backend.update_item(Item('bread', 2.0, 30))
    print(backend.read_item('bread'))

    print('--- delete ---')
    backend.delete_item('beer')
    print(backend.read_items())


if __name__ == '__main__':
    main()
