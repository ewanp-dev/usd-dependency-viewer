

if __name__ == "__main__":
    import os

    EXAMPLES_FOLDER: str = "~/repos/local/USD-Strata/examples/houdini/"
    expanded_path: str = os.path.expanduser(EXAMPLES_FOLDER)
    print(expanded_path)

