add_library(Mainwindow STATIC
        mainwindow.cpp
)

target_include_directories(Mainwindow PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Mainwindow
        PRIVATE
            Qt::Core
            Qt::Gui
            Qt::Widgets
        STATIC
            CalculateCore
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION mainwindow.h)