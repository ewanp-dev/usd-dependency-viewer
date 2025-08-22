import os
import time
from pathlib import Path

import pytest

import src.item as item

"""
Tests to run:
    assertion tests on dependency function types
    assertion tests on function times
    parameter tests using different dependency types
    large vs smaller tests
"""

TESTS_DIR = Path(__file__).parent
ASSETS_DIR = (TESTS_DIR / "../examples/assets").resolve()

# ---------------------------------------------------------------


def test_asset_loading():
    usd_file = (ASSETS_DIR / "crag/crag.usd").resolve()
    assert usd_file.exists()


# ---------------------------------------------------------------


@pytest.fixture
def usd_item():
    # NOTE: Using dummy usd for now, will switch to a local file at a later point
    return item.UsdItem(str((ASSETS_DIR / "rubbertoy/rubbertoy.usd").resolve()))


# ---------------------------------------------------------------
# TEST : Checking specific paths


@pytest.mark.skip(reason="Test not relevant")
def test_path(usd_item):
    # testing that paths match, simple test to see that fixture is working
    assert usd_item.path == str((ASSETS_DIR / "rubbertoy/rubbertoy.usd").resolve())


# ---------------------------------------------------------------
# TEST : Checking to see that the dependecies function is working


@pytest.mark.parametrize(
    "path",
    [
        str((ASSETS_DIR / "pig/pig.usd").resolve()),
        str((ASSETS_DIR / "squab/squab.usd").resolve()),
    ],
)
def test_scrape_dependencies(usd_item, path):
    # need to see that there are dependencies

    dependencies = item.UsdItem(path)
    assert len(usd_item.get_layers()) > 1


# ---------------------------------------------------------------
# TEST : Checking the execution time meets specific time constraints


@pytest.mark.parametrize(
    "path",
    [
        str((ASSETS_DIR / "pig/pig.usd").resolve()),
        str((ASSETS_DIR / "squab/squab.usd").resolve()),
    ],
)
def test_scrape_dependencies_runtime(usd_item, path):
    start = time.perf_counter()
    result = item.UsdItem(path).get_layers()
    elapsed = time.perf_counter() - start

    assert elapsed < 0.8, f"Function too slow: {elapsed:.3f}s"


# ---------------------------------------------------------------
# TEST : Checking to see that the returned dependencies do in fact exist


@pytest.mark.parametrize(
    "path",
    [
        os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda"),
        str((ASSETS_DIR / "pig/pig.usd").resolve()),
        str((ASSETS_DIR / "squab/squab.usd").resolve()),
    ],
)
def test_existing_dependencies(path):
    usd_item = item.UsdItem(path)
    dependencies = usd_item.get_layers()
    for _ in dependencies:
        assert os.path.exists(_.realPath)
