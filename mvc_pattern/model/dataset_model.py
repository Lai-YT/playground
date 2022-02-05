import backend.dataset_backend as backend
from model.model_interface import ModelInterface


# NOTE: the only difference between SQLiteModel is the backend
class DatasetModel(ModelInterface):
    def __init__(self, app_items=None):
        self._item_type = 'product'
        self._connection = backend.connect_to_db(backend.DB_name)
        # item_type is the table name
        backend.create_table(self._connection, self._item_type)
        if app_items is not None:
            self.create_items(app_items)

    @property
    def connection(self):
        return self._connection

    @property
    def item_type(self):
        return self._item_type

    @item_type.setter
    def item_type(self, new_item_type):
        self._item_type = new_item_type

    def create_item(self, item):
        backend.insert_one(self._connection, item, self._item_type)

    def create_items(self, items):
        backend.insert_many(self._connection, items, self._item_type)

    def read_item(self, name):
        return backend.select_one(self._connection, name, self._item_type)

    def read_items(self):
        return backend.select_all(self._connection, self._item_type)

    def update_item(self, item):
        backend.update_one(self._connection, item, self._item_type)

    def delete_item(self, name):
        backend.delete_one(self._connection, name, self._item_type)
