#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(Action)


Action::Action(string name) :
	Attributed(), mName(name)
{
	InitalizeSignatures();
}

Action::Action(const Action& otherAction)
{
	*this = otherAction;
}

Action::Action(Action&& otherAction)
{
	*this = move(otherAction);
}

Action& Action::operator=(const Action& otherAction)
{
	if (this != &otherAction)
	{
		mName = otherAction.mName;

		Attributed::operator=(otherAction);
		FixExternals();
	}

	return *this;
}

Action& Action::operator=(Action&& otherAction)
{
	if (this != &otherAction)
	{
		mName = otherAction.mName;

		Attributed::operator=(move(otherAction));
		FixExternals();
	}

	otherAction.mName = string();

	return *this;
}

void Action::InitalizeSignatures()
{
	Attributed::InitalizeSignatures();

	AddExternalAttribute(World::sNameTag, &mName, 1);

	AddEmptyScopeAttribute(Reaction::sReactionsTag);
}

const string& Action::Name() const
{
	return mName;
}

string& Action::Name()
{
	return mName;
}

void Action::SetName(const std::string& name)
{
	mName = name;
}

void Action::FixExternals()
{
	(*this)[World::sNameTag].SetStorage(&mName, 1);
}