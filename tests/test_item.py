import time

import pytest
import src.item as item

# TODO: Run tests on dependency resolvers
# TODO: Start writing item class to run tests with

"""
Tests to run:
    assertion tests on dependency function types
    assertion tests on function times
    parameter tests using different dependency types
    large vs smaller tests
"""


@pytest.fixture
def usd_item():
    # NOTE: Using dummy usd for now, will switch to a local file at a later point
    return item.UsdItem(
        "/Applications/Houdini/Houdini20.5.445/Frameworks/Houdini.framework/Versions/20.5/Resources/houdini/usd/assets/crag/crag.usd"
    )


def test_path(usd_item):
    # testing that paths match, simple test to see that fixture is working
    assert (
        usd_item.path
        == "/Applications/Houdini/Houdini20.5.445/Frameworks/Houdini.framework/Versions/20.5/Resources/houdini/usd/assets/crag/crag.usd"
    )


def test_function_runtime(usd_item):
    start = time.perf_counter()
    result = usd_item.time_test()
    elapsed = time.perf_counter() - start

    assert elapsed < 0.5, f"Function too slow: {elapsed:.3f}s"
