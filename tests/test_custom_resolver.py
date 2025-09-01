import os

from pxr import Ar, Sdf

"""
testing the logistics of creating a custom resolver as the 
ComputeAllDependencies function is good but quite slow
"""

PATH = os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda")


def resolve_asset_basic(path: str = PATH):
    layer = Sdf.Layer.FindOrOpen(path)
    resolved = layer.resolvedPath
    resolver = Ar.GetResolver()
    ctx = resolver.CreateDefaultContextForAsset(resolved)

    with Ar.ResolverContextBinder(ctx):
        for sublayer in layer.subLayerPaths:
            print(sublayer)
            resolved_path = resolver.Resolve(sublayer)
            print(resolved_path)


def resolve_asset_recursive(path):
    print("\n")
    layer = Sdf.Layer.FindOrOpen(path)
    resolved = layer.resolvedPath
    resolver = Ar.GetResolver()
    ctx = resolver.CreateDefaultContextForAsset(resolved)

    with Ar.ResolverContextBinder(ctx):
        print(resolved)
        for sublayer in layer.subLayerPaths:
            print(f"UNRESOLVED PATH:  {sublayer}")
            print(f"RESOLVED PATH: {resolver.Resolve(sublayer)}")
            resolve_asset_recursive(path=resolver.Resolve(sublayer))


if __name__ == "__main__":
    resolve_asset_recursive(PATH)
