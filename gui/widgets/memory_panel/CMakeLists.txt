add_library(MemoryPanel STATIC
        MemoryPanel.cpp
)

target_include_directories(MemoryPanel PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(MemoryPanel PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION MemoryPanel.h)