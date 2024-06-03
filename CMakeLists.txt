cmake_minimum_required(VERSION 3.10)
project(MKCG CXX)
include_directories(PUBLIC include)

# Installation of gro library
add_library(gro SHARED src/gro.cpp)
target_compile_features(gro PUBLIC cxx_std_11)

# Installation of matvec library (header only)
add_library(matvec INTERFACE)
target_compile_features(matvec INTERFACE cxx_std_11)
target_include_directories(matvec INTERFACE include)

# Installtion of mkcg software
add_executable(mkcg src/mkcg.cpp)
target_link_libraries(mkcg gro)
target_compile_features(gro PUBLIC cxx_std_11)

install(TARGETS gro mkcg RUNTIME DESTINATION bin LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
