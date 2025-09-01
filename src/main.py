"""
bring in the interface here
"""

import sys
from PyQt6.QtWidgets import QApplication
from interface.application import strata_window_main, load_styles

def main():
    app = QApplication(sys.argv)
    load_styles(app)
    window = strata_window_main()
    window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
