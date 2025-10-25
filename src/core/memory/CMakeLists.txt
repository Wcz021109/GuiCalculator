add_library(Memory STATIC Memory.cpp)

target_include_directories(Memory PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Memory PRIVATE
        CalculateCore
        Qt::Core
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION Memory.h)