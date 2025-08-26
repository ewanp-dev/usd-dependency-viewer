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
    """
    the calculate dependencies function os okay for now
    but it is running a little slow and its only going to get slower
    as we add more functionality to it

    not to worry about for now but keep it in mind, we will use multithreading
    with the interface which should help with speeds
    """

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
            tmp_dict["references"] = dependency_instance.get_references()
            layers_tree[dependency_instance.path] = tmp_dict

        return layers_tree


if __name__ == "__main__":
    item = UsdItem(path=os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda"))
    tmp = UsdDependencies(usd_item=item)
    for i in tmp.layers_tree.keys():
        print(i, tmp.layers_tree[i])
        print("\n")
