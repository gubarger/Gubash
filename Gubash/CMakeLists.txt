#  Copyright (c) 2026 Gubarger. All rights reserved.
#
# This file is part of the Gubash project.
# Distributed under the MIT License. See the LICENSE file for details.

# CMakeList.txt: CMake project for Gubash.

add_executable (Gubash "main.cpp" "core/Gubash.h"  "utils/MacrosesLogs.h" "utils/MacrosesTests.h"  "utils/MacrosesSaveToUse.h" "utils/MacrosesPlatform.h" "utils/MacrosesUseful.h" "core/Gubash.cpp" "core/Input.h" "core/Input.cpp" "core/Prompt.h" "core/Prompt.cpp" "utils/MacrosesStyle.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Gubash PROPERTY CXX_STANDARD 20)
endif()