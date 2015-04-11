project(aca2)

set(CMAKE_CXX_FLAGS "-mssse3 -msse4.1")

add_executable(aca2 main.cpp)

install(TARGETS aca2 RUNTIME DESTINATION bin)

add_subdirectory(include)