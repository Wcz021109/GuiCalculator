add_library(Mainwindow STATIC
        mainwindow.cpp
)

target_include_directories(Mainwindow PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Mainwindow PRIVATE
        CalculateCore
#       Memory
        DualDisplayPanel
        MemoryPanel
        BasicInputPanel

        Qt::Core
        Qt::Gui
        Qt::Widgets
)

add_subdirectory(widgets/display_panel/dual)
add_subdirectory(widgets/memory_panel)
add_subdirectory(widgets/input_panel/basic)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION mainwindow.h)