#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

namespace UnitTest
{

	RemoveSubscriberSubscriber::RemoveSubscriberSubscriber()
	{
		mNotified = false;

	}

	void RemoveSubscriberSubscriber::Notify(const EventPublisher& eventPublisher)
	{
		if (eventPublisher.Is(Event<Foo>::TypeIdClass()))
		{
			mNotified = true;

			Event<Foo>::Unsubscribe(*this);
		}
	}
}