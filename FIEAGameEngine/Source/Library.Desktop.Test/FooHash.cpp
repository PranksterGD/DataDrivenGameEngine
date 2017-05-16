#include "pch.h"

using namespace std;

namespace UnitTest
{
	uint32_t FooHash::operator() (const Foo& key) const
	{
		const std::uint8_t * data = reinterpret_cast<const std::uint8_t *> (&key.GetData());
		const std::uint8_t * data2 = reinterpret_cast<const std::uint8_t *> (&key.GetPointerData());
		std::uint32_t hashReturn = 0;

		for (std::uint32_t i = 0; i < sizeof(key.GetData()); ++i)
		{
			hashReturn += data[i] + 13;
		}

		for (std::uint32_t i = 0; i < sizeof(key.GetPointerData()); ++i)
		{
			hashReturn += data2[i] + 13;
		}

		return hashReturn;
	}
}
