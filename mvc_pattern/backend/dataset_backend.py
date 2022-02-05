from dataclasses import asdict

import dataset
from sqlalchemy.exc import IntegrityError

from data import Item
from exceptions import ItemAlreadyStoredError, ItemNotStoredError


DB_name = 'dataset_db'


def connect_to_db(db=None):
    if db is None:
        mydb = ':memory:'
        print('New connection to in-memory SQLite DB...')
    else:
        mydb = f'{db}.db'
        print('New connection to SQLite DB...')
    return dataset.connect(f'sqlite:///{mydb}')


def create_table(conn, table_name):
    if not conn.has_table(table_name):
        print(f'table {table_name} does not exist; it will be created now')
        conn.create_table(table_name, primary_id='name', primary_type=conn.types.text)
        print(f'created table {table_name} on database')


def insert_one(conn, item, table_name):
    table = conn.load_table(table_name)
    try:
        table.insert(asdict(item))
    except IntegrityError as e:
        raise ItemAlreadyStoredError(f'{e}: "{item.name}" already stored in table "{table_name}"')


def insert_many(conn, items, table_name):
    table = conn.load_table(table_name)
    try:
        # the items before exception are inserted
        for item in items:
            table.insert(asdict(item))
    except IntegrityError as e:
        print(f'{e}: at least one in {[item.name for item in items]} was already'
              f' stored in table "{table_name}"')


def select_one(conn, item_name, table_name):
    table = conn.load_table(table_name)
    result = table.find_one(name=item_name)  # type: OrderedDict
    if result is None:
        raise ItemNotStoredError(f'can\'t read "{item_name}" becase it\'s not'
                                 f' stored in table "{table_name}"' )
    return Item(**result)


def select_all(conn, table_name):
    table = conn.load_table(table_name)
    results = table.all()
    return [Item(**result) for result in results]


def update_one(conn, item, table_name):
    table = conn.load_table(table_name)
    result = table.find_one(name=item.name)
    if result is None:
        raise ItemNotStoredError(f'can\'t update {item.name} because it\'s not stored'
                                 f' in table "{table_name}"')
    table.update(asdict(item), keys=['name'])


def delete_one(conn, item_name, table_name):
    table = conn.load_table(table_name)
    result = table.find_one(name=item_name)
    if result is None:
        raise ItemNotStoredError(f'can\'t delete {item_name} because it\'s not stored'
                                 f' in table "{table_name}"')
    table.delete(name=item_name)
