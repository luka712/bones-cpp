cmake_minimum_required(VERSION 3.5)
project(glad_es)

add_library(glad_es STATIC glad.c glad/glad_es.h KHR/khrplatform.h)

target_include_directories(glad_es PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})