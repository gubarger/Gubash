// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#include <iostream>

#include "Gubash.h"
#include "../utils/MacrosesUseful.h"

namespace gubash::core
{
	Gubash::Gubash()
	{
		std::cout << "Gubash [Version " << M_GUBASH_VERSION_FULL__ << "]\n\n\n";
	}

	void Gubash::Start()
	{
		while (true)
		{
			prompt_.ShowPrompt();
			input_.ReadLine();
		}
	}
}