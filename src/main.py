import argparse
import os
import sys

from PyQt6.QtWidgets import QApplication
from PyQt6.QtGui import QFontDatabase

from core.item import strata_core_usditem
from interface.application import load_styles, strata_window_main


def main():
    """
    TODO
    * add in more verbose arguments
    * add in help argument
    * add in refresh argument
    * add in description
    * add in man command
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("usd_file", help="Path to the USD File")
    args = parser.parse_args()

    usd_item = strata_core_usditem(os.path.expanduser(args.usd_file))

    app = QApplication(sys.argv)
    load_styles(app)
    window = strata_window_main(item=usd_item)
    window.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()
