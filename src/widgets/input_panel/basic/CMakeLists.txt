add_library(BasicInputPanel STATIC
        include/BasicInputPanel.h
        src/BasicInputPanel.cpp
)

target_include_directories(BasicInputPanel PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(BasicInputPanel PRIVATE
        Button

        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY include DESTINATION include/BasicInputPanel.h)