set(DIR ${CMAKE_CURRENT_SOURCE_DIR}) # Directory with this CMakeLists.txt

# cum -- plugins
add_library(cum SHARED)
target_include_directories(cum PUBLIC ${DIR}/include)
target_sources(cum PRIVATE ${DIR}/source/cum/manager.cpp)

# dr4 -- drawing
add_library(dr4 INTERFACE)
target_include_directories(dr4 INTERFACE ${DIR}/include)
target_link_libraries(dr4 INTERFACE cum)

#hui -- widgets
add_library(hui SHARED)
target_sources(hui PRIVATE
    ${DIR}/source/hui/container.cpp
    ${DIR}/source/hui/event.cpp
    ${DIR}/source/hui/widget.cpp
    ${DIR}/source/hui/state.cpp
)
target_include_directories(hui PRIVATE ${DIR}/include)

# pp -- graphical editor drawing tools
add_library(pp INTERFACE)
target_include_directories(pp INTERFACE ${DIR}/include)
target_link_libraries(pp INTERFACE cum)
