#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(Sector)

string Sector::sSectorsTag = "Sectors";

Sector::Sector(string name):
	Attributed(), mName(name), mWorld(nullptr)
{
	InitalizeSignatures();
}

Sector::Sector(const Sector& otherSector)
{
	*this = otherSector;
}

Sector::Sector(Sector&& otherSector)
{
	*this = move(otherSector);
}

Sector& Sector::operator=(const Sector& otherSector)
{
	if (this != &otherSector)
	{
		Attributed::operator=(otherSector);
		mName = otherSector.mName;
		mWorld = otherSector.mWorld;
		FixExternals();
	}

	return *this;
}

Sector& Sector::operator=(Sector&& otherSector)
{
	if (this != &otherSector)
	{
		mName = otherSector.mName;
		mWorld = otherSector.mWorld;

		Attributed::operator=(move(otherSector));
		FixExternals();

		otherSector.mName = string();
		otherSector.mWorld = nullptr;
	}
	
	return *this;
}

void Sector::InitalizeSignatures()
{
	Attributed::InitalizeSignatures();

	AddExternalAttribute(World::sNameTag, &mName, 1);

	AddEmptyScopeAttribute(Entity::sEntitiesTag);

	AddEmptyScopeAttribute(Entity::sActionsTag);

	AddEmptyScopeAttribute(Reaction::sReactionsTag);
}

const string& Sector::Name() const
{
	return mName;
}

string& Sector::Name()
{
	return mName;
}

void Sector::SetName(const std::string& name)
{
	mName = name;
}

const World* Sector::GetWorld() const
{
	return mWorld;
}

World* Sector::GetWorld()
{
	return mWorld;
}

void Sector::SetWorld(World& world)
{
	world.Adopt(*this, sSectorsTag);
	mWorld = &world;
}

Entity* Sector::CreateEntity(const std::string& className, const std::string& instanceName)
{
	EntityFactory a;
	Entity* entity = Factory<Entity>::Create(className);
	entity->SetName(instanceName);
	entity->SetSector(*this);
	
	return entity;
}

void Sector::Update(WorldState& worldState)
{
	worldState.mCurrentSector = this;

	Datum* actionsDatum = Find(Entity::sActionsTag);

	for (uint32_t i = 0; i < actionsDatum->Size(); ++i)
	{
		assert(actionsDatum->Get<Scope*&>(i)->Is("Action"));
		static_cast<Action*>(actionsDatum->Get<Scope*&>(i))->Update(worldState);
	}

	Datum* entitiesDatum = Find(Entity::sEntitiesTag);

	for (uint32_t i = 0; i < entitiesDatum->Size(); ++i)
	{
		assert(entitiesDatum->Get<Scope*&>(i)->Is("Entity"));
		static_cast<Entity*>(entitiesDatum->Get<Scope*&>(i))->Update(worldState);
	}
}

const Datum& Sector::Entities() const
{
	return *Find(Entity::sEntitiesTag);
}

Datum& Sector::Entities()
{
	return *Find(Entity::sEntitiesTag);
}

const Datum& Sector::Actions() const
{
	return *Find(Entity::sActionsTag);
}

Datum& Sector::Actions()
{
	return *Find(Entity::sActionsTag);
}

void Sector::FixExternals()
{
	(*this)["Name"].SetStorage(&mName, 1);
}

Scope* Sector::Copy() const
{
	return new Sector(*this);
}