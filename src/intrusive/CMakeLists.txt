cmake_minimum_required(VERSION 3.20)
project(intrusive)

add_library(${PROJECT_NAME}
    pointed_object.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

