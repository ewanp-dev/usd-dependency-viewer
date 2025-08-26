import os
import time

from pxr import Sdf, Usd, UsdUtils

try:
    from decorators import benchmark
except ModuleNotFoundError:
    pass


class UsdItem:
    """
    TODO:
        - write resolve function to properly group dependencies
        - write in checks for if the given path does not exist
    """

    def __init__(self, path: str):
        self.path = path
        self.layer = Sdf.Layer.FindOrOpen(self.path)

    def get_layers(self):
        # returns a list of all the dependencies to be resolved
        return UsdUtils.ComputeAllDependencies(self.path)[0]

    def get_assets(self):
        # returns a list of all the assets
        return UsdUtils.ComputeAllDependencies(self.path)[1]

    def get_unresolved_paths(self):
        # returns a list of all unresolved_paths
        return UsdUtils.ComputeAllDependencies(self.path)[2]

    def get_sublayers(self):
        # returns a list of all resolved top-level sublayers
        # TODO: cross compare with ComputeAllDependencies list to make sure all exist (maybe do this in a unit test)
        return [
            self.layer.ComputeAbsolutePath(path) for path in self.layer.subLayerPaths
        ]

    def get_references(self):
        # returns a list of all resolved top-level references
        # NOTE: this is just a dummy class for testing, i will improve it at a later point
        sublayers = self.get_sublayers()

        references_dirty = [
            self.layer.ComputeAbsolutePath(ref) for ref in self.layer.externalReferences
        ]
        references = [ref for ref in references_dirty if ref not in sublayers]
        return references


if __name__ == "__main__":
    item = UsdItem(path="tmp")
    assert isinstance(item, UsdItem)
