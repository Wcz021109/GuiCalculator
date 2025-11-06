add_library(MainWindow STATIC
        include/MainWindow.h
        src/MainWindow.cpp
)

target_include_directories(MainWindow PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(MainWindow PRIVATE
        Function
        Memory
        CalculateCore

        DualDisplayPanel

        Button
        BasicInputPanel

        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(DIRECTORY include DESTINATION include/MainWindow)