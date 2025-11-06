add_library(Button STATIC
        include/button.h
        src/button.cpp
)

target_include_directories(Button PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Button PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY include DESTINATION include/Button)