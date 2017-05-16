#include "pch.h"
#include "Scope.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(Scope)

Scope::Scope(std::int32_t capacity) :
	mOrderArray(capacity), mTable(capacity), mParent(nullptr)
{

}



Scope::Scope(const Scope& otherScope) :
	Scope()
{
	*this = otherScope;
}

Scope::Scope(Scope&& otherScope) :
	mParent(otherScope.mParent), mTable(move(otherScope.mTable)), mOrderArray(move(otherScope.mOrderArray))
{
	Reparent(otherScope);
	otherScope.mParent = nullptr;
}

Scope& Scope::operator=(const Scope& otherScope)
{
	if (this != &otherScope)
	{
		Clear();

		for (auto value : otherScope.mOrderArray)
		{
			if (value->second.Type() != DatumType::TABLE)
			{
				Iterator it = mTable.Insert(*value);
				mOrderArray.PushBack(&*it);
			}
			else
			{
				Datum& datum = Append(value->first);
				datum.SetType(DatumType::TABLE);

				for (uint32_t i = 0; i < value->second.Size(); ++i)
				{
					Scope* scope = value->second.Get<Scope*&>(i)->Copy();
					scope->mParent = this;
					datum.PushBack(scope);
				}
			}
		}
	}

	return *this;
}

Scope& Scope::operator=(Scope&& otherScope)
{
	if (this != &otherScope)
	{
		Clear();

		mOrderArray = move(otherScope.mOrderArray);
		mTable = move(otherScope.mTable);
		mParent = otherScope.mParent;

		Reparent(otherScope);
		otherScope.mParent = nullptr;	
	}
	return *this;
}

Scope::~Scope()
{
	if (mParent != nullptr)
	{
		mParent->Orphan(*this);
	}
	Clear();
}

void Scope::Clear()
{
	for (EntryType* value : mOrderArray)
	{
		Datum& datum = value->second;

		if (datum.Type() == DatumType::TABLE)
		{
			while (datum.Size() > 0)
			{
				delete(datum.Get<Scope*&>(0));
			}
		}
	}

	mTable.Clear();
	mOrderArray.Clear();
}

Datum* Scope::Find(const std::string& key)
{
	return const_cast<Datum*> (const_cast<const Scope*>(this)->Find(key));
}

const Datum* Scope::Find(const std::string& key) const
{
	Iterator it = mTable.Find(key);
	Datum* returnPointer = nullptr;

	if (it != mTable.end())
	{
		returnPointer = &(it->second);
	}

	return returnPointer;
}

Datum* Scope::Search(const std::string& key, Scope** returnScope)
{
	return const_cast<Datum*> (const_cast<const Scope*>(this)->Search(key, returnScope));
}

const Datum* Scope::Search(const std::string& key, Scope** returnScope) const
{
	Datum* returnDatum;
	Scope* foundScope = const_cast<Scope*> (this);

	do
	{
		returnDatum = foundScope->Find(key);

		if (returnDatum != nullptr)
		{
			break;
		}

		foundScope = foundScope->mParent;
	} while (foundScope != nullptr);

	if (returnScope != nullptr)
	{
		*returnScope = foundScope;
	}

	return returnDatum;
}

Datum& Scope::Append(const std::string& key)
{
	bool didInsert;
	Datum datum;
	Iterator it= mTable.Insert(EntryType(key, datum), didInsert);

	if (didInsert)
	{
		mOrderArray.PushBack(&*it);
	}
	return it->second;
}

Scope& Scope::AppendScope(const std::string& key)
{
	Datum& scopeDatum = Append(key);

	if (scopeDatum.Type() != DatumType::INVALID && scopeDatum.Type() != DatumType::TABLE)
	{
		throw exception("Datum at specified key is not of TABLE type");
	}

	Scope* scope = new Scope();
	scope->mParent = this;
	scopeDatum.PushBack(scope);

	return *(scope);
}

void Scope::Adopt(Scope& scopeToAdpot, const std::string& key)
{
	if (this == &scopeToAdpot)
	{
		throw exception("Cannot adopt self");
	}

	Datum& scopeDatum = Append(key);

	if (scopeDatum.Type() != DatumType::INVALID && scopeDatum.Type() != DatumType::TABLE)
	{
		throw exception("Datum at specified key is not of TABLE type");
	}

	if (scopeToAdpot.mParent != nullptr)
	{
		scopeToAdpot.mParent->Orphan(scopeToAdpot);
	}

	scopeToAdpot.mParent = this;
	scopeDatum.PushBack(&scopeToAdpot);
}

void Scope::Orphan(Scope& scopeToOrphan)
{
	for (EntryType* value : mOrderArray)
	{
		if (value->second.Remove(&scopeToOrphan))
		{
			break;
		}
	}
	scopeToOrphan.mParent = nullptr;
}

Datum& Scope::operator[](const std::string& key)
{
	return Append(key);
}

const Datum& Scope::operator[](const std::string&key) const
{
	if (!mTable.ContainsKey(key))
	{
		throw exception("Key not found");
	}

	return mTable[key];
}

Datum& Scope::operator[](uint32_t index)
{
	if (index >= mOrderArray.Size())
	{
		throw exception("Index out of range");
	}

	return mOrderArray[index]->second; 
}

const Datum& Scope::operator[](uint32_t index) const
{
	if (index >= mOrderArray.Size())
	{
		throw exception("Index out of range");
	}

	return mOrderArray[index]->second;
}


Scope* Scope::GetParent()
{
	return mParent;
}

const Scope* Scope::GetParent() const
{
	return mParent;
}

bool Scope::operator==(const Scope& otherScope) const
{
	return (mTable == otherScope.mTable);
}

bool Scope::operator!=(const Scope& otherScope) const
{
	return !(*this == otherScope);
}

bool Scope::Equals(const RTTI* rhs) const
{
	if (this == rhs)
	{
		return true;
	}

	if (rhs == nullptr)
	{
		return false;
	}

	Scope* scope = rhs->As<Scope>();
	return(scope != nullptr ? *this == *scope : false);
}

Datum* Scope::FindContainedScope(Scope& scope, uint32_t& index)
{
	Datum* foundDatum = nullptr;
	for (auto value : mOrderArray)
	{
		Datum& datum = value->second;
		if (datum.Type() == DatumType::TABLE)
		{
			for (uint32_t i = 0; i < datum.Size(); ++i)
			{
				if (datum.Get<Scope*&>(i) == &scope)
				{
					foundDatum = &datum;
					index = i;
					break;
				}
			}
		}
	}
	return foundDatum;
}

void Scope::Reparent(Scope& otherScope)
{
	if (mParent != nullptr)
	{
		uint32_t index = mOrderArray.Size();
		Datum* parentDatum = mParent->FindContainedScope(otherScope, index);

		if (parentDatum != nullptr)
		{
			parentDatum->Set(this, index);
		}
	}


	for (auto value : mOrderArray)
	{
		Datum& datum = value->second;
		if (datum.Type() == DatumType::TABLE)
		{
			for (uint32_t i = 0; i < datum.Size(); ++i)
			{
				datum.Get<Scope*&>(i)->mParent = this;		
			}
		}
	}
}

Scope* Scope::Copy() const
{
	return new Scope(*this);
}

const Vector<pair<string, Datum>*>& Scope::GetEntries() const
{
	return mOrderArray;
}
