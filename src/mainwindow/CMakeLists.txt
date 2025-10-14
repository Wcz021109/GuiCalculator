add_library(Mainwindow STATIC
        mainwindow.cpp
)

target_include_directories(Mainwindow PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Mainwindow PRIVATE
        CalculateCore
#        Memory
        Dialog

        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION mainwindow.h)

# Dialog 次级子类

add_library(Dialog STATIC
        dialog/dialog.cpp
)

target_include_directories(Dialog PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/error_dialog
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Dialog PRIVATE
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY dialog DESTINATION dialog/dialog.h)