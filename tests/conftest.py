import os
from pathlib import Path

import pytest
import src.item as item

# TODO: make a wildcard fixture to pick up all assets for easy parametrize

# ---------------------------------------------------------------


@pytest.fixture
def assets_dir():
    # NOTE: could also add parametrize mark here to point to multiple assets
    return (Path(__file_).parent / "../examples/assets").resolve()


@pytest.fixture
def item_instance(assets_dir):
    # TODO: move to parametrize mark to test multiple files
    return item.UsdItem(str((assets_dir / "rubbertoy/rubbertoy.usd").resolve()))
