import os
from pathlib import Path

import pytest
import src.core.dependencies as dep_item
import src.core.item as usd_item

# TODO: make a wildcard fixture to pick up all assets for easy parametrize

# ---------------------------------------------------------------


@pytest.fixture
def assets_dir():
    # NOTE: could also add parametrize mark here to point to multiple assets
    return (Path(__file_).parent / "../examples/assets").resolve()


@pytest.fixture
def item_instance(assets_dir):
    # TODO: move to parametrize mark to test multiple files
    return usd_item.UsdItem(str((assets_dir / "rubbertoy/rubbertoy.usd").resolve()))


@pytest.fixture(
    params=[
        os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda"),
        os.path.expanduser("~/repos/local/USD-Strata/examples/assets/test.usda"),
        os.path.expanduser("~/geo/untitled.usd_rop1.usda"),
    ]
)
def item_parametrized(request):
    return usd_item.UsdItem(request.param)


@pytest.fixture
def dep_item_instance(item_parametrized):
    return dep_item.UsdDependencies(usd_item=item_parametrized)
