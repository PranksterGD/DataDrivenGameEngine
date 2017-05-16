#include "pch.h"
#include "Datum.h"
#include "Scope.h"
using namespace std;
using namespace FieaGameEngine;

Datum::Datum() :
	mSize(0), mCapacity(0), mDatumType(DatumType::INVALID), mIsExternal(false)
{
		mDatum.voidPointer = nullptr;
}

Datum::Datum(const Datum& otherDatum) :
	Datum()
{
	*this = otherDatum;
}

Datum::Datum(Datum&& otherDatum) :
	mSize(otherDatum.mSize), mCapacity(otherDatum.mCapacity), mDatumType(otherDatum.mDatumType),
	mIsExternal(otherDatum.mIsExternal), mDatum(otherDatum.mDatum)
{
	otherDatum.mSize = 0;
	otherDatum.mCapacity = 0;
	otherDatum.mDatumType = DatumType::INVALID;
	otherDatum.mIsExternal = false;
	otherDatum.mDatum.voidPointer = nullptr;
}

Datum& Datum::operator=(const Datum& otherDatum)
{
	if (this != &otherDatum)
{
	Clear();

	mDatumType = otherDatum.mDatumType;

	if (otherDatum.mIsExternal)
	{
		mSize = otherDatum.mSize;
		mCapacity = otherDatum.mCapacity;
		mDatum.intArray = otherDatum.mDatum.intArray;
	}
	else
	{
		Reserve(otherDatum.mCapacity);

		for (uint32_t i = 0; i < otherDatum.mSize; ++i)
		{
			switch (mDatumType)
			{
			case DatumType::INTEGER:
				PushBack(otherDatum.mDatum.intArray[i]);
				break;

			case DatumType::FLOAT:
				PushBack(otherDatum.mDatum.floatArray[i]);
				break;

			case DatumType::VECTOR:
				PushBack(otherDatum.mDatum.vectorArray[i]);
				break;

			case DatumType::MATRIX:
				PushBack(otherDatum.mDatum.matrixArray[i]);
				break;
			case DatumType::STRING:
				PushBack(otherDatum.mDatum.stringArray[i]);
				break;

			case DatumType::POINTER:
				PushBack(otherDatum.mDatum.RTTIArray[i]);
				break;

			case DatumType::TABLE:
				PushBack(otherDatum.mDatum.ScopeArray[i]);
				break;
			}
		}
	}

	mIsExternal = otherDatum.mIsExternal;
}
	

	return *this;
}

Datum& Datum::operator=(Datum&& otherDatum)
{
	if (this != &otherDatum)
	{
		Clear();

		mDatumType = otherDatum.mDatumType;
		mSize = otherDatum.mSize;
		mCapacity = otherDatum.mCapacity;
		mDatum.voidPointer = otherDatum.mDatum.voidPointer;
		mIsExternal = otherDatum.mIsExternal;

		otherDatum.mDatum.voidPointer = nullptr;
		otherDatum.mSize = 0;
		otherDatum.mCapacity = 0;
		otherDatum.mDatumType = DatumType::INVALID;
		otherDatum.mIsExternal = false;
	}
	return *this;
}

Datum::~Datum()
{
	if (!mIsExternal)
	{
		Clear();
	}
}

void Datum::Clear()
{
	if (!mIsExternal)
	{
		for (uint32_t i = 0; i < mSize; ++i)
		{
			switch (mDatumType)
			{
			case DatumType::INTEGER:
				mDatum.intArray[i].int32_t::~int32_t();
				break;

			case DatumType::VECTOR:
				mDatum.vectorArray[i].glm::vec4::~vec4();
				break;

			case DatumType::MATRIX:
				mDatum.matrixArray[i].glm::mat4::~mat4();
				break;

			case DatumType::STRING:
				mDatum.stringArray[i].~string();
				break;
			}
		}
		free(mDatum.voidPointer);
	}

	mSize = 0;
	mCapacity = 0;
	mDatumType = DatumType::INVALID;
	mIsExternal = false;
	mDatum.voidPointer = nullptr;
}

