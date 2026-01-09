cmake_minimum_required(VERSION 3.26)

# set vars
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

# set exec names
set(AppExec dependencyViewer)
set(TestExec tests)

set(CMAKE_AUTORCC ON)

# setup project
project(force_directed_graph_qt)

set(ENZO_DEV_LIB_DIR "${CMAKE_SOURCE_DIR}/build/src/OpDefs/")

set(SOURCES
    static/resources.qrc
    src/Gui/Main.cpp

    src/Gui/Application.cpp
    src/Gui/Widgets/Header.cpp
    src/Gui/Widgets/Search.cpp
    src/Gui/Widgets/Footer.cpp

    src/Gui/Widgets/Settings/Settings.cpp

    src/Core/Nodegraph/Edge.cpp
    src/Core/Nodegraph/ForceDirectedGraph.cpp
    src/Core/Nodegraph/GraphicsScene.cpp
    src/Core/Nodegraph/GraphicsView.cpp
    src/Core/Nodegraph/Node.cpp

    src/Gui/Widgets/NavigationPage.cpp
    src/Gui/Widgets/ItemSelection/ItemBackgroundWidget.cpp
    src/Gui/Widgets/ItemSelection/ItemWidget.cpp
    src/Gui/Widgets/ItemSelection/ItemThumbnail.cpp
    src/Gui/Widgets/ItemSelection/ItemListWidget.cpp
    src/Gui/Widgets/Nodegraph/Nodegraph.cpp
    src/Gui/Widgets/Nodegraph/NodegraphPropertiesWidget.cpp
    src/Gui/Widgets/RecursiveViewTable/TableHeader.cpp
    src/Gui/Widgets/Properties/PropertiesWidget.cpp

    src/Gui/Widgets/AbstractWidgets/AbstractButton.cpp
    src/Gui/Widgets/AbstractWidgets/AbstractTable.cpp
    src/Gui/Widgets/AbstractWidgets/AbstractWidgetUtils.cpp

    src/Gui/Widgets/DropdownWidgets/Properties.cpp
    src/Gui/Widgets/DropdownWidgets/Results.cpp
    src/Gui/Widgets/DropdownWidgets/Sort.cpp

    src/Core/UsdDependencyGraph.cpp
    src/Core/DependencyNode.cpp
    src/Core/NodePath.cpp
)

set(ENGINE_INCLUDE_DIRECTORIES
    src
    extern/icecream-cpp/include
)


# qt
find_package(Qt6 REQUIRED COMPONENTS Core Widgets SvgWidgets OpenGLWidgets)
qt_standard_project_setup()
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

# argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# tbb
# find_package(TBB REQUIRED COMPONENTS tbb)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
include_directories(${Python3_INCLUDE_DIRS})

# usd
find_package(X11 REQUIRED)
set(PXR_USD_LOCATION "$ENV{HOME}/USD")
list(APPEND CMAKE_PREFIX_PATH "${PXR_USD_LOCATION}")
find_package(pxr REQUIRED COMPONENTS Sdf Tf Vt Usd)
add_compile_options(-Wno-deprecated)

# force directed graph
# set(FDG_FRAMEWORK_DIR "${CMAKE_SOURCE_DIR}/../qt-force-directed-graph-framework")
# include_directories(${FDG_FRAMEWORK_DIR}/include)
# link_directories(${FDG_FRAMEWORK_DIR}/build)


qt_add_executable(${AppExec}
    ${SOURCES}
)

target_compile_definitions(${AppExec} PRIVATE ENZO_DEV_LIB_DIR="${ENZO_DEV_LIB_DIR}")

target_link_libraries(${AppExec} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::SvgWidgets
    Qt6::OpenGLWidgets
    argparse
    # TBB::tbb
    Python3::Python
    ${PXR_LIBRARIES}
)
target_include_directories(${AppExec} PUBLIC
    ${ENGINE_INCLUDE_DIRECTORIES}
    ${PXR_INCLUDE_DIRS}
)
