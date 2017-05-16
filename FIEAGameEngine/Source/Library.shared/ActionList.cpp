#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionList)

ActionList::ActionList(std::string name) :
	Action(name)
{
	InitalizeSignatures();
}

ActionList::ActionList(const ActionList& otherActionList)
{
	*this = otherActionList;
}

ActionList::ActionList(ActionList&& otherActionList)
{
	*this = move(otherActionList);
}

ActionList& ActionList::operator=(const ActionList& otherActionList)
{
	if (this != &otherActionList)
	{
		Action::operator=(otherActionList);
		FixExternals();
	}

	return *this;
}

ActionList& ActionList::operator=(ActionList&& otherActionList)
{
	if (this != &otherActionList)
	{

		Action::operator=(move(otherActionList));
		FixExternals();
	}

	return *this;
}

void ActionList::InitalizeSignatures()
{
	Action::InitalizeSignatures();

	AddEmptyScopeAttribute(Entity::sActionsTag);
}

void ActionList::FixExternals()
{
	(*this)[World::sNameTag].SetStorage(&mName, 1);
}

Action* ActionList::CreateAction(const std::string& className, const std::string& instanceName)
{
	Action* action = Factory<Action>::Create(className);
	action->SetName(instanceName);
	Adopt(*action, Entity::sActionsTag);

	return action;
}

const Datum& ActionList::Actions() const
{
	return *Find(Entity::sActionsTag);
}

Datum& ActionList::Actions()
{
	return *Find(Entity::sActionsTag);
}

void ActionList::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;

	Datum actionsDatum = *Find(Entity::sActionsTag);

	for (uint32_t i = 0; i < actionsDatum.Size(); ++i)
	{
		assert(actionsDatum.Get<Scope*&>(i)->Is("Action"));
		static_cast<Action*>(actionsDatum.Get<Scope*&>(i))->Update(worldState);
	}
}

Scope* ActionList::Copy() const
{
	return new ActionList(*this);
}