const DatumType& Datum::Type() const
{
	return mDatumType;
}

void Datum::SetType(const DatumType& type)
{
	if (mDatumType != DatumType::INVALID && mDatumType != type)
	{
		throw exception("Cannot reset type");
	}

	mDatumType = type;
}

uint32_t Datum::Size() const
{
	return mSize;
}

uint32_t Datum::Capacity() const
{
	return mCapacity;
}

template<>
 std::int32_t& Datum::Get<std::int32_t&>(uint32_t index)
{	
	return const_cast<std::int32_t&>(const_cast<const Datum*> (this)->Get<const int32_t&>(index));
}

template<>
float& Datum::Get<float&>(uint32_t index)
{
	return const_cast<float&>(const_cast<const Datum*> (this)->Get<const float&>(index));
}

template<>
string& Datum::Get<string&>(uint32_t index)
{
	return const_cast<std::string&>(const_cast<const Datum*> (this)->Get<const string&>(index));
}

template<>
glm::vec4& Datum::Get<glm::vec4&>(uint32_t index)
{
	return const_cast<glm::vec4&>(const_cast<const Datum*> (this)->Get<const glm::vec4&>(index));
}

template<>
glm::mat4& Datum::Get<glm::mat4&>(uint32_t index)
{
	return const_cast<glm::mat4&>(const_cast<const Datum*> (this)->Get<const glm::mat4&>(index));
}

template<>
RTTI*& Datum::Get<RTTI*&>(uint32_t index)
{
	return const_cast<RTTI*&>(const_cast<const Datum*> (this)->Get<const RTTI*&>(index));
}

template<>
Scope*& Datum::Get<Scope*&>(uint32_t index)
{
	return const_cast<Scope*&>(const_cast<const Datum*> (this)->Get<const Scope*&>(index));
}

template<>
const RTTI*& Datum::Get<const RTTI*&>(uint32_t index) const
{
	if (index >= mSize)
	{
		throw exception("Index out bounds");
	}

	if (mDatumType != DatumType::POINTER)
	{
		throw exception("Incorrect type");
	}

	return const_cast<const RTTI*&>((mDatum.RTTIArray[index]));
}

template<>
const Scope*& Datum::Get<const Scope*&>(uint32_t index) const
{
	if (index >= mSize)
	{
		throw exception("Index out bounds");
	}

	if (mDatumType != DatumType::TABLE)
	{
		throw exception("Incorrect type");
	}

	return const_cast<const Scope*&>((mDatum.ScopeArray[index]));
}

template<>
const int32_t& Datum::Get<const int32_t&>(uint32_t index) const
{
	if (index >= mSize)
	{
		throw exception("Index out bounds");
	}

	if (mDatumType != DatumType::INTEGER)
	{
		throw exception("Incorrect type");
	}

	return mDatum.intArray[index];
}

template<>
const float& Datum::Get<const float&>(uint32_t index) const
{
	if (index >= mSize)
	{
		throw exception("Index out bounds");
	}

	if (mDatumType != DatumType::FLOAT)
	{
		throw exception("Incorrect type");
	}

	return mDatum.floatArray[index];
}

template<>
const string& Datum::Get<const string&>(uint32_t index) const
{
	if (index >= mSize)
	{
		throw exception("Index out bounds");
	}

	if (mDatumType != DatumType::STRING)
	{
		throw exception("Incorrect type");
	}

	return mDatum.stringArray[index];
}

template<>
const glm::vec4& Datum::Get<const glm::vec4&>(uint32_t index) const
{
	if (index >= mSize)
	{
		throw exception("Index out bounds");
	}

	if (mDatumType != DatumType::VECTOR)
	{
		throw exception("Incorrect type");
	}
	return mDatum.vectorArray[index];

}

