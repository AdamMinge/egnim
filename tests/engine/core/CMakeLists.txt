# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# --------------------------- Generate headers and set files variable ------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/tests/engine/core/src)
set(include_root ${EGNIM_SOURCE_DIR}/tests/engine/core/include)

set(sources
    ${source_root}/main.cpp)

set(includes)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Create engine core test -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_test(egnim-core-test
        SOURCES ${sources} ${includes}
        DEPENDS engine::egnim-engine)
# -------------------------------------------------------------------------------------------------- #
