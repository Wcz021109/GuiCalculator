add_library(BasicInputPanel STATIC
        BasicInputPanel.cpp
)

target_include_directories(BasicInputPanel PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(BasicInputPanel PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION BasicInputPanel.h)