template<>
const glm::mat4& Datum::Get<const glm::mat4&>(uint32_t index) const
{
	if (index >= mSize)
	{
		throw exception("Index out bounds");
	}

	if (mDatumType != DatumType::MATRIX)
	{
		throw exception("Incorrect type");
	}
	return mDatum.matrixArray[index];
}

void Datum::Set(const std::int32_t& value, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::INTEGER;
	}

	if (mDatumType != DatumType::INTEGER)
	{
		throw exception("Incorrect type.");
	}

	if (index >= mSize)
	{
		throw exception("Index out of bounds.");
	}

	mDatum.intArray[index] = value;
}

void Datum::Set(const float& value, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::FLOAT;
	}

	if (mDatumType != DatumType::FLOAT)
	{
		throw exception("Incorrect type.");
	}

	if (index >= mSize)
	{
		throw exception("Index out of bounds.");
	}

	mDatum.floatArray[index] = value;
}

void Datum::Set(const std::string& value, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::STRING;
	}

	if (mDatumType != DatumType::STRING)
	{
		throw exception("Incorrect type.");
	}

	if (index >= mSize)
	{
		throw exception("Index out of bounds.");
	}

	mDatum.stringArray[index] = value;
}

void Datum::Set(const glm::vec4& value, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::VECTOR;
	}

	if (mDatumType != DatumType::VECTOR)
	{
		throw exception("Incorrect type.");
	}

	if (index >= mSize)
	{
		throw exception("Index out of bounds.");
	}

	mDatum.vectorArray[index] = value;
}

void Datum::Set(const glm::mat4& value, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::MATRIX;
	}

	if (mDatumType != DatumType::MATRIX)
	{
		throw exception("Incorrect type.");
	}

	if (index >= mSize)
	{
		throw exception("Index out of bounds.");
	}

	mDatum.matrixArray[index] = value;
}

void Datum::Set(RTTI* value, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::POINTER;
	}

	if (mDatumType != DatumType::POINTER)
	{
		throw exception("Incorrect type.");
	}

	if (index >= mSize)
	{
		throw exception("Index out of bounds.");
	}

	mDatum.RTTIArray[index] = value;
}

void Datum::Set(Scope* value, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::TABLE;
	}

	if (mDatumType != DatumType::TABLE)
	{
		throw exception("Incorrect type.");
	}

	if (index >= mSize)
	{
		throw exception("Index out of bounds.");
	}

	mDatum.ScopeArray[index] = value;
}

void Datum::PushBack(const std::int32_t& value)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::INTEGER;
	}

	if (mDatumType != DatumType::INTEGER)
	{
		throw exception("Incorrect type");
	}

	if (mSize == mCapacity)
	{
		uint32_t newCapacity = 2 * mCapacity + 1;
		Reserve(newCapacity);
	}
	new (mDatum.intArray + mSize) int32_t(value);
	++mSize;
}

void Datum::PushBack(const float& value)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::FLOAT;
	}

	if (mDatumType != DatumType::FLOAT)
	{
		throw exception("Incorrect type");
	}

	if (mSize == mCapacity)
	{
		uint32_t newCapacity = 2 * mCapacity + 1;
		Reserve(newCapacity);
	}
	new (mDatum.floatArray + mSize) float(value);
	++mSize;
}

void Datum::PushBack(const std::string& value)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::STRING;
	}

	if (mDatumType != DatumType::STRING)
	{
		throw exception("Incorrect type");
	}

	if (mSize == mCapacity)
	{
		Reserve(2 * mCapacity + 1);
	}
	new (mDatum.stringArray + mSize) string(value);
	++mSize;
}

void Datum::PushBack(const glm::vec4& value)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::VECTOR;
	}

	if (mDatumType != DatumType::VECTOR)
	{
		throw exception("Incorrect type");
	}

	if (mSize == mCapacity)
	{
		uint32_t newCapacity = 2 * mCapacity + 1;
		Reserve(newCapacity);
	}
	new (mDatum.vectorArray + mSize) glm::vec4(value);
	++mSize;
}

