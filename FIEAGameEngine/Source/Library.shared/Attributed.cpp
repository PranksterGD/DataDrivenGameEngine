#include "pch.h"

using namespace std;
using namespace FieaGameEngine;


RTTI_DEFINITIONS(Attributed)

Hashmap <std::int64_t, Vector<std::string>> Attributed::PrescribedAttributeList;

Attributed::Attributed(std::int32_t capacity) :
	Scope(capacity)
{
	InitalizeSignatures();
}

Attributed::Attributed(const Attributed& otherAttributed) :
	Scope(otherAttributed)
{
	(*this)["this"] = (static_cast<RTTI*>(this));
}

Attributed::Attributed(Attributed&& otherAttributed) :
	Scope(move(otherAttributed))
{
	(*this)["this"] = (static_cast<RTTI*>(this));
}

Attributed& Attributed::operator=(const Attributed& otherAttributed)
{
	Scope::operator=(otherAttributed);
	(*this)["this"] = (static_cast<RTTI*>(this));
	return *this;
}

Attributed& Attributed::operator=(Attributed&& otherAttributed)
{
	Scope::operator=(move(otherAttributed));
	(*this)["this"] = (static_cast<RTTI*>(this));
	return *this;
}

bool Attributed::IsPrescribedAttribute(const std::string& key) const
{
	Vector<string> prescribedAttributeList = PrescribedAttributeList[TypeIdInstance()];
	return(prescribedAttributeList.Find(key) != prescribedAttributeList.end() && IsAttribute(key));
}

bool Attributed::IsAuxiliaryAttribute(const std::string& key) const
{
	return (IsAttribute(key) && !IsPrescribedAttribute(key));
}

bool Attributed::IsAttribute(const std::string& key) const
{
	return Find(key) != nullptr;
}

Datum&  Attributed::AppendAuxiliaryAttribute(const std::string& key)
{
	if (IsPrescribedAttribute(key))
	{
		throw exception("Is already a prescribed attribute");
	}

	return Append(key);
}

void Attributed::AddInternalAttribute(const std::string& key, int32_t defaultValue, uint32_t size)
{
	Datum& datum = Append(key);

	datum.Clear();

	for (uint32_t i = 0; i < size; ++i)
	{
		datum.PushBack(defaultValue);
	}

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddInternalAttribute(const std::string& key, float defaultValue, uint32_t size)
{
	Datum& datum = Append(key);

	datum.Clear();

	for (uint32_t i = 0; i < size; ++i)
	{
		datum.PushBack(defaultValue);
	}

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddInternalAttribute(const std::string& key, const std::string& defaultValue, uint32_t size)
{
	Datum& datum = Append(key);

	datum.Clear();

	for (uint32_t i = 0; i < size; ++i)
	{
		datum.PushBack(defaultValue);
	}

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddInternalAttribute(const std::string& key, const glm::vec4& defaultValue, uint32_t size)
{
	Datum& datum = Append(key);

	datum.Clear();

	for (uint32_t i = 0; i < size; ++i)
	{
		datum.PushBack(defaultValue);
	}

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddInternalAttribute(const std::string& key, const glm::mat4& defaultValue, uint32_t size)
{
	Datum& datum = Append(key);
	
	datum.Clear();

	for (uint32_t i = 0; i < size; ++i)
	{
		datum.PushBack(defaultValue);
	}

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddInternalAttribute(const std::string& key, RTTI* defaultValue, uint32_t size)
{
	Datum& datum = Append(key);

	datum.Clear();

	for (uint32_t i = 0; i < size; ++i)
	{
		datum.PushBack(defaultValue);
	}

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddExternalAttribute(const std::string& key, int32_t* value, uint32_t size)
{
	Datum& datum = Append(key);

	datum.SetStorage(value, size);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddExternalAttribute(const std::string& key, float* value, uint32_t size)
{
	Datum& datum = Append(key);
	datum.SetStorage(value, size);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddExternalAttribute(const std::string& key, string* value, uint32_t size)
{
	Datum& datum = Append(key);
	datum.SetStorage(value, size);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddExternalAttribute(const std::string& key, glm::vec4* value, uint32_t size)
{
	Datum& datum = Append(key);
	datum.SetStorage(value, size);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddExternalAttribute(const std::string& key, glm::mat4* value, uint32_t size)
{
	Datum& datum = Append(key);
	datum.SetStorage(value, size);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddExternalAttribute(const std::string& key, RTTI** value, uint32_t size)
{
	Datum& datum = Append(key);
	datum.SetStorage(value, size);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

Scope& Attributed::AddScopeAttribute(const std::string&key)
{
	Scope& scope = AppendScope(key);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}

	return scope;
}

void Attributed::AddScopeAttribute(const std::string&key, Scope& scope)
{
	Adopt(scope, key);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddEmptyScopeAttribute(const std::string&key)
{
	Append(key).SetType(DatumType::TABLE);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::AddEmptyStringAttribute(const std::string&key)
{
	Append(key).SetType(DatumType::STRING);

	if (!IsPrescribedAttribute(key))
	{
		PrescribedAttributeList[TypeIdInstance()].PushBack(key);
	}
}

void Attributed::ClearPrescribedAttributes()
{
	PrescribedAttributeList.Clear();
}

Vector<string>& Attributed::GetPrescribedAttributes()
{
	return PrescribedAttributeList[TypeIdInstance()];
}

Vector<std::pair<std::string, Datum>*> Attributed::GetAuxiliaryAttributes() const
{
	Vector<std::pair<std::string, Datum>*> returnVector;

	for (auto& entry : GetEntries())
	{
		if (!IsPrescribedAttribute(entry->first))
		{
			returnVector.PushBack(entry);
		}
	}

	return returnVector;
}

void Attributed::InitalizeSignatures()
{
	AddInternalAttribute("this", static_cast<RTTI*>(this), 1);
}

bool Attributed::operator==(const Attributed& otherAttributed) const
{
	bool isEqual = otherAttributed.mTable.Size() == mTable.Size();

	if (isEqual)
	{
		for (EntryType& value : otherAttributed.mTable)
		{
			Iterator it = mTable.Find(value.first);
			if (it == mTable.end() || (value.first != "this" && value.second != it->second ))
			{
				isEqual = false;
				break;
			}
		}
	}

	return isEqual;
}

bool Attributed::operator!=(const Attributed& otherAttributed) const
{
	return !(*this == otherAttributed);
}

bool Attributed::Equals(const RTTI* rhs) const
{
	if (this == rhs)
	{
		return true;
	}

	if (rhs == nullptr)
	{
		return false;
	}

	if (!rhs->Is(TypeIdClass()))
	{
		return false;
	}

	return *this == *(rhs->As<Attributed>());
}

Scope* Attributed::Copy() const
{
	return new Attributed(*this);
}


