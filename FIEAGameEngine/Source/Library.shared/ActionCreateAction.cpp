#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionCreateAction)

ActionCreateAction::ActionCreateAction(std::string name, std::string className, std::string instanceName) :
	Action(name), mClassName(className), mInstanceName(instanceName)
{
	InitalizeSignatures();
}

ActionCreateAction::ActionCreateAction(const ActionCreateAction& otherActionCreateAction)
{
	*this = otherActionCreateAction;
}

ActionCreateAction::ActionCreateAction(ActionCreateAction&& otherActionCreateAction)
{
	*this = move(otherActionCreateAction);
}

ActionCreateAction& ActionCreateAction::operator=(const ActionCreateAction& otherActionCreateAction)
{
	if (this != &otherActionCreateAction)
	{
		mClassName = otherActionCreateAction.mClassName;
		mInstanceName = otherActionCreateAction.mInstanceName;

		Action::operator=(otherActionCreateAction);
		FixExternals();
	}

	return *this;
}

ActionCreateAction& ActionCreateAction::operator=(ActionCreateAction&& otherActionCreateAction)
{
	if (this != &otherActionCreateAction)
	{;
		mClassName = otherActionCreateAction.mClassName;
		mInstanceName = otherActionCreateAction.mInstanceName;

		Action::operator=(move(otherActionCreateAction));
		FixExternals();
	}

	otherActionCreateAction.mClassName = string();
	otherActionCreateAction.mInstanceName = string();

	return *this;
}

void ActionCreateAction::SetCreatedClassName(std::string className)
{
	mClassName = className;
}

void ActionCreateAction::SetCreatedInstanceName(std::string InstanceName)
{
	mInstanceName = InstanceName;
}

string& ActionCreateAction::GetCreatedClassName()
{
	return mClassName;
}

const string& ActionCreateAction::GetCreatedClassName() const
{
	return mClassName;
}

string& ActionCreateAction::GetCreatedInstanceName()
{
	return mInstanceName;
}

const string& ActionCreateAction::GetCreatedInstanceName() const
{
	return mInstanceName;
}

void ActionCreateAction::InitalizeSignatures()
{
	Action::InitalizeSignatures();

	AddExternalAttribute("ClassName", &mClassName, 1);

	AddExternalAttribute("InstanceName", &mInstanceName, 1);
}

void ActionCreateAction::FixExternals()
{
	(*this)["ClassName"].SetStorage(&mClassName, 1);

	(*this)["InstanceName"].SetStorage(&mInstanceName, 1);
}

void ActionCreateAction::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;

	if (GetParent() != nullptr)
	{
		Action* action = Factory<Action>::Create(mClassName);

		if (action != nullptr)
		{
			action->SetName(mInstanceName);

			GetParent()->Adopt(*action, Entity::sActionsTag);
		}
	}
}

Scope* ActionCreateAction::Copy() const
{
	return new ActionCreateAction(*this);
}
