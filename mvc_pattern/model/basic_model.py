import backend.basic_backend as backend
from model.model_interface import ModelInterface


class BasicModel(ModelInterface):
    def __init__(self, app_items=None):
        self._item_type = 'product'
        if app_items is not None:
            self.create_items(app_items)

    @property
    def item_type(self):
        return self._item_type

    @item_type.setter
    def item_type(self, new_item_type):
        self._item_type = new_item_type

    def create_item(self, item):
        backend.create_item(item)

    def create_items(self, items):
        backend.create_items(items)

    def read_item(self, name):
        return backend.read_item(name)

    def read_items(self):
        return backend.read_items()

    def update_item(self, item):
        backend.update_item(item)

    def delete_item(self, name):
        backend.delete_item(name)