void Datum::PushBack(const glm::mat4& value)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::MATRIX;
	}

	if (mDatumType != DatumType::MATRIX)
	{
		throw exception("Incorrect type");
	}

	if (mSize == mCapacity)
	{
		uint32_t newCapacity = 2 * mCapacity + 1;
		Reserve(newCapacity);
	}
	new (mDatum.matrixArray + mSize) glm::mat4(value);
	++mSize;
}

void Datum::PushBack(RTTI* value)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::POINTER;
	}

	if (mDatumType != DatumType::POINTER)
	{
		throw exception("Incorrect type");
	}

	if (mSize == mCapacity)
	{
		uint32_t newCapacity = 2 * mCapacity + 1;
		Reserve(newCapacity);
	}
	new (mDatum.RTTIArray + mSize) RTTI*(value);
	++mSize;
}

void Datum::PushBack(Scope* value)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::TABLE;
	}

	if (mDatumType != DatumType::TABLE)
	{
		throw exception("Incorrect type");
	}

	if (mSize == mCapacity)
	{
		uint32_t newCapacity = 2 * mCapacity + 1;
		Reserve(newCapacity);
	}
	new (mDatum.ScopeArray + mSize) Scope*(value);
	++mSize;
}

Datum& Datum::operator=(const int32_t& value)
{
	if (mSize == 0)
	{
		PushBack(value);
	}
	else
	{
		Set(value);
	}

	return *this;
}

Datum& Datum::operator=(const float& value)
{
	if (mSize == 0)
	{
		PushBack(value);
	}
	else
	{
		Set(value);
	}

	return *this;
}

Datum& Datum::operator=(const string& value)
{
	if (mSize == 0)
	{
		PushBack(value);
	}
	else
	{
		Set(value);
	}

	return *this;
}

Datum& Datum::operator=(const glm::vec4& value)
{
	if (mSize == 0)
	{
		PushBack(value);
	}
	else
	{
		Set(value);
	}

	return *this;
}

Datum& Datum::operator=(const glm::mat4& value)
{
	if (mSize == 0)
	{
		PushBack(value);
	}
	else
	{
		Set(value);
	}

	return *this;
}

Datum& Datum::operator=(RTTI* value)
{
	if (mSize == 0)
	{
		PushBack(value);
	}
	else
	{
		Set(value);
	}

	return *this;
}

Datum& Datum::operator=(Scope* value)
{
	if (mSize == 0)
	{
		PushBack(value);
	}
	else
	{
		Set(value);
	}

	return *this;
}

bool Datum::operator==(const Datum& otherDatum) const
{
	bool isEqual = true;

	if (mDatumType == otherDatum.mDatumType &&
		mSize == otherDatum.mSize)
	{
		for (uint32_t i = 0; i < mSize; ++i)
		{
			switch (mDatumType)
			{
			case DatumType::INVALID:
				break;

			case DatumType::INTEGER:
				if (mDatum.intArray[i] != otherDatum.mDatum.intArray[i])
				{
					isEqual = false;
					break;
				}
				break;

			case DatumType::FLOAT:
				if (mDatum.floatArray[i] != otherDatum.mDatum.floatArray[i])
				{
					isEqual = false;
					break;
				}
				break;

			case DatumType::VECTOR:
				if (mDatum.vectorArray[i] != otherDatum.mDatum.vectorArray[i])
				{
					isEqual = false;
					break;
				}
				break;

			case DatumType::MATRIX:
				if (mDatum.matrixArray[i] != otherDatum.mDatum.matrixArray[i])
				{
					isEqual = false;
					break;
				}
				break;

			case DatumType::STRING:
				if (mDatum.stringArray[i] != otherDatum.mDatum.stringArray[i])
				{
					isEqual = false;
					break;
				}
				break;

			case DatumType::POINTER:
				if (mDatum.RTTIArray[i] != nullptr)
				{
					if(mDatum.RTTIArray[i] != otherDatum.mDatum.RTTIArray[i])
					{
						isEqual = false;
						break;
					}
				}

				break;

			case DatumType::TABLE:
				if (mDatum.ScopeArray[i] != nullptr)
				{
					if (!(mDatum.ScopeArray[i]->Equals(otherDatum.mDatum.ScopeArray[i])))
					{
						isEqual = false;
						break;
					}
				}

				break;
			}
		}
	}
	else
	{
		isEqual = false;
	}

	return isEqual;
}

