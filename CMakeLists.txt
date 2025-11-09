add_library(dr4hui-interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/hui/event.cpp
)

target_include_directories(dr4hui-interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
