"""
bring in the interface here
"""

import sys
import argparse
import os
from PyQt6.QtWidgets import QApplication
from interface.application import strata_window_main, load_styles
from core.item import strata_core_usditem 

def main():
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
