from exceptions import ItemAlreadyStoredError, ItemNotStoredError


class Controller:
    def __init__(self, model, view):
        self._model = model
        self._view = view

    def show_items(self, bullet_point=False):
        items = self._model.read_items()
        if bullet_point:
            show_func = self._view.show_pullet_point_list
        else:
            show_func = self._view.show_number_point_list
        show_func(self._model.item_type, items)

    def show_item(self, name):
        try:
            item = self._model.read_item(name)
            self._view.show_item(self._model.item_type, item)
        except ItemNotStoredError as e:
            self._view.display_missing_item_error(name, e)

    def insert_item(self, item):
        assert item.price > 0, 'price must be greater than 0'
        assert item.quantity >= 0, 'quantity must be greater than or equal to 0'

        item_type = self._model.item_type
        try:
            self._model.create_item(item)
            self._view.display_item_stored(item.name, item_type)
        except ItemAlreadyStoredError as e:
            self._view.display_item_already_stored_error(item.name, item_type, e)

    def update_item(self, item):
        assert item.price > 0, 'price must be greater than 0'
        assert item.quantity >= 0, 'quantity must be greater than or equal to 0'

        try:
            old = self._model.read_item(item.name)
            self._model.update_item(item)
            self._view.display_item_updated(old, item)
        except ItemNotStoredError as e:
            self._view.display_item_not_stored_error(item.name, self._model.item_type, e)

    def update_item_type(self, new_item_type):
        old_item_type = self._model.item.type
        self._model.item_type = new_item_type
        self._view.display_item_type_changed(old_item_type, new_item_type)

    def delete_item(self, name):
        try:
            self._model.delete_item(name)
            self._view.display_item_deleted(name)
        except ItemNotStoredError as e:
            self._view.display_item_not_stored_error(name, self._model.item_type, e)
