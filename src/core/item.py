import json
import os
import time

from pxr import Ar, Sdf, Usd, UsdUtils

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
        self._cache_file = os.path.expanduser("~/repos/local/USD-Strata/cache/tmp.json")
        self.dependencies = self.cache_dependencies(file=self._cache_file)
        self.dependencies_list = []

    def get_flattened_dependencies(self):
        self.flatten_dependencies(self.dependencies)
        return list(set(self.dependencies_list))

    def flatten_dependencies(self, tree):
        total = 1
        for child in tree["children"]:
            self.dependencies_list.append(child["name"])
            total += self.flatten_dependencies(child)
        return total

    def cache_dependencies(self, file: str):
        """
        pre-caches the dependencies upon startup, this is super inefficient at the moment
        for many reasons but I will leave it like this for now
        """
        if not os.path.exists(file):
            tree = self.construct_dependency_tree(self.path)
            with open(file, "w") as f:
                json.dump(tree, f, indent=4)

            return tree

        else:
            with open(file, "r") as r:
                return json.load(r)

    def construct_dependency_tree(self, path: str = "", visited=None):
        """
        constructs all the dependencies based off of the given file
        """
        if visited is None:
            visited = set()

        layer = Sdf.Layer.FindOrOpen(path)
        if not layer:
            return {"name": path, "children": []}

        resolver = Ar.GetResolver()
        layer_resolved = layer.resolvedPath

        visited.add(layer_resolved)

        ctx = resolver.CreateDefaultContextForAsset(layer_resolved)
        node = {"name": layer_resolved.GetPathString(), "children": []}

        with Ar.ResolverContextBinder(ctx):
            for sublayer in layer.externalReferences:
                resolved_path = resolver.Resolve(
                    resolver.CreateIdentifier(sublayer, layer_resolved)
                )
                if resolved_path:
                    child_node = self.construct_dependency_tree(
                        resolved_path.GetPathString(), visited
                    )
                    node["children"].append(child_node)

        return node


if __name__ == "__main__":

    @benchmark(num_tests=1)
    def main():
        item = strata_core_usditem(
            path=os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda")
        )
        dep = item.dependencies
        # _list = item.get_dependencies_list(dep)
        print(len(item.get_flattened_dependencies()))

    main()
