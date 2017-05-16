#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

namespace UnitTest
{

	EventSubscriberFoo::EventSubscriberFoo()
	{
		mNotified = false;
		mCount = 0;
	}

	void EventSubscriberFoo::Notify(const EventPublisher& eventPublisher)
	{
		if (eventPublisher.Is(Event<Foo>::TypeIdClass()))
		{
			{
				lock_guard<mutex> lock(mMutex);
				mNotified = true;
				mFoo = eventPublisher.As<Event<Foo>>()->Message();
				++mCount;
			}

		}
	}
}