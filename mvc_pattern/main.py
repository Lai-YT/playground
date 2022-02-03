import backend.sqlite_backend as sql
from controller import Controller
from data import Item
from model.basic_model import BasicModel
from view import View


def basic_main():

    cont = Controller(
        BasicModel(
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


def sqlite_main():
    table_name = 'items'
    conn = sql.connect_to_db()

    sql.create_table(conn, table_name)

    print('--- create ---')
    sql.insert_many(
        conn,
        [
            Item('bread', 0.5, 20),
            Item('milk', 1.0, 10),
            Item('wine', 10.0, 5),
        ],
        table_name
    )
    sql.insert_one(conn, Item('beer', 2.0, 5), table_name)

    print('--- read ---')
    print(sql.select_one(conn, 'milk', table_name))
    print(sql.select_all(conn, table_name))

    print('--- update ---')
    sql.update_one(conn, Item('bread', 1.5, 5), table_name)
    print(sql.select_one(conn, 'bread', table_name))


    print('--- delete ---')
    sql.delete_one(conn, 'beer', table_name)
    print(sql.select_all(conn, table_name))


if __name__ == '__main__':
    sqlite_main()
