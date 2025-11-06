add_library(DualDisplayPanel STATIC
        include/DualDisplayPanel.h
        src/DualDisplayPanel.cpp
)

target_include_directories(DualDisplayPanel PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(DualDisplayPanel PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY include DESTINATION include/DualDisplayPanel)