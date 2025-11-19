cmake_minimum_required(VERSION 3.10)
project(mipt-ded-zemax)
set(CMAKE_CXX_STANDARD 17)

set(DIR ${CMAKE_CURRENT_LIST_DIR}) # Directory with this CMakeLists.txt

# cum -- Plugins
add_library(cum SHARED)
target_include_directories(cum PUBLIC ${DIR}/include)
target_sources(cum PRIVATE ${DIR}/src/cum/manager.cpp)

# dr4 -- drawing
add_library(dr4 INTERFACE)
target_include_directories(dr4 INTERFACE ${DIR}/include)
target_link_libraries(dr4 INTERFACE cum)

# pp -- graphical editor drawing tools
add_library(pp INTERFACE)
target_include_directories(pp INTERFACE ${DIR}/include)
target_link_libraries(pp INTERFACE cum)


