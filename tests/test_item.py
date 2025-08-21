import pytest
import src.item as item

# TODO: Run tests on dependency resolvers
# TODO: Start writing item class to run tests with


@pytest.fixture
def fix_usditem():
    # NOTE: Using dummy usd for now, will switch to a local file at a later point
    return item.UsdItem(
        "/Applications/Houdini/Houdini20.5.445/Frameworks/Houdini.framework/Versions/20.5/Resources/houdini/usd/assets/crag/crag.usd"
    )


def test_path(fix_usditem):
    # testing that paths match, simple test to see that fixture is working
    assert (
        fix_usditem.path
        == "/Applications/Houdini/Houdini20.5.445/Frameworks/Houdini.framework/Versions/20.5/Resources/houdini/usd/assets/crag/crag.usd"
    )
