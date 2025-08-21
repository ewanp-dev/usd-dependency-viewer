import time

from pxr import Sdf, Usd, UsdUtils


class UsdItem:

    def __init__(self, path: str):
        self.path = path

    def scrape_dependencies(self):
        root_layer = Sdf.Layer.FindOrOpen(self.path)
        all_dependencies = UsdUtils.ComputeAllDependencies(assetPath=self.path)
        layers = all_dependencies[0]
        assets = all_dependencies[1]
        unresolved_paths = all_dependencies[2]

        return layers


if __name__ == "__main__":
    test_file = "/Applications/Houdini/Houdini20.5.445/Frameworks/Houdini.framework/Versions/20.5/Resources/houdini/usd/assets/crag/crag.usd"

    item = UsdItem(path=test_file)
