import sys

import dataset

from controller import Controller
from data import Item
from model import BasicModel, DatasetModel, SQLiteModel
from view import View


def client_code(model_type):
    """When using MVC pattern, things work the same."""

    cont = Controller(
        model_type(
            [
                Item('bread', 0.5, 20),
                Item('milk', 1.0, 10),
                Item('wine', 10.0, 5),
            ]
        ),
        View()
    )

    cont.show_items()
    cont.show_items(bullet_point=True)

    cont.show_item('bread')
    cont.show_item('chocolate')

    cont.insert_item(Item('chocolate', 2.0, 10))
    cont.insert_item(Item('bread', 1.0, 5))

    cont.update_item(Item('milk', 1.2, 20))
    cont.update_item(Item('ice cream', 3.5, 20))

    cont.delete_item('bread')
    cont.delete_item('fish')

    cont.show_items()


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('please specify which model to use: basic | dataset | sqlite')
    elif sys.argv[1] == 'basic':
        client_code(BasicModel)
    elif sys.argv[1] == 'dataset':
        client_code(DatasetModel)
    elif sys.argv[1] == 'sqlite':
        client_code(SQLiteModel)
    else:
        print('please specify which model to use: basic | dataset | sqlite')
