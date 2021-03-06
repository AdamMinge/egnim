# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/src/egnim/engine)
set(include_root ${EGNIM_SOURCE_DIR}/include/egnim/engine)
set(resources_root ${EGNIM_SOURCE_DIR}/resources)

set(sources
        ${source_root}/core/context.cpp
        ${source_root}/core/state.cpp
        ${source_root}/core/state_stack.cpp
        ${source_root}/core/command_queue.cpp
        ${source_root}/core/animated_sprite.cpp
        ${source_root}/core/main_loop.cpp

        ${source_root}/scene/component.cpp
        ${source_root}/scene/component_container.cpp
        ${source_root}/scene/node.cpp
        ${source_root}/scene/sound_node.cpp
        ${source_root}/scene/music_node.cpp
        ${source_root}/scene/sprite_node.cpp
        ${source_root}/scene/label_node.cpp
        ${source_root}/scene/animated_sprite_node.cpp
        ${source_root}/scene/camera.cpp
        ${source_root}/scene/scene_node.cpp
        ${source_root}/scene/node_factory.cpp

        ${source_root}/scene/visitor/scene_serializer.cpp
        ${source_root}/scene/visitor/priv/scene_serializer_impl.h
        ${source_root}/scene/visitor/priv/json_scene_serializer_impl.h
        ${source_root}/scene/visitor/priv/json_scene_serializer_impl.cpp)

set(includes
        ${include_root}/../config.h
        ${include_root}/export.h
        ${include_root}/core/object.h
        ${include_root}/core/context.h
        ${include_root}/core/lazy_unique_pointer.h
        ${include_root}/core/resource_holder.h
        ${include_root}/core/state.h
        ${include_root}/core/state_stack.h
        ${include_root}/core/command.h
        ${include_root}/core/command_queue.h
        ${include_root}/core/animated_sprite.h
        ${include_root}/core/main_loop.h

        ${include_root}/scene/component.h
        ${include_root}/scene/component_container.h
        ${include_root}/scene/node.h
        ${include_root}/scene/sound_node.h
        ${include_root}/scene/music_node.h
        ${include_root}/scene/sprite_node.h
        ${include_root}/scene/label_node.h
        ${include_root}/scene/animated_sprite_node.h
        ${include_root}/scene/camera.h
        ${include_root}/scene/scene_node.h
        ${include_root}/scene/node_factory.h

        ${include_root}/scene/visitor/scene_visitor.h
        ${include_root}/scene/visitor/scene_serializer.h)

set(resources)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(SFML REQUIRED COMPONENTS graphics audio system network)
find_package(box2d REQUIRED)
find_package(nlohmann_json REQUIRED)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- create application target ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_library(egnim-engine
        SOURCES ${sources} ${includes} ${resources}
        DEPENDS sfml-graphics sfml-audio sfml-system
                box2d nlohmann_json::nlohmann_json)

set_target_properties(egnim-engine
        PROPERTIES CXX_STANDARD 20)
# -------------------------------------------------------------------------------------------------- #
