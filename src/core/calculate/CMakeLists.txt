add_library(CalculateCore STATIC
        include/CalculateCore.h
        src/CalculateCore.cpp
)

target_include_directories(CalculateCore PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(CalculateCore PRIVATE
        Function
        Memory

        Qt::Core
)

install(DIRECTORY include DESTINATION include/CalculateCore)