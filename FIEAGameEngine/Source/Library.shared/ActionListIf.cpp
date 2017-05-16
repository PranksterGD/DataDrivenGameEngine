#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(ActionListIf)

string ActionListIf::sConditionTag = "condition";
string ActionListIf::sThenTag = "then";
string ActionListIf::sElseTag = "else";

ActionListIf::ActionListIf(std::string name) :
	ActionList(name), mCondtion(0)
{
	InitalizeSignatures();
}

ActionListIf::ActionListIf(const ActionListIf& otherActionListIf)
{
	*this = otherActionListIf;
}

ActionListIf::ActionListIf(ActionListIf&& otherActionListIf)
{
	*this = move(otherActionListIf);
}

ActionListIf& ActionListIf::operator=(const ActionListIf& otherActionListIf)
{
	if (this != &otherActionListIf)
	{
		mCondtion = otherActionListIf.mCondtion;
		Action::operator=(otherActionListIf);
		FixExternals();
	}

	return *this;
}

ActionListIf& ActionListIf::operator=(ActionListIf&& otherActionListIf)
{
	if (this != &otherActionListIf)
	{
		mCondtion = otherActionListIf.mCondtion;
		Action::operator=(move(otherActionListIf));
		FixExternals();
	}

	return *this;
}

void ActionListIf::InitalizeSignatures()
{
	ActionList::InitalizeSignatures();

	AddExternalAttribute(sConditionTag, &mCondtion, 1);
}

void ActionListIf::FixExternals()
{
	(*this)[sConditionTag].SetStorage(&mCondtion, 1);
}

void ActionListIf::SetCondition(std::int32_t conditon)
{
	mCondtion = conditon;
}

std::int32_t ActionListIf::GetCondition() const
{
	return mCondtion;
}

Action* ActionListIf::GetThenAction()
{
	Datum actionsDatum = *Find(Entity::sActionsTag);

	Action* returnAction = nullptr;

	for (uint32_t i = 0; i < actionsDatum.Size(); ++i)
	{
		Action* action = actionsDatum.Get<Scope*&>(i)->As<Action>();
		if (action != nullptr)
		{
			if (action->Name() == sThenTag)
			{
				returnAction = action;
			}
		}
	}

	return returnAction;
}

const Action* ActionListIf::GetThenAction() const
{
	Datum actionsDatum = *Find(Entity::sActionsTag);

	Action* returnAction = nullptr;

	for (uint32_t i = 0; i < actionsDatum.Size(); ++i)
	{
		Action* action = actionsDatum.Get<Scope*&>(i)->As<Action>();
		if (action != nullptr)
		{
			if (action->Name() == sThenTag)
			{
				returnAction = action;
			}
		}
	}

	return returnAction;
}

Action* ActionListIf::GetElseAction()
{
	Datum actionsDatum = *Find(Entity::sActionsTag);

	Action* returnAction = nullptr;

	for (uint32_t i = 0; i < actionsDatum.Size(); ++i)
	{
		Action* action = actionsDatum.Get<Scope*&>(i)->As<Action>();
		if (action != nullptr)
		{
			if (action->Name() == sElseTag)
			{
				returnAction = action;
			}
		}
	}

	return returnAction;
}

const Action* ActionListIf::GetElseAction() const
{
	Datum actionsDatum = *Find(Entity::sActionsTag);

	Action* returnAction = nullptr;

	for (uint32_t i = 0; i < actionsDatum.Size(); ++i)
	{
		Action* action = actionsDatum.Get<Scope*&>(i)->As<Action>();
		if (action != nullptr)
		{
			if (action->Name() == sElseTag)
			{
				returnAction = action;
			}
		}
	}

	return returnAction;
}

void ActionListIf::Update(WorldState& worldState)
{
	worldState.mCurrentAction = this;

	Action* actionToFire = mCondtion ? GetThenAction() : GetElseAction();

	actionToFire->Update(worldState);

}

Scope* ActionListIf::Copy() const
{
	return new ActionListIf(*this);
}
