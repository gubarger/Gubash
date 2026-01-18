// Copyright (c) 2026 Gubarger. All rights reserved.
//
// This file is part of the Gubash project.
// Distributed under the MIT License. See the LICENSE file for details.

#pragma once

#include "../utils/MacrosesPlatform.h"

#include "Input.h"
#include "Prompt.h"

namespace gubash::core
{
	class M_GUBASH_EXPORT__ Gubash
	{
	public:
		explicit Gubash();
		~Gubash() = default;

		void Start();
	private:
		Input input_;
		Prompt prompt_;
	};
} // !gubash::core