bool Datum::operator==(const int32_t& value)  const
{
	return (mDatumType == DatumType::INTEGER &&
		mSize == 1 &&
		mDatum.intArray[0] == value);
			
}

bool Datum::operator==(const float& value)  const
{
	return (mDatumType == DatumType::FLOAT &&
		mSize == 1 &&
		mDatum.floatArray[0] == value);

}

bool Datum::operator==(const string& value)  const
{
	return (mDatumType == DatumType::STRING &&
		mSize == 1 &&
		mDatum.stringArray[0] == value);
}

bool Datum::operator==(const glm::vec4& value)  const
{
	return (mDatumType == DatumType::VECTOR &&
		mSize == 1 &&
		mDatum.vectorArray[0] == value);
}

bool Datum::operator==(const glm::mat4& value)  const
{
	return (mDatumType == DatumType::MATRIX &&
		mSize == 1 &&
		mDatum.matrixArray[0] == value);
}

bool Datum::operator==(const RTTI* value)  const
{
	return (mDatumType == DatumType::POINTER &&
		mSize == 1 && mDatum.RTTIArray[0]!=nullptr &&
		mDatum.RTTIArray[0]->Equals(value));
}

bool Datum::operator==(const Scope& value)  const
{
	return( mDatumType == DatumType::TABLE &&
		mSize == 1 && mDatum.ScopeArray[0] != nullptr &&
		(mDatum.ScopeArray[0])->Equals(&value));
}

bool Datum::operator!=(const Datum& otherDatum) const
{
	return !(*this == otherDatum);
}

bool Datum::operator!=(const int32_t& value) const
{
	return !(*this == value);
}

bool Datum::operator!=(const float& value) const
{
	return !(*this == value);
}

bool Datum::operator!=(const string& value) const
{
	return !(*this == value);
}

bool Datum::operator!=(const glm::vec4& value) const
{
	return !(*this == value);
}

bool Datum::operator!=(const glm::mat4& value) const
{
	return !(*this == value);
}

bool Datum::operator!=(const RTTI* value) const
{
	return !(*this == value);
}

bool Datum::operator!=(const Scope& value) const
{
	return !(*this == value);
}

void Datum::SetStorage(int32_t* newArray, uint32_t size)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::INTEGER;
	}

	if (mDatumType != DatumType::INTEGER)
	{
		throw exception("Incorrect type");
	}

	if (size == 0)
	{
		throw exception("Size cannot be zero");
	}

	Clear();

	mDatumType = DatumType::INTEGER;

	if (!mIsExternal)
	{
		free(mDatum.intArray);
	}

	mDatum.intArray = newArray;
	mSize = size;
	mCapacity = size;
	mIsExternal = true;
}

void Datum::SetStorage(float* newArray, uint32_t size)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::FLOAT;
	}

	if (mDatumType != DatumType::FLOAT)
	{
		throw exception("Incorrect type");
	}

	if (size == 0)
	{
		throw exception("Size cannot be zero");
	}

	Clear();

	if (!mIsExternal)
	{
		free(mDatum.floatArray);
	}

	mDatumType = DatumType::FLOAT;

	mDatum.floatArray = newArray;
	mSize = size;
	mCapacity = size;
	mIsExternal = true;
}

