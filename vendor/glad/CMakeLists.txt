cmake_minimum_required(VERSION 3.5)
project(glad)

add_library(glad STATIC glad.c glad/glad.h KHR/khrplatform.h)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})