from pxr import Sdf, Usd, UsdUtils

path = "/Applications/Houdini/Houdini20.5.445/Frameworks/Houdini.framework/Versions/20.5/Resources/houdini/usd/assets/crag/crag.usd"

root_layer = Sdf.Layer.FindOrOpen(path)

dep_a = root_layer.ComputeAbsolutePath(root_layer.GetCompositionAssetDependencies()[0])

dep_b = UsdUtils.ComputeAllDependencies(assetPath=path)

# NOTE: this function returns 3 lists: layers, assets, unresolved paths
# TODO: need to time this function, we might be able to come up with a faster alternative

print("\n")
print("###################################")
print("\n")

for i in dep_b[0]:
    print(i, "\n")
