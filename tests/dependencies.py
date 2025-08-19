from pxr import Sdf

if __name__ == "__main__":
    import os

    EXAMPLES_FOLDER: str = "~/repos/local/USD-Strata/examples/houdini/"
    expanded_path: str = os.path.expanduser(f"{EXAMPLES_FOLDER}rubbertoy/rubbertoy.usd")

    layer = Sdf.Layer.FindOrOpen(expanded_path)

    print(layer.GetCompositionAssetDependencies())
