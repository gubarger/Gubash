// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#include "../utils/MacrosesPlatform.h"

namespace gubash::core
{
	struct M_GUBASH_EXPORT__ Prompt
	{
		~Prompt() = default;

		std::string GetPrompt();
		void ShowPrompt();
		bool isRootUser();
	};
}