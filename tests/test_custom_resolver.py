import os

from pxr import Ar, Sdf, UsdUtils

"""
testing the logistics of creating a custom resolver as the 
ComputeAllDependencies function is good but quite slow

TODO
* run checks for relative paths '../, ./ .etc'
* find an efficient way to resolve all paths
* run tests on sublayers and references
* compare with the ComputeAllDependencies function
* manually resolve broken context before writing recursive function
"""

PATH = os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda")


# -----------------------------------------------------------------------
# NOTE simple resolving function


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


# -----------------------------------------------------------------------
# NOTE broken


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


# -----------------------------------------------------------------------
# NOTE the number of dependencies here is inconsistent with the true number


def resolve_dependency_tree(path, visited=None):
    """
    Recursively resolve USD dependencies into a nested dict tree.
    Avoids cycles and duplicates by tracking visited paths.
    """
    if visited is None:
        visited = set()

    layer = Sdf.Layer.FindOrOpen(path)
    if not layer:
        return {"name": path, "children": []}

    resolver = Ar.GetResolver()
    lyrResolved = layer.resolvedPath

    # if already visited, stop recursion
    # if lyrResolved in visited:
    #    return {"name": str(lyrResolved) + " (already visited)", "children": []}
    visited.add(lyrResolved)

    ctx = resolver.CreateDefaultContextForAsset(lyrResolved)
    node = {"name": lyrResolved, "children": []}

    with Ar.ResolverContextBinder(ctx):
        for sublayer in layer.externalReferences:
            resolved_path = resolver.Resolve(
                resolver.CreateIdentifier(sublayer, lyrResolved)
            )
            if resolved_path:
                child_node = resolve_dependency_tree(
                    resolved_path.GetPathString(), visited
                )
                node["children"].append(child_node)

    return node


# -----------------------------------------------------------------------
# NOTE way to visualise the tree


def pretty_print_tree(node, indent=0):
    """Nicely prints the dependency tree."""
    print("  " * indent + "- " + str(node["name"]))
    for child in node["children"]:
        pretty_print_tree(child, indent + 1)


tree = resolve_dependency_tree(PATH)


# pretty_print_tree(tree)
x = []


def count_all_nodes(node):
    """Counts the node itself plus all children recursively."""
    total = 1  # count this node
    global x
    for child in node["children"]:
        x.append(child["name"])
        total += count_all_nodes(child)
    return total


total_files = count_all_nodes(tree)
# print(f"\nTotal files in tree (including root): {total_files}")

duplicates = [i for i in x if x.count(i) > 1]

# use set() to remove duplications
duplicates = set(duplicates)

print(len(x))
print(len(set(x)))
# print(len(UsdUtils.ComputeAllDependencies(PATH)[0]))
print(duplicates)

# resolve_asset_alternative(PATH)
