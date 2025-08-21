import time

from pxr import Sdf, Usd, UsdUtils


class UsdItem:

    def __init__(self, path: str):
        self.path = path

    def time_test(self):
        time.sleep(0.1)
        print("function_sorted")
