import os
import time

from pxr import Sdf, Usd, UsdUtils

from decorators import benchmark


class UsdItem:
    """
    TODO:
        - write resolve function to properly group dependencies
        - write in checks for if the given path does not exist
    """

    def __init__(self, path: str):
        self.path = path
        self.layer = Sdf.Layer.FindOrOpen(self.path)

    @benchmark(num_tests=3)
    def get_layers(self):
        # returns a list of all the dependencies to be resolved
        return UsdUtils.ComputeAllDependencies(self.path)[0]

    def get_assets(self):
        # returns a list of all the assets
        return UsdUtils.ComputeAllDependencies(self.path)[1]

    def get_unresolved_paths(self):
        # returns a list of all unresolved_paths
        return UsdUtils.ComputeAllDependencies(self.path)[2]


if __name__ == "__main__":
    test_file = "/Users/epalmer/lib/usd/ALab-main/ALab/entry.usda"

    item = UsdItem(path=test_file)
    layers = item.get_layers()
