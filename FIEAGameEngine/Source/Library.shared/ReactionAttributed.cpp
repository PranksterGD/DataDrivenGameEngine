#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

RTTI_DEFINITIONS(ReactionAttributed)

ReactionAttributed::ReactionAttributed(const std::string& name) :
	Reaction(name)
{
	InitalizeSignatures();

	Event<EventMessageAttributed>::Subscribe(*this);
}

ReactionAttributed::ReactionAttributed(const ReactionAttributed& otherReactionAttirubted)
{
	Event<EventMessageAttributed>::Subscribe(*this);

	*this = otherReactionAttirubted;
}

ReactionAttributed::ReactionAttributed(ReactionAttributed&& otherReactionAttirubted)
{
	Event<EventMessageAttributed>::Subscribe(*this);

	*this = move(otherReactionAttirubted);
}

ReactionAttributed& ReactionAttributed::operator=(const ReactionAttributed& otherReactionAttirubted)
{
	if (this != &otherReactionAttirubted)
	{
		ActionList::operator=(otherReactionAttirubted);
	}
	return *this;
}

ReactionAttributed& ReactionAttributed::operator=(ReactionAttributed&& otherReactionAttirubted)
{
	if (this != &otherReactionAttirubted)
	{
		ActionList::operator=(move(otherReactionAttirubted));

		Event<EventMessageAttributed>::Unsubscribe(otherReactionAttirubted);
	}
	return *this;
}

void ReactionAttributed::InitalizeSignatures()
{
	ActionList::InitalizeSignatures();

	AddEmptyStringAttribute("Subtype");
}

void ReactionAttributed::Notify(const EventPublisher& eventPublisher)
{
	Event<EventMessageAttributed>* event = eventPublisher.As<Event<EventMessageAttributed>>();

	if (event != nullptr)
	{
		const EventMessageAttributed& message = event->Message();

		Datum* subtypeDatum = Find("Subtype");

		for (uint32_t i = 0; i < subtypeDatum->Size(); ++i)
		{
			if (subtypeDatum->Get<string&>(i) == message.GetSubType())
			{
				Vector<pair<string, Datum>*> auxiliaryAttributes = message.GetAuxiliaryAttributes();

				for (auto& entry : auxiliaryAttributes)
				{
					if (entry->second.Type() != DatumType::TABLE)
					{
						Datum& datum = Append(entry->first);
						datum = entry->second;
					}

				}

				if (message.GetWorldState() != nullptr)
				{
					ActionList::Update(*message.GetWorldState());
				}
			
			}
		}
	}
}

Scope* ReactionAttributed::Copy() const
{
	return new ReactionAttributed(*this);
}

ReactionAttributed::~ReactionAttributed()
{
	Event<EventMessageAttributed>::Unsubscribe(*this);
}