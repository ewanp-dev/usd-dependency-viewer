import os

from pxr import Sdf, Usd, UsdUtils

# NOTE pytest is messing with relative imports so this is just a temporary
# workaround so I can continue to run tests
try:
    from decorators import *
    from item import UsdItem
except ModuleNotFoundError:
    from .item import UsdItem


class UsdDependencies:

    def __init__(self, usd_item):
        self.item = usd_item
        self.layers = self.item.get_layers()
        self.layers_tree = self.calculate_dependencies()

    def calculate_dependencies(self):
        """
        takes the input usd item and creates the dependency
        tree
        """
        layers_tree = {}
        for layer in self.layers:
            dependency_instance = UsdItem(path=layer.realPath)
            tmp_dict = {}
            tmp_dict["sublayers"] = dependency_instance.get_sublayers()
            layers_tree[dependency_instance.path] = tmp_dict

        return layers_tree


if __name__ == "__main__":
    item = UsdItem(path=os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda"))
    tmp = UsdDependencies(usd_item=item)
