#  Copyright (c) 2026 Gubarger. All rights reserved.
#
# This file is part of the Gubash project.
# Distributed under the MIT License. See the LICENSE file for details.

# CMakeList.txt: top-level CMake project file.

cmake_minimum_required (VERSION 3.10)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Gubash")

add_subdirectory ("Gubash")