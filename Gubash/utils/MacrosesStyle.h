// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#pragma once

#include <string>

// Basic colors.
static constexpr const char* RESET = "\033[0m";
static constexpr const char* BOLD = "\033[1m";
static constexpr const char* DIM = "\033[2m";
static constexpr const char* ITALIC = "\033[3m";
static constexpr const char* UNDERLINE = "\033[4m";
static constexpr const char* BLINK = "\033[5m";
static constexpr const char* INVERT = "\033[7m";
static constexpr const char* HIDDEN = "\033[8m";

// Foreground colors.
static constexpr const char* BLACK = "\033[30m";
static constexpr const char* RED = "\033[31m";
static constexpr const char* GREEN = "\033[32m";
static constexpr const char* YELLOW = "\033[33m";
static constexpr const char* BLUE = "\033[34m";
static constexpr const char* MAGENTA = "\033[35m";
static constexpr const char* CYAN = "\033[36m";
static constexpr const char* WHITE = "\033[37m";

// Bright foreground colors.
static constexpr const char* BRIGHT_BLACK = "\033[90m";
static constexpr const char* BRIGHT_RED = "\033[91m";
static constexpr const char* BRIGHT_GREEN = "\033[92m";
static constexpr const char* BRIGHT_YELLOW = "\033[93m";
static constexpr const char* BRIGHT_BLUE = "\033[94m";
static constexpr const char* BRIGHT_MAGENTA = "\033[95m";
static constexpr const char* BRIGHT_CYAN = "\033[96m";
static constexpr const char* BRIGHT_WHITE = "\033[97m";

// Background colors.
static constexpr const char* BG_BLACK = "\033[40m";
static constexpr const char* BG_RED = "\033[41m";
static constexpr const char* BG_GREEN = "\033[42m";
static constexpr const char* BG_YELLOW = "\033[43m";
static constexpr const char* BG_BLUE = "\033[44m";
static constexpr const char* BG_MAGENTA = "\033[45m";
static constexpr const char* BG_CYAN = "\033[46m";
static constexpr const char* BG_WHITE = "\033[47m";

// Bright background colors.
static constexpr const char* BG_BRIGHT_BLACK = "\033[100m";
static constexpr const char* BG_BRIGHT_RED = "\033[101m";
static constexpr const char* BG_BRIGHT_GREEN = "\033[102m";
static constexpr const char* BG_BRIGHT_YELLOW = "\033[103m";
static constexpr const char* BG_BRIGHT_BLUE = "\033[104m";
static constexpr const char* BG_BRIGHT_MAGENTA = "\033[105m";
static constexpr const char* BG_BRIGHT_CYAN = "\033[106m";
static constexpr const char* BG_BRIGHT_WHITE = "\033[107m";

namespace gubash::utils
{
	// 256 colors.
    inline std::string fg256(int color)
    {
        return "\033[38;5;" + std::to_string(color) + "m";
    }

    inline std::string bg256(int color)
    {
        return "\033[48;5;" + std::to_string(color) + "m";
    }

    // True color (24-bit).
    inline std::string trueColor(int r, int g, int b)
    {
        return "\033[38;2;" +
            std::to_string(r) + ";" +
            std::to_string(g) + ";" +
            std::to_string(b) + "m";
    }

    inline std::string bgTruecolor(int r, int g, int b)
    {
        return "\033[48;2;" +
            std::to_string(r) + ";" +
            std::to_string(g) + ";" +
            std::to_string(b) + "m";
    }
}

#define M_GUBASH_COLORIZE__(color, text) (color + std::string(text) + RESET)
#define M_GUBASH_BOLD_TEXT__(text) (BOLD + std::string(text) + RESET)
#define M_GUBASH_ERROR_TEXT__(text) (BOLD RED + std::string(text) + RESET)
#define M_GUBASH_SUCCESS_TEXT__(text) (BOLD GREEN + std::string(text) + RESET)
#define M_GUBASH_WARNING_TEXT__(text) (BOLD YELLOW + std::string(text) + RESET)
#define M_GUBASH_INFO_TEXT__(text) (BOLD BLUE + std::string(text) + RESET)