void Datum::SetStorage(string* newArray, uint32_t size)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::STRING;
	}

	if (mDatumType != DatumType::STRING)
	{
		throw exception("Incorrect type");
	}

	if (size == 0)
	{
		throw exception("Size cannot be zero");
	}

	Clear();

	mDatumType = DatumType::STRING;

	if (!mIsExternal)
	{
		free(mDatum.stringArray);
	}

	mDatum.stringArray = newArray;
	mSize = size;
	mCapacity = size;
	mIsExternal = true;
}

void Datum::SetStorage(glm::vec4* newArray, uint32_t size)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::VECTOR;
	}

	if (mDatumType != DatumType::VECTOR)
	{
		throw exception("Incorrect type");
	}

	if (size == 0)
	{
		throw exception("Size cannot be zero");
	}

	Clear();

	mDatumType = DatumType::VECTOR;

	if (!mIsExternal)
	{
		free(mDatum.vectorArray);
	}

	mDatum.vectorArray = newArray;
	mSize = size;
	mCapacity = size;
	mIsExternal = true;
}

void Datum::SetStorage(glm::mat4* newArray, uint32_t size)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::MATRIX;
	}

	if (mDatumType != DatumType::MATRIX)
	{
		throw exception("Incorrect type");
	}

	if (size == 0)
	{
		throw exception("Size cannot be zero");
	}

	Clear();

	mDatumType = DatumType::MATRIX;

	if (!mIsExternal)
	{
		free(mDatum.matrixArray);
	}

	mDatum.matrixArray = newArray;
	mSize = size;
	mCapacity = size;
	mIsExternal = true;
}

void Datum::SetStorage(RTTI** newArray, uint32_t size)
{
	if (mDatumType == DatumType::INVALID)
	{
		mDatumType = DatumType::POINTER;
	}

	if (mDatumType != DatumType::POINTER)
	{
		throw exception("Incorrect type");
	}

	if (size == 0)
	{
		throw exception("Size cannot be zero");
	}

	Clear();

	mDatumType = DatumType::POINTER;

	if (!mIsExternal)
	{
		free(mDatum.RTTIArray);
	}

	mDatum.RTTIArray = newArray;
	mSize = size;
	mCapacity = size;
	mIsExternal = true;
}

void Datum::ReSize(uint32_t size)
{
	if (mDatumType == DatumType::INVALID)
	{
		throw exception("Invalid type");
	}

	if (mIsExternal)
	{
		throw exception("Cannot resize external");
	}

	if (size > mCapacity)
	{
		Reserve(size);
	}

	if (size > mSize)
	{
		for (uint32_t i = mSize; i < mCapacity; ++i)
		{
			switch (mDatumType)
			{
			case DatumType::INTEGER:
				PushBack(int32_t());
				break;

			case DatumType::FLOAT:
				PushBack(float());
				break;

			case DatumType::VECTOR:
				PushBack(glm::vec4());
				break;

			case DatumType::MATRIX:
				PushBack(glm::mat4());
				break;

			case DatumType::STRING:
				PushBack(string());
				break;

			case DatumType::POINTER:
				PushBack(static_cast<RTTI*> (nullptr));
				break;

			case DatumType::TABLE:
				PushBack(static_cast<Scope*>(nullptr));
				break;
			}
		}
	}
	else
	{
		for (uint32_t i = mSize - 1; i >= size; --i)
		{
			switch (mDatumType)
			{
			case DatumType::INTEGER:
				mDatum.intArray[i].int32_t::~int32_t();
				break;

			case DatumType::VECTOR:
				mDatum.vectorArray[i].glm::vec4::~vec4();
				break;

			case DatumType::MATRIX:
				mDatum.matrixArray[i].glm::mat4::~mat4();
				break;

			case DatumType::STRING:
				mDatum.stringArray[i].string::~string();
				break;
			}
		}
	}

	mSize = size;
}

