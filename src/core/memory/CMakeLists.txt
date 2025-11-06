add_library(Memory STATIC
        include/Memory.h
        src/Memory.cpp
)

target_include_directories(Memory PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Memory PRIVATE
        Qt::Core
)

install(DIRECTORY include DESTINATION include/Memory)