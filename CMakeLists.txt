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
    src/dependency_viewer/Main.cpp
    src/dependency_viewer/interface/Application.cpp    
    src/dependency_viewer/interface/AbstractButton.cpp
    src/dependency_viewer/interface/Home.cpp
    src/dependency_viewer/interface/widgets/Sidebar.cpp
    src/dependency_viewer/interface/widgets/Header.cpp
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
find_package(TBB REQUIRED COMPONENTS tbb)


qt_add_executable(${AppExec}
    ${SOURCES}
)

target_compile_definitions(${AppExec} PRIVATE ENZO_DEV_LIB_DIR="${ENZO_DEV_LIB_DIR}")


target_link_libraries(${AppExec} PRIVATE Qt6::Core Qt6::Widgets Qt6::SvgWidgets Qt6::OpenGLWidgets TBB::tbb)
target_include_directories(${AppExec} PUBLIC
    ${ENGINE_INCLUDE_DIRECTORIES}
)

# ----
# start tests
# ----
# Include(FetchContent)

# FetchContent_Declare(
#   Catch2
#   GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#   GIT_TAG        v3.8.1 # or a later release
# )

# FetchContent_MakeAvailable(Catch2)

# add_executable(${TestExec}
#     ${SOURCES}
#     tests/main-tests.cpp
# )

# target_link_libraries(${TestExec} PRIVATE Catch2::Catch2WithMain Eigen3::Eigen Qt6::Core TBB::tbb)

# target_compile_definitions(${TestExec} PRIVATE UNIT_TEST)
# target_include_directories(${TestExec} PUBLIC
#     ${ENGINE_INCLUDE_DIRECTORIES}
#     ${BOOST_INCLUDE_DIRS}
# )
# target_compile_definitions(${TestExec} PRIVATE ENZO_DEV_LIB_DIR="${ENZO_DEV_LIB_DIR}")
# ----
# end tests
#
