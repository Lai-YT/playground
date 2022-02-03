from abc import ABC, abstractmethod


class ModelInterface(ABC):
    @abstractmethod
    def __init__(self, app_items=None):
        pass

    @property
    @abstractmethod
    def item_type(self):
        pass

    @item_type.setter
    @abstractmethod
    def item_type(self, new_item_type):
        pass

    @abstractmethod
    def create_item(self, item):
        pass

    @abstractmethod
    def create_items(self, items):
        pass

    @abstractmethod
    def read_item(self, name):
        pass

    @abstractmethod
    def read_items(self):
        pass

    @abstractmethod
    def update_item(self, item):
        pass

    @abstractmethod
    def delete_item(self, name):
        pass
