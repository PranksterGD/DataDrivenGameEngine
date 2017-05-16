#include "pch.h"

using namespace std;
using namespace FieaGameEngine;
using namespace std::chrono;

RTTI_DEFINITIONS(ActionEvent)


ActionEvent::ActionEvent(const std::string& name,const std::string& subtype, int32_t delay) :
	Action(name), mSubtype(subtype), mDelay(delay)
{
	InitalizeSignatures();
}

ActionEvent::ActionEvent(const ActionEvent& otherActionEvent)
{
	*this = otherActionEvent;
}

ActionEvent::ActionEvent(ActionEvent&& otherActionEvent)
{
	*this = move(otherActionEvent);
}

ActionEvent& ActionEvent::operator=(const ActionEvent& otherActionEvent)
{
	if (this != &otherActionEvent)
	{
		mSubtype = otherActionEvent.mSubtype;
		mDelay = otherActionEvent.mDelay;

		Action::operator=(otherActionEvent);
		FixExternals();
	}

	return *this;
}

ActionEvent& ActionEvent::operator=(ActionEvent&& otherActionEvent)
{
	if (this != &otherActionEvent)
	{
		mSubtype = otherActionEvent.mSubtype;
		mDelay = otherActionEvent.mDelay;

		Action::operator= (move(otherActionEvent));
		FixExternals();

		otherActionEvent.mSubtype = string();
		otherActionEvent.mDelay = 0;
	}

	return *this;
}

void ActionEvent::SetDelay(int32_t delay)
{
	mDelay = delay;
}

void ActionEvent::SetSubtype(const std::string& subtype)
{
	mSubtype = subtype;
}

const string& ActionEvent::GetSubtype() const
{
	return mSubtype;
}

int32_t ActionEvent::GetDelay() const
{
	return mDelay;
}

void ActionEvent::Update(WorldState& worldState)
{
	EventMessageAttributed message(mSubtype, &worldState);

	Vector<pair<string, Datum>*> auxiliaryAttributes = GetAuxiliaryAttributes();

	for (auto& entry : auxiliaryAttributes)
	{
		Datum& datum = message.Append(entry->first);
		datum = entry->second;
	}

	Event<EventMessageAttributed>* event = new Event<EventMessageAttributed>(message);

	worldState.mCurrentWorld->GetEventQueue().Enqueue(*event, worldState.mGameTime, milliseconds(mDelay));
}

void ActionEvent::InitalizeSignatures()
{
	Action::InitalizeSignatures();

	AddExternalAttribute(EventMessageAttributed::sSubtypeTag, &mSubtype, 1);

	AddExternalAttribute("Delay", &mDelay, 1);
}

void ActionEvent::FixExternals()
{
	(*this)[EventMessageAttributed::sSubtypeTag].SetStorage(&mSubtype, 1);

	(*this)["Delay"].SetStorage(&mDelay, 1);
}

Scope* ActionEvent::Copy() const
{
	return new ActionEvent(*this);
}