void Datum::Reserve(const std::uint32_t newCapacity)
{


	if (mIsExternal)
	{
		throw exception("Cannot resize external storage");
	}

	if (newCapacity > mCapacity)
	{
		mCapacity = newCapacity;

		if (mDatumType == DatumType::INVALID)
		{
			throw exception("Cannot reserve memory for invalid type.");
		}

		switch (mDatumType)
		{
		case DatumType::INTEGER:
			mDatum.voidPointer = (realloc(mDatum.intArray, sizeof(int32_t)*mCapacity));
			break;

		case DatumType::FLOAT:
			mDatum.voidPointer = (realloc(mDatum.intArray, sizeof(float)*mCapacity));
			break;

		case DatumType::VECTOR:
			mDatum.voidPointer = (realloc(mDatum.vectorArray, sizeof(glm::vec4)*mCapacity));
			break;

		case DatumType::MATRIX:
			mDatum.voidPointer = (realloc(mDatum.matrixArray, sizeof(glm::mat4)*mCapacity));
			break;

		case DatumType::STRING:
			mDatum.voidPointer = (realloc(mDatum.vectorArray, sizeof(string)*mCapacity));
			break;

		case DatumType::POINTER:
			mDatum.voidPointer = (realloc(mDatum.vectorArray, sizeof(RTTI*)*mCapacity));
			break;

		case DatumType::TABLE:
			mDatum.voidPointer = (realloc(mDatum.vectorArray, sizeof(Scope*)*mCapacity));
			break;
		}
	}
}

string Datum::ToString(std::uint32_t index)
{
	string returnString;
	char buffer[200];
	int32_t intValue;
	float floatValue;
	glm::vec4 vectorValue;
	glm::mat4 matrixValue;
	string stringValue;
	RTTI* pointerValue;
	Scope* scopeValue;
	switch (mDatumType)
	{

	case DatumType::INVALID:
		throw exception("Cannot to string on invalid type");
		break;

	case DatumType::INTEGER:
		intValue = Get<int32_t&>(index);
		sprintf_s(buffer, "%d", intValue);
		returnString = buffer;
		break;

	case DatumType::FLOAT:	
		floatValue = Get<float&>(index);
		sprintf_s(buffer, "%f", floatValue);
		returnString = buffer;
		break;

	case DatumType::VECTOR:
		vectorValue = Get<glm::vec4&>(index);
		sprintf_s(buffer, "%f, %f, %f, %f", vectorValue[0], vectorValue[1], vectorValue[2], vectorValue[3]);
		returnString = buffer;
		break;

	case DatumType::MATRIX:
		matrixValue = Get<glm::mat4&>(index);
		for (int32_t i = 0; i < 4; ++i)
			for (int32_t j = 0; j < 4; ++j)
			{
				sprintf_s(buffer, "%f, ", matrixValue[i][j]);
				returnString += buffer;
			}
		break;

	case DatumType::STRING:
		stringValue = Get<string&>(index);
		returnString = stringValue;
		break;

	case DatumType::POINTER:
		pointerValue = Get<RTTI*&>(index);
		sprintf_s(buffer, "%p", pointerValue);
		returnString = buffer;
		break;

	case DatumType::TABLE:
		scopeValue = Get<Scope*&>(index);
		sprintf_s(buffer, "%p", scopeValue);
		returnString = buffer;
		break;
	}
	return returnString;
}

