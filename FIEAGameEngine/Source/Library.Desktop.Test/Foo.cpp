#include "pch.h"

using namespace std;

namespace UnitTest
{
	RTTI_DEFINITIONS(Foo)
	Foo::Foo():
		mData(0), mPointerData(nullptr)
	{
		mPointerData = new std::int32_t();
	}

	Foo::Foo(int32_t data, int32_t pointerData):
		mData(data)
	{
		mPointerData = new std::int32_t(pointerData);
	}

	Foo::Foo(const Foo& otherFoo) :
		mData(otherFoo.mData)
	{
		mPointerData = new std::int32_t(*(otherFoo.mPointerData));
	}

	Foo& Foo::operator=(const Foo& otherFoo)
	{
		if (this == &otherFoo)
		{
			return *this;
		}

		else
		{
			mData = otherFoo.mData;
			if (mPointerData != nullptr)
			{
				*mPointerData = *otherFoo.mPointerData;
			}
			else
			{
				mPointerData = new std::int32_t(*otherFoo.mPointerData);
			}
			
			return *this;
		}
	}

	const bool Foo::operator==(const Foo& otherFoo) const 
	{
		bool isEqual;

		if (this == &otherFoo)
		{
			isEqual = true;
		}
		
		else if (mData == otherFoo.mData && *mPointerData == *otherFoo.mPointerData)
		{
			isEqual = true;
		}
		else
		{
			isEqual = false;
		}

		return isEqual;
	}

	const bool Foo::operator!=(const Foo& otherFoo) const
	{
		bool isEqual = (*this == otherFoo);
		return !isEqual;
	}

	Foo::~Foo()
	{
		delete mPointerData;
	}

	const int32_t& Foo::GetData() const
	{
		return mData;
	}

	const int32_t& Foo::GetPointerData() const
	{
		return *mPointerData;
	}

	/*std::uint64_t Foo::TypeIdInstance() const 
	{
		return 1;
	}*/
}