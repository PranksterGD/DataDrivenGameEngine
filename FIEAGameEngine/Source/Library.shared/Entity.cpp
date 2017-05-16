#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(Entity)

ConcreteActionFactory(ActionList)


string Entity::sEntitiesTag = "Entities";
string Entity::sActionsTag = "Actions";

Entity::Entity(string name):
	Attributed(), mName(name), mSector(nullptr)
{
	InitalizeSignatures();
}

Entity::Entity(const Entity& otherEntity)
{
	*this = otherEntity;
}

Entity::Entity(Entity&& otherEntity)
{
	*this = move(otherEntity);
}

Entity& Entity::operator=(const Entity& otherEntity)
{
	if (this != &otherEntity)
	{
		mName = otherEntity.mName;
		mSector = otherEntity.mSector;

		Attributed::operator=(otherEntity);
		FixExternals();
	}

	return *this;
}

Entity& Entity::operator=(Entity&& otherEntity)
{
	if (this != &otherEntity)
	{
		mName = otherEntity.mName;
		mSector = otherEntity.mSector;

		Attributed::operator=(move(otherEntity));
		FixExternals();
	}

	otherEntity.mName = string();
	otherEntity.mSector = nullptr;

	return *this;
}

void Entity::InitalizeSignatures()
{
	Attributed::InitalizeSignatures();

	AddExternalAttribute(World::sNameTag, &mName, 1);

	AddEmptyScopeAttribute(sActionsTag);

	AddEmptyScopeAttribute(Reaction::sReactionsTag);
}

const string& Entity::Name() const
{
	return mName;
}

string& Entity::Name()
{
	return mName;
}

void Entity::SetName(const std::string& name)
{
	mName = name;
}

Datum& Entity::Actions()
{
	return *Find(sActionsTag);
}

const Datum& Entity::Actions() const
{
	return *Find(sActionsTag);
}

Action* Entity::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* action = Factory<Action>::Create(className);
	action->SetName(instanceName);
	Adopt(*action, sActionsTag);

	return action;
}

const Sector* Entity::GetSector() const
{
	return mSector;
}

Sector* Entity::GetSector()
{
	return mSector;
}

void Entity::SetSector(Sector& sector)
{
	sector.Adopt(*this, sEntitiesTag);
	mSector = &sector;
}

void Entity::Update(WorldState& worldState)
{
	worldState.mCurrentEntity = this;

	Datum* actionsDatum = Find(sActionsTag);

	for (uint32_t i = 0; i < actionsDatum->Size(); ++i)
	{
		assert(actionsDatum->Get<Scope*&>(i)->Is("Action"));
		static_cast<Action*>(actionsDatum->Get<Scope*&>(i))->Update(worldState);
	}
}

void Entity::FixExternals()
{
	(*this)[World::sNameTag].SetStorage(&mName, 1);
}

Scope* Entity::Copy() const
{
	return new Entity(*this);
}