add_library(Function STATIC
        include/Function.h
        src/Function.cpp
)

target_include_directories(Function PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(Function PRIVATE
        Qt::Core
)

install(DIRECTORY include DESTINATION include/Function)