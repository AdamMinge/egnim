# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# --------------------------- Generate headers and set files variable ------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/tests/engine/src)
set(include_root ${EGNIM_SOURCE_DIR}/tests/engine/include)

set(sources
    ${source_root}/main.cpp)

set(includes)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(GTest REQUIRED CONFIG)
# -------------------------------------------------------------------------------------------------- #
# --------------------------------- Define the abovo-test target ----------------------------------- #
# -------------------------------------------------------------------------------------------------- #
add_executable(egnim-core-test ${sources} ${includes})
# -------------------------------------------------------------------------------------------------- #
# -------------------------------- Define the abovo-test features ---------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set_target_properties(egnim-core-test PROPERTIES COMPILE_FEATURES cxx_std_17)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Setup include directories ------------------------------------ #
# -------------------------------------------------------------------------------------------------- #
target_include_directories(egnim-core-test
                           PUBLIC $<BUILD_INTERFACE:${ABOVO_SOURCE_DIR}/tests/core/include>)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Setup dependencies ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
target_link_libraries(egnim-core-test
                      PUBLIC egnim::egnim-engine
                      PRIVATE GTest::gtest
                      PRIVATE GTest::gmock)
# -------------------------------------------------------------------------------------------------- #
