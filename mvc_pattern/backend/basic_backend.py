from copy import deepcopy

from data import Item
from exceptions import ItemAlreadyStoredError, ItemNotStoredError


# global data storage
_item_base = []


def _find_item(name):
    item = list(filter(lambda x: x.name == name, _item_base))
    if item:
        return item[0]
    return None


def _already_stored(name):
    return _find_item(name) is not None


def create_item(item):
    if _already_stored(item.name):
        raise ItemAlreadyStoredError(f'"{item.name}" already stored!')
    _item_base.append(item)


def create_items(items):
    for item in items:
        create_item(item)


def read_item(name):
    item = _find_item(name)
    if item is None:
        raise ItemNotStoredError(f'Can\'t read "{name}" because it\'s not stored')
    return deepcopy(item)


def read_items():
    return deepcopy(_item_base)


def update_item(item):
    old_item = _find_item(item.name)
    if old_item is None:
        raise ItemNotStoredError(f'Can\'t update "{item.name}" because it\'s not stored')
    old_item.price, old_item.quantity = item.price, item.quantity


def delete_item(name):
    item = _find_item(name)
    if item is None:
        raise ItemNotStoredError(f'Can\'t delete "{name}" because it\'s not stored')
    _item_base.remove(item)
