// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#pragma once

#include <string>
#include <bits/stdint-uintn.h>

#include "../utils/MacrosesPlatform.h"

namespace gubash::core
{
	class M_GUBASH_EXPORT__ Input
	{
	public:
		explicit Input();
		~Input() = default;

		void ReadLine();

	private:
		static constexpr uint16_t MAX_SIZE_ = 16384;

		union Data { // SSO
			char str__[MAX_SIZE_];
			Data() : str__{}{} // Constructor for initializing an array.
		} data_;

		size_t size_; // Stores the actual size of the input string.
	};
}