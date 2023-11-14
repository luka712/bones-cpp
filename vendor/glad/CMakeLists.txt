cmake_minimum_required(VERSION 3.5)
project(Glad)

add_library(Glad STATIC glad.c glad/glad.h KHR/khrplatform.h)

target_include_directories(Glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})