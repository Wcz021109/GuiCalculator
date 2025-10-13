add_library(Mainwindow STATIC
        mainwindow.cpp
)

target_include_directories(Mainwindow PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Mainwindow PRIVATE
        CalculateCore
        Memory

        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION mainwindow.h)