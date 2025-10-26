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
    src/Gui/interface/Application.cpp    
    src/Gui/interface/AbstractButton.cpp

    src/Gui/interface/widgets/nodegraph/ForceDirectedGraph.cpp
    src/Gui/interface/widgets/nodegraph/GraphicsScene.cpp
    src/Gui/interface/widgets/nodegraph/GraphicsView.cpp
    src/Gui/interface/widgets/nodegraph/Edge.cpp
    src/Gui/interface/widgets/nodegraph/Node.cpp

    src/Gui/pages/RecursiveViewPage/RecursiveViewPage.cpp
    src/Gui/pages/RecursiveViewPage/RecursiveTableWidget.cpp
    src/Gui/pages/RecursiveViewPage/TableWidget.cpp
    src/Gui/pages/ForceDirectedGraphPage/ForceDirectedGraphPage.cpp
    src/Gui/interface/Nodegraph.cpp
    src/Gui/interface/Home.cpp
    src/Gui/interface/widgets/Sidebar.cpp
    src/Gui/interface/widgets/Search.cpp
    src/Gui/interface/widgets/Settings.cpp
    src/Gui/interface/widgets/Tree.cpp
    src/Gui/interface/widgets/Header.cpp
    src/Gui/interface/widgets/dropdown/Properties.cpp
    src/Gui/interface/widgets/dropdown/Results.cpp
    src/Gui/interface/widgets/dropdown/Sort.cpp

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
    # TBB::tbb
    Python3::Python
    ${PXR_LIBRARIES}
)
target_include_directories(${AppExec} PUBLIC
    ${ENGINE_INCLUDE_DIRECTORIES}
)
