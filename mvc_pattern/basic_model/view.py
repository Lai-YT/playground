
class View:
    @staticmethod
    def show_pullet_point_list(item_type, items):
        print(f'--- {item_type.upper()} LIST ---')
        for item in items:
            print(f'* {item}')

    @staticmethod
    def show_number_point_list(item_type, items):
        print(f'--- {item_type.upper()} LIST ---')
        for i, item in enumerate(items):
            print(f'{i + 1}. {item}')

    @staticmethod
    def show_item(item_type, item):
        print('/////')
        print(f'Good news, we have some {item.name.upper()}!')
        print(f'{item_type.upper()} INFO: {item}')
        print('/////')

    @staticmethod
    def display_missing_item_error(name, err):
        print('*****')
        print(f'We are sorry, we have no {name.upper()}!')
        print(err.args[0])
        print('*****')

    @staticmethod
    def display_item_already_stored_error(name, item_type, err):
        print('*****')
        print(f'Hey! We already have {name.upper()} in our {item_type} list!')
        print(err.args[0])
        print('*****')

    @staticmethod
    def display_item_not_stored_error(name, item_type, err):
        print('*****')
        print(f'Hey! We don\'t have any {name.upper()} in our {item_type} list. '
              'Please insert it first!')
        print(err.args[0])
        print('*****')

    @staticmethod
    def display_item_stored(name, item_type):
        print('+++++')
        print(f'Hooray! We have just added some {name.upper()} to our {item_type} list!')
        print('+++++')

    @staticmethod
    def display_item_type_changed(old_name, new_name):
        print('-- --')
        print(f'Change item type from "{old_name}" to "{new_name}"')
        print('-- --')

    @staticmethod
    def display_item_updated(old, new):
        print('-- --')
        print(f'Change {old.name} price: {old.price} --> {new.price}')
        print(f'Change {old.name} quantity: {old.quantity} --> {new.quantity}')
        print('-- --')

    @staticmethod
    def display_item_deleted(name):
        print('-----')
        print(f'We have just removed {name} from our list')
        print('-----')
