add_library(CalculateCore STATIC
        CalculateCore.cpp
)

target_include_directories(CalculateCore PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(CalculateCore PRIVATE
        Qt::Core
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION CalculateCore.h)