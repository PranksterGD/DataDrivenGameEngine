#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionDestroyAction)

ActionDestroyAction::ActionDestroyAction(std::string name, std::string instanceName) :
	Action(name), mInstanceName(instanceName)
{
	InitalizeSignatures();
}

ActionDestroyAction::ActionDestroyAction(const ActionDestroyAction& otherActionDestroyAction)
{
	*this = otherActionDestroyAction;
}

ActionDestroyAction::ActionDestroyAction(ActionDestroyAction&& otherActionDestroyAction)
{
	*this = move(otherActionDestroyAction);
}

ActionDestroyAction& ActionDestroyAction::operator=(const ActionDestroyAction& otherActionDestroyAction)
{
	if (this != &otherActionDestroyAction)
	{
		mInstanceName = otherActionDestroyAction.mInstanceName;

		Action::operator=(otherActionDestroyAction);
		FixExternals();
	}

	return *this;
}

ActionDestroyAction& ActionDestroyAction::operator=(ActionDestroyAction&& otherActionDestroyAction)
{
	if (this != &otherActionDestroyAction)
	{
		mInstanceName = otherActionDestroyAction.mInstanceName;

		Action::operator=(move(otherActionDestroyAction));
		FixExternals();
	}

	otherActionDestroyAction.mInstanceName = string();

	return *this;
}


void ActionDestroyAction::SetDestroyedInstanceName(std::string InstanceName)
{
	mInstanceName = InstanceName;
}

string& ActionDestroyAction::GetDestroyedInstanceName()
{
	return mInstanceName;
}

const string& ActionDestroyAction::GetDestroyedInstanceName() const
{
	return mInstanceName;
}

void ActionDestroyAction::InitalizeSignatures()
{
	Action::InitalizeSignatures();

	AddExternalAttribute("InstanceName", &mInstanceName, 1);
}

void ActionDestroyAction::FixExternals()
{

	(*this)["InstanceName"].SetStorage(&mInstanceName, 1);
}

void ActionDestroyAction::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;

	Action* actionToDestroy;
	Datum* actionsDatum = nullptr;

	if (GetParent() != nullptr)
	{
		actionsDatum = GetParent()->Find(Entity::sActionsTag);
	}

	if (actionsDatum != nullptr)
	{
		for (uint32_t i = 0; i < actionsDatum->Size(); ++i)
		{
			assert(actionsDatum->Get<Scope*&>(i)->Is("Action"));

			actionToDestroy = static_cast<Action*>(actionsDatum->Get<Scope*&>(i));
			
			if (actionToDestroy->Name() == mInstanceName)
			{
				if (worldState.mCurrentWorld != nullptr)
				{
					worldState.mCurrentWorld->AddToDeletionQueue(actionToDestroy);
				}
			}
		}
	}
}

Scope* ActionDestroyAction::Copy() const
{
	return new ActionDestroyAction(*this);
}
