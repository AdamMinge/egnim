# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/src/egnim/tools/editor)
set(include_root ${EGNIM_SOURCE_DIR}/include/egnim/tools/editor)
set(uis_root ${EGNIM_SOURCE_DIR}/uis/egnim/tools/editor)
set(resources_root ${EGNIM_SOURCE_DIR}/resources)

set(sources
        ${source_root}/meta_types.cpp
        ${source_root}/main.cpp
        ${source_root}/main_window.cpp
        ${source_root}/language_manager.cpp
        ${source_root}/style_manager.cpp
        ${source_root}/action_manager.cpp
        ${source_root}/preferences_manager.cpp
        ${source_root}/logging_manager.cpp
        ${source_root}/issue.cpp
        ${source_root}/about_dialog.cpp
        ${source_root}/settings_dialog.cpp
        ${source_root}/file_system_watcher.cpp

        ${source_root}/document/document.cpp
        ${source_root}/document/document_manager.cpp
        ${source_root}/document/document_editor.cpp
        ${source_root}/document/scene_document.cpp
        ${source_root}/document/scene_editor.cpp
        ${source_root}/document/new_document_dialog.cpp
        ${source_root}/document/undo_dock.cpp
        ${source_root}/document/inspector_dock.cpp
        ${source_root}/document/nodes_dock.cpp
        ${source_root}/document/nodes_view.cpp
        ${source_root}/document/nodes_scene.cpp
        ${source_root}/document/no_document_widget.cpp
        ${source_root}/document/document_serializer.cpp
        ${source_root}/document/priv/document_serializer_impl.h
        ${source_root}/document/priv/document_serializer_impl.cpp
        ${source_root}/document/priv/json_document_serializer_impl.h
        ${source_root}/document/priv/json_document_serializer_impl.cpp

        ${source_root}/project/project.cpp
        ${source_root}/project/no_project_widget.cpp
        ${source_root}/project/project_manager.cpp
        ${source_root}/project/game_project.cpp
        ${source_root}/project/new_project_dialog.cpp
        ${source_root}/project/new_directory_dialog.cpp
        ${source_root}/project/rename_file_dialog.cpp
        ${source_root}/project/rename_directory_dialog.cpp
        ${source_root}/project/project_file_system_proxy_model.cpp
        ${source_root}/project/project_file_system_model.cpp
        ${source_root}/project/project_dock.cpp
        ${source_root}/project/console_dock.cpp
        ${source_root}/project/issue_dock.cpp
        ${source_root}/project/project_serializer.cpp
        ${source_root}/project/project_list_model.cpp
        ${source_root}/project/project_list_delegate.cpp
        ${source_root}/project/export_project_dialog.cpp
        ${source_root}/project/export_preset_widget.cpp
        ${source_root}/project/export_preset.cpp
        ${source_root}/project/export_preset_list_model.cpp
        ${source_root}/project/export_manager.cpp
        ${source_root}/project/export_template.cpp
        ${source_root}/project/export_template_list_model.cpp
        ${source_root}/project/priv/project_serializer_impl.h
        ${source_root}/project/priv/project_serializer_impl.cpp
        ${source_root}/project/priv/json_project_serializer_impl.h
        ${source_root}/project/priv/json_project_serializer_impl.cpp

        ${source_root}/commands/command.cpp
        ${source_root}/commands/group_command.cpp)

set(includes
        ${include_root}/meta_types.h
        ${include_root}/main_window.h
        ${include_root}/language_manager.h
        ${include_root}/style_manager.h
        ${include_root}/action_manager.h
        ${include_root}/preferences_manager.h
        ${include_root}/logging_manager.h
        ${include_root}/issue.h
        ${include_root}/about_dialog.h
        ${include_root}/settings_dialog.h
        ${include_root}/file_system_watcher.h

        ${include_root}/document/document.h
        ${include_root}/document/document_manager.h
        ${include_root}/document/document_editor.h
        ${include_root}/document/scene_document.h
        ${include_root}/document/scene_editor.h
        ${include_root}/document/new_document_dialog.h
        ${include_root}/document/undo_dock.h
        ${include_root}/document/inspector_dock.h
        ${include_root}/document/nodes_dock.h
        ${include_root}/document/nodes_view.h
        ${include_root}/document/nodes_scene.h
        ${include_root}/document/no_document_widget.h
        ${include_root}/document/document_serializer.h

        ${include_root}/project/project.h
        ${include_root}/project/no_project_widget.h
        ${include_root}/project/project_manager.h
        ${include_root}/project/game_project.h
        ${include_root}/project/new_project_dialog.h
        ${include_root}/project/new_directory_dialog.h
        ${include_root}/project/rename_file_dialog.h
        ${include_root}/project/rename_directory_dialog.h
        ${include_root}/project/project_file_system_proxy_model.h
        ${include_root}/project/project_file_system_model.h
        ${include_root}/project/project_dock.h
        ${include_root}/project/console_dock.h
        ${include_root}/project/issue_dock.h
        ${include_root}/project/project_serializer.h
        ${include_root}/project/project_list_model.h
        ${include_root}/project/project_list_delegate.h
        ${include_root}/project/export_project_dialog.h
        ${include_root}/project/export_preset_widget.h
        ${include_root}/project/export_preset.h
        ${include_root}/project/export_preset_list_model.h
        ${include_root}/project/export_manager.h
        ${include_root}/project/export_template.h
        ${include_root}/project/export_template_list_model.h

        ${include_root}/commands/command.h
        ${include_root}/commands/group_command.h)

set(resources
        ${resources_root}/egnim-images.qrc
        ${resources_root}/egnim-translations.qrc)

set(uis
        ${uis_root}/main_window.ui
        ${uis_root}/about_dialog.ui
        ${uis_root}/settings_dialog.ui

        ${uis_root}/document/no_document_widget.ui
        ${uis_root}/document/new_scene_document_dialog.ui

        ${uis_root}/project/no_project_widget.ui
        ${uis_root}/project/new_game_project_dialog.ui
        ${uis_root}/project/new_directory_dialog.ui
        ${uis_root}/project/rename_directory_dialog.ui
        ${uis_root}/project/rename_file_dialog.ui
        ${uis_root}/project/export_project_dialog.ui
        ${uis_root}/project/project_dock.ui
        ${uis_root}/project/export_preset_widget.ui)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- Qt libraries configuration ------------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${uis_root})
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# -------------------------------------------------------------------------------------------------- #
# ------------------------------------ create engine editor ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_tool(egnim-tools-editor
        SOURCES ${sources} ${includes} ${uis} ${resources}
        DEPENDS Qt6::Widgets engine::egnim-engine tool::tools-shared)

egnim_add_translations(egnim-tools-editor
        QM_DIR ${resources_root}/translations/
        INCLUDES ${include_root}
        SOURCES ${source_root}
        TS_FILES
        ${resources_root}/translations/egnim_editor_pl.ts
        ${resources_root}/translations/egnim_editor_en.ts)

target_compile_definitions(egnim-tools-editor
        PUBLIC QT_NO_KEYWORDS)
# -------------------------------------------------------------------------------------------------- #
