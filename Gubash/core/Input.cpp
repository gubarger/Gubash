// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#include <iostream>
#include <cstring>

#include "Input.h"

namespace gubash::core
{
	Input::Input() : size_(0)
	{
	}

	void Input::ReadLine()
	{
		if (std::cin.getline(data_.str__, MAX_SIZE_))
		{
			size_ = std::strlen(data_.str__); // Preserving the row size.
			std::cout << "Str: " << data_.str__ << "\n";
		}
		else
		{
			std::cerr << "Error reading input.\n";
		}
	}
}