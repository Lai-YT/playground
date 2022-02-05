import sqlite3
from dataclasses import astuple

from data import Item
from exceptions import ItemAlreadyStoredError, ItemNotStoredError


DB_name = 'sql_db'


def connect_to_db(db=None):
    if db is None:
        mydb = ':memory:'
        print('New connection to in-memory SQLite DB...')
    else:
        mydb = f'{db}.db'
        print('New connection to SQLite DB...')
    return sqlite3.connect(mydb)


def disconnect_from_db(db=None, conn=None):
    if db is not conn:
        print('You are trying to disconnect from a wrong DB')
    if conn is not None:
        conn.close()


def connect(func):
    """Decorator to (re)open a sqlite database connection when needed."""
    def inner_func(conn, *args, **kwargs):
        try:
            conn.execute('SELECT name from sqlite_temp_master WHERE type="table"')
        except (AttributeError, sqlite3.ProgrammingError):
            conn = connect_to_db(DB_name)
        return func(conn, *args, **kwargs)
    return inner_func


@connect
def create_table(conn, table_name):
    sql = '''
        CREATE TABLE {} (rowid INTEGER PRIMARY KEY AUTOINCREMENT,
        name TEXT UNIQUE, price REAL, quantity INTEGER)
        '''.format(table_name)
    try:
        conn.execute(sql)
    except sqlite3.OperationalError as e:
        print(e)


@connect
def insert_one(conn, item, table_name):
    sql = '''
        INSERT INTO {} ('name', 'price', 'quantity') VALUES (?, ?, ?)
        '''.format(table_name)
    try:
        conn.execute(sql, astuple(item))
        conn.commit()
    except sqlite3.IntegrityError as e:
        raise ItemAlreadyStoredError(f'{e}: "{item.name}" already stored in table "{table_name}"')


@connect
def insert_many(conn, items, table_name):
    sql = '''
        INSERT INTO {} ('name', 'price', 'quantity') VALUES (?, ?, ?)
        '''.format(table_name)
    entries = tuple(astuple(item) for item in items)
    try:
        conn.executemany(sql, entries)
        conn.commit()
    except sqlite3.IntegrityError as e:
        print(f'{e}: at least one in {[item.name for item in items]} was already'
              f' stored in table "{table_name}"')


@connect
def select_one(conn, item_name, table_name):
    sql = '''
        SELECT * FROM {} WHERE name=?
        '''.format(table_name)
    cursor = conn.execute(sql, (item_name,))
    result = cursor.fetchone()
    if result is None:
        raise ItemNotStoredError(f'can\'t read "{item_name}" becase it\'s not'
                                 f' stored in table "{table_name}"' )
    return Item(*result[1:])  # exclude row id


@connect
def select_all(conn, table_name):
    sql = '''
        SELECT * FROM {}
        '''.format(table_name)
    cursor = conn.execute(sql)
    results = cursor.fetchall()
    return [Item(*result[1:]) for result in results]


@connect
def update_one(conn, item, table_name):
    sql_check = '''
        SELECT EXISTS(SELECT 1 FROM {} WHERE name=? LIMIT 1)
        '''.format(table_name)
    sql_update = '''
        UPDATE {} SET price=?, quantity=? WHERE name=?
        '''.format(table_name)
    cursor = conn.execute(sql_check, (item.name,))
    result = cursor.fetchone()
    if result[0] == 0:
        raise ItemNotStoredError(f'can\'t update {item.name} because it\'s not stored'
                                 f' in table "{table_name}"')
    cursor.execute(sql_update, (item.price, item.quantity, item.name))
    conn.commit()


@connect
def delete_one(conn, item_name, table_name):
    sql_check = '''
        SELECT EXISTS(SELECT 1 FROM {} WHERE name=? LIMIT 1)
        '''.format(table_name)
    sql_delete = '''
        DELETE FROM {} WHERE name=?
        '''.format(table_name)
    cursor = conn.execute(sql_check, (item_name,))
    result = cursor.fetchone()
    if result[0] == 0:
        raise ItemNotStoredError(f'can\'t delete {item_name} because it\'s not stored'
                                 f' in table "{table_name}"')
    cursor.execute(sql_delete, (item_name,))
    conn.commit()
