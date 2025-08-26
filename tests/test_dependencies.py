import os

import pytest

import src.item as item

"""
this is where usd dependency related tests will live so the test_item.py
file doesn't become too bloated
"""


# ---------------------------------------------------------------
# TEST : test to see that the parametrize fixture is working properly
def test_fixture_parametrize(item_parametrized):
    path = item_parametrized.path
    assert path.endswith((".usd", ".usda"))


# ---------------------------------------------------------------
# TEST : testing that different usd files lists add up to the number of external references


def test_compare_references(item_parametrized):
    sublayers = item_parametrized.get_sublayers()
    references = item_parametrized.get_references()
    assert len(sublayers + references) == len(
        item_parametrized.layer.externalReferences
    )


# ---------------------------------------------------------------
# TEST : test to see that the keys for the dependency hashmap
# matches the length of all single dependencies


def test_compare_keys(item_parametrized):
    layers = item_parametrized.get_layers()

    dep_tree = {}

    for _ in layers:
        _item_instance = item.UsdItem(path=_.realPath)
        dep_tree[_item_instance.path] = _item_instance.get_sublayers()

    assert len(dep_tree.keys()) == len(layers)
