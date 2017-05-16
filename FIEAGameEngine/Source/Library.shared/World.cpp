#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(World)

string World::sNameTag = "Name";

World::World(std::string name):
	Attributed(), mName(name)
{
	InitalizeSignatures();
}

World::World(const World& otherWorld)
{
	*this = otherWorld;
}

World::World(World&& otherWorld)
{
	*this = move(otherWorld);
}

World& World::operator=(const World& otherWorld)
{
	if (this != &otherWorld)
	{
		mName = otherWorld.mName;

		Attributed::operator=(otherWorld);
		FixExternals();
	}

	return *this;
}

World& World::operator=(World&& otherWorld)
{
	if (this != &otherWorld)
	{
		mName = otherWorld.mName;
		Attributed::operator=(move(otherWorld));
		FixExternals();

		otherWorld.mName = string();
	}
	return *this;
}

const string& World::Name() const
{
	return mName;
}

string& World::Name()
{
	return mName;
}

void World::SetName(const std::string& name)
{
	mName = name;
}

const Datum& World::Sectors() const
{
	return *Find(Sector::sSectorsTag);
}

Datum& World::Sectors()
{
	return *Find(Sector::sSectorsTag);
}

const Datum& World::Actions() const
{
	return *Find(Entity::sActionsTag);
}

Datum& World::Actions()
{
	return *Find(Entity::sActionsTag);
}

Sector* World::CreateSector(const std::string& name)
{
	Sector* sector = new Sector(name);
	sector->SetWorld(*this);

	return sector;
}

Action* World::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* action = Factory<Action>::Create(className);
	action->SetName(instanceName);
	Adopt(*action, Entity::sActionsTag);

	return action;
}

void World::Update(WorldState& worldState)
{
	worldState.mCurrentWorld = this;

	Datum* actionsDatum = Find(Entity::sActionsTag);

	for (uint32_t i = 0; i < actionsDatum->Size(); ++i)
	{
		assert(actionsDatum->Get<Scope*&>(i)->Is("Action"));
		static_cast<Action*>(actionsDatum->Get<Scope*&>(i))->Update(worldState);
	}

	Datum* sectorsDatum = Find(Sector::sSectorsTag);
	
	for (uint32_t i = 0; i < sectorsDatum->Size(); ++i)
	{
		assert(sectorsDatum->Get<Scope*&>(i)->Is("Sector"));
		static_cast<Sector*>(sectorsDatum->Get<Scope*&>(i))->Update(worldState);
	}

	for (Scope* scopeToDelete : mDeletionQueue)
	{
		delete(scopeToDelete);
	}

	mDeletionQueue.Clear();

	mEventQueue.Update(worldState.mGameTime);
}

void World::InitalizeSignatures()
{
	Attributed::InitalizeSignatures();

	AddExternalAttribute(sNameTag, &mName, 1);

	AddEmptyScopeAttribute(Sector::sSectorsTag);

	AddEmptyScopeAttribute(Entity::sActionsTag);

	AddEmptyScopeAttribute(Reaction::sReactionsTag);
}

void World::FixExternals()
{
	(*this)[sNameTag].SetStorage(&mName, 1);
}

void World::AddToDeletionQueue(Scope* scopeToDelete)
{
	mDeletionQueue.PushBack(scopeToDelete);
}

Scope* World::Copy() const
{
	return new World(*this);
}

EventQueue& World::GetEventQueue()
{
	return mEventQueue;
}

const EventQueue& World::GetEventQueue() const
{
	return mEventQueue;
}