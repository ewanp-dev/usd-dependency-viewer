import os

import pytest

import src.item as item

"""
this is where usd dependency related tests will live so the test_item.py
file doesn't become too bloated
"""

# ---------------------------------------------------------------
# TEST: testing that different usd files lists add up to the number of external references


@pytest.mark.parametrize(
    "test_projects",
    [
        os.path.expanduser("~/lib/usd/ALab-main/ALab/entry.usda"),
        os.path.expanduser("~/repos/local/USD-Strata/examples/assets/test.usda"),
        os.path.expanduser("~/geo/untitled.usd_rop1.usda"),
    ],
)
def test_compare_references(test_projects):
    usd_item = item.UsdItem(test_projects)
    sublayers = usd_item.get_sublayers()
    references = usd_item.get_references()
    assert len(sublayers + references) == len(usd_item.layer.externalReferences)
