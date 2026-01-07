# Copyright (c) 2026 Gubarger. All Rights Reserved.

cmake_minimum_required(VERSION 3.2)

project(Gubash)
add_executable(${PROJECT_NAME} ${TARGET_SOURCES})

target_sources(${PROJECT_NAME} PRIVATE
  source/main.cpp
  source/parser.cpp
  source/laxer.cpp
  source/executor.cpp
  source/builtins.cpp
)
