cmake_minimum_required(VERSION 3.8)

project(enum_class VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(example)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
        INTERFACE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)