// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include "Prompt.h"
#include "../utils/MacrosesStyle.h"

namespace gubash::core
{
	std::string Prompt::GetPrompt()
	{
		std::string prompt;

		// User and host
		struct passwd* pw = getpwuid(getuid()); // Getting username via UID.
		char hostname[256];
		gethostname(hostname, sizeof(hostname));

		prompt += BOLD;
		prompt += BLUE;
		prompt += pw->pw_name;
		prompt += "@";
		prompt += hostname;
		prompt += RESET;
		prompt += " ";

		// Current directory.
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != nullptr) 
		{
			prompt += GREEN;
			prompt += cwd;
			prompt += RESET;
		}
		else
		{
			prompt += RED;
			prompt += "[unknown]";
			prompt += RESET;
		}

		// Access (user rights).
		char right = isRootUser() ? '#' : '$'; // Getting the Prompt symbol.

		prompt += "\n";
		prompt += BOLD;
		prompt += CYAN;
		prompt += right;
		prompt += " ";
		prompt += RESET;

		return prompt;
	}

	void Prompt::ShowPrompt()
	{
		std::cout << GetPrompt() << std::flush;
	}

	bool Prompt::isRootUser()
	{
		return getuid() == 0; // Root UID = 0.
	}
}