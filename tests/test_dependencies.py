import os
import time

import pytest
import src.dependencies as dep_item
import src.item as usd_item

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
        _item_instance = usd_item.UsdItem(path=_.realPath)
        dep_tree[_item_instance.path] = _item_instance.get_sublayers()

    assert len(dep_tree.keys()) == len(layers)


# ---------------------------------------------------------------
# TEST : simple assertion test on whether dependencies dict is working


def test_dependencies_dict(dep_item_instance):
    assert dep_item_instance.layers_tree


# ---------------------------------------------------------------


def test_dependencies_execution_time(item_parametrized):
    start = time.perf_counter()
    dependencies_class = dep_item.UsdDependencies(usd_item=item_parametrized)
    dependency_tree = dependencies_class.layers_tree
    elapsed = time.perf_counter() - start

    assert elapsed < 0.5, f"Function is too slow: {elapsed:.3f}s"
