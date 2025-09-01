import os
import time

from pxr import Sdf, Usd, UsdUtils

try:
    from decorators import benchmark
except ModuleNotFoundError:
    pass


class strata_core_usditem:
    """
    TODO:
        - write resolve function to properly group dependencies
        - write in checks for if the given path does not exist
    """

    def __init__(self, path: str):
        self.path = path
        self.layer = Sdf.Layer.FindOrOpen(self.path)
        self.dependencies = UsdUtils.ComputeAllDependencies(self.path)
        self.layers = self.dependencies[0]
        self.layers_path = [i.realPath for i in self.layers]

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

    def calculate_single_dependencies(self):
        """
        calculates a single dict of all dependencies and their top level
        depenncies

        NOTE
        * this will probably be removed in later revisions as there will be no need
        for two dependency resolving solutions
        """

        layer_tree = {}
        for layer in self.get_layers():
            depdendency_instance = UsdItem(path=layer.realPath)
            tmp_dict = {}
            tmp_dict["sublayers"] = depdendency_instance.get_sublayers()
            tmp_dict["references"] = depdendency_instance.get_references()
            layer_tree[depdendency_instance.path] = tmp_dict

        return layer_tree


if __name__ == "__main__":
    item = UsdItem(path=os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda"))
    print(len(item.calculate_single_dependencies().keys()))
    # assert isinstance(item, UsdItem)
