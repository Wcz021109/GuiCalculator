add_library(DualDisplayPanel STATIC
        DualDisplayPanel.cpp
)

target_include_directories(DualDisplayPanel PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(DualDisplayPanel PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION DualDisplayPanel.h)