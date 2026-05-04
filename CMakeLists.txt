cmake_minimum_required(VERSION 3.16)
project(robot_behavior_tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =============================================================================
# Fetch BehaviorTree.CPP v4.9.0 automatically (no manual install needed)
# =============================================================================
include(FetchContent)

# Disable optional BT.CPP features we don't need
set(BTCPP_SHARED_LIBS   OFF CACHE BOOL "" FORCE)
set(BTCPP_BUILD_TOOLS   OFF CACHE BOOL "" FORCE)
set(BTCPP_EXAMPLES      OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING        OFF CACHE BOOL "" FORCE)
set(BTCPP_GROOT_INTERFACE OFF CACHE BOOL "" FORCE)
set(BTCPP_SQLITE_LOGGING  OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    behaviortree_cpp
    GIT_REPOSITORY https://github.com/BehaviorTree/BehaviorTree.CPP.git
    GIT_TAG        4.6.2
)
FetchContent_MakeAvailable(behaviortree_cpp)

# =============================================================================
# Our executable
# =============================================================================
add_executable(robot_bt
    src/main.cpp
    src/robot_nodes.cpp
)

target_include_directories(robot_bt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(robot_bt PRIVATE behaviortree_cpp)
