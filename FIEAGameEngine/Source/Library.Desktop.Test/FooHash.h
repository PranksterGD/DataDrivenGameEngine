#pragma once
#include "pch.h"

namespace UnitTest
{
	class FooHash
	{
	public:
		std::uint32_t operator() (const Foo& key) const;
	};
}