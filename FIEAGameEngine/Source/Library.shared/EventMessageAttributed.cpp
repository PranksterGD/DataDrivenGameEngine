#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

string EventMessageAttributed::sSubtypeTag = "Subtype";
string EventMessageAttributed::sWorldTag = "World";

RTTI_DEFINITIONS(EventMessageAttributed)

EventMessageAttributed::EventMessageAttributed(const std::string& subtype, WorldState* worldState) :
	Attributed(), mSubType(subtype), mWorldState(worldState)
{
	InitalizeSignatures();
}

EventMessageAttributed::EventMessageAttributed(const EventMessageAttributed& otherEventMessageAttributed)
{
	*this = otherEventMessageAttributed;
}

EventMessageAttributed::EventMessageAttributed(EventMessageAttributed&& otherEventMessageAttributed)
{
	*this = move(otherEventMessageAttributed);
}

EventMessageAttributed& EventMessageAttributed::operator=(const EventMessageAttributed& otherEventMessageAttributed)
{
	if (this != &otherEventMessageAttributed)
	{
		mSubType = otherEventMessageAttributed.mSubType;
		mWorldState = otherEventMessageAttributed.mWorldState;

		Attributed::operator=(otherEventMessageAttributed);
		FixExternals();
	}
	return *this;
}

EventMessageAttributed& EventMessageAttributed::operator=(EventMessageAttributed&& otherEventMessageAttributed)
{
	if (this != &otherEventMessageAttributed)
	{
		mSubType = otherEventMessageAttributed.mSubType;
		mWorldState = otherEventMessageAttributed.mWorldState;

		Attributed::operator= (move(otherEventMessageAttributed));
		FixExternals();

		otherEventMessageAttributed.mSubType = string();
		otherEventMessageAttributed.mWorldState = nullptr;
	}
	return *this;
}

const string& EventMessageAttributed::GetSubType() const
{
	return mSubType;
}

void EventMessageAttributed::SetSubType(const std::string& subtype)
{
	mSubType = subtype;
}

WorldState* EventMessageAttributed::GetWorldState() const
{
	return mWorldState;
}

void EventMessageAttributed::SetWorldState(WorldState& worldState)
{
	mWorldState = &worldState;
}

void EventMessageAttributed::InitalizeSignatures()
{
	Attributed::InitalizeSignatures();

	AddExternalAttribute(sSubtypeTag, &mSubType, 1);
}

void EventMessageAttributed::FixExternals()
{
	(*this)[sSubtypeTag].SetStorage(&mSubType, 1);
}

Scope* EventMessageAttributed::Copy() const
{
	return new EventMessageAttributed(*this);
}