void Datum::SetFromString(const std::string& valueToParse, std::uint32_t index)
{
	if (mDatumType == DatumType::INVALID)
	{
		throw exception("Type not set");
	}

	const char* input;
	input = valueToParse.c_str();

	int32_t intValue;
	float floatValue;
	glm::vec4 vectorValue;
	glm::mat4 matrixValue;
	string stringValue;

	int32_t count = 0;

	switch (mDatumType)
	{
	case DatumType::INTEGER:
		count=sscanf_s(input, "%d", &intValue);
		if (count != 1)
		{
			throw exception("Could not parse string");
		}
		Set(intValue, index);
		break;

	case DatumType::FLOAT:
		count = sscanf_s(input, "%f", &floatValue);
		if (count != 1)
		{
			throw exception("Could not parse string");
		}
		Set(floatValue, index);
		break;

	case DatumType::VECTOR:
		count = sscanf_s(input, "%f,%f,%f,%f", &vectorValue[0], &vectorValue[1], &vectorValue[2], &vectorValue[3]);
		if (count != 4)
		{
			throw exception("Could not parse string");
		}
		Set(vectorValue, index);
		break;

	case DatumType::MATRIX:
		count = sscanf_s(input, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			&matrixValue[0][0], &matrixValue[0][1], &matrixValue[0][2], &matrixValue[0][3],
			&matrixValue[1][0], &matrixValue[1][1], &matrixValue[1][2], &matrixValue[1][3],
			&matrixValue[2][0], &matrixValue[2][1], &matrixValue[2][2], &matrixValue[2][3],
			&matrixValue[3][0], &matrixValue[3][1], &matrixValue[3][2], &matrixValue[3][3]);

		if (count != 16)
		{
			throw exception("Could not parse string");
		}
		Set(matrixValue, index);
		break;

	case DatumType::STRING:
		Set(valueToParse, index);
		break;
	}
}

void Datum::PushBackFromString(const std::string& valueToParse)
{
	if (mDatumType == DatumType::INVALID)
	{
		throw exception("Type not set");
	}

	const char* input;
	input = valueToParse.c_str();

	int32_t intValue;
	float floatValue;
	glm::vec4 vectorValue;
	glm::mat4 matrixValue;
	string stringValue;

	int32_t count = 0;

	switch (mDatumType)
	{
	case DatumType::INTEGER:
		count = sscanf_s(input, "%d", &intValue);
		if (count != 1)
		{
			throw exception("Could not parse string");
		}
		PushBack(intValue);
		break;

	case DatumType::FLOAT:
		count = sscanf_s(input, "%f", &floatValue);
		if (count != 1)
		{
			throw exception("Could not parse string");
		}
		PushBack(floatValue);
		break;

	case DatumType::VECTOR:
		count = sscanf_s(input, "%f, %f, %f, %f", &vectorValue[0], &vectorValue[1], &vectorValue[2], &vectorValue[3]);
		if (count != 4)
		{
			throw exception("Could not parse string");
		}
		PushBack(vectorValue);
		break;

	case DatumType::MATRIX:
		count = sscanf_s(input, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			&matrixValue[0][0], &matrixValue[0][1], &matrixValue[0][2], &matrixValue[0][3],
			&matrixValue[1][0], &matrixValue[1][1], &matrixValue[1][2], &matrixValue[1][3],
			&matrixValue[2][0], &matrixValue[2][1], &matrixValue[2][2], &matrixValue[2][3],
			&matrixValue[3][0], &matrixValue[3][1], &matrixValue[3][2], &matrixValue[3][3]);

		if (count != 16)
		{
			throw exception("Could not parse string");
		}
		PushBack(matrixValue);
		break;

	case DatumType::STRING:
		PushBack(valueToParse);
		break;
	}
}

bool Datum::Remove(Scope* value)
{
	bool removed = false;

	if (mDatumType == DatumType::TABLE)
	{
		uint32_t findInt;

		for (findInt = 0; findInt < mSize; ++findInt)
		{
			if (Get<Scope*&>(findInt) == value)
			{
				break;
			}
		}

		uint32_t workFindInt = findInt;
		if (findInt != mSize)
		{
			while (++workFindInt != mSize)
			{
				Set(Get<Scope*&>(workFindInt), findInt);
				++findInt;
			}
			Set(static_cast<Scope*> (nullptr), findInt);
			--mSize;
			removed = true;
		}
	}

	return removed;
}

bool Datum::IsExternal() const
{
	return mIsExternal;
}
