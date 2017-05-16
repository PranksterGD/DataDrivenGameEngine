#pragma once
#include <cstdint>
#include "RTTI.h"
namespace UnitTest
{
	class Foo :public FieaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Foo, FieaGameEngine::RTTI)
	public:

		Foo();
		Foo(std::int32_t data, std::int32_t pointerData);
		Foo(const Foo& otherFoo);

		Foo& operator=(const Foo& otherFoo);

		const bool operator==(const Foo& otherFoo) const;
		const bool operator!=(const Foo& otherFoo) const;

		~Foo();
		const std::int32_t& GetData() const;
		const std::int32_t& GetPointerData() const;
	private:
		std::int32_t mData;
		std::int32_t* mPointerData;